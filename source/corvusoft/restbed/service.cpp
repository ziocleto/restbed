/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <ciso646>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/service.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/middleware.hpp"
#include "corvusoft/restbed/resource_cache.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/service_impl.hpp"

//External Includes
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/core/log_level.hpp>
#include <corvusoft/protocol/http.hpp>
#include <corvusoft/protocol/protocol.hpp>
#include <corvusoft/network/adaptor.hpp>
#include <corvusoft/network/tcpip_adaptor.hpp> //why not just call it tcpip.hpp?

//System Namespaces
using std::set;
using std::string;
using std::multimap;
using std::find;
using std::bind;
using std::function;
using std::placeholders::_1;
using std::placeholders::_2;
using std::shared_ptr;
using std::make_shared;
using std::error_code;
using std::make_error_code;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::chrono::duration_cast;

//Project Namespaces
using corvusoft::restbed::detail::ServiceImpl;

//External Namespaces
using corvusoft::core::ERROR;
using corvusoft::core::RunLoop;
using corvusoft::protocol::HTTP;
using corvusoft::protocol::Protocol;
using corvusoft::network::Adaptor;
using corvusoft::network::TCPIPAdaptor; //rename TCPIP

namespace corvusoft
{
    namespace restbed
    {
        Service::Service( void ) : m_pimpl( new ServiceImpl )
        {
            return;
        }
        
        Service::~Service( void )
        {
            try
            {
                stop( );
            }
            catch ( ... )
            {
                m_pimpl->log( "Service failed graceful retirement.", ERROR );
            }
        }
        
        bool Service::is_up( void ) const
        {
            return m_pimpl->uptime not_eq steady_clock::time_point::min( );
        }
        
        bool Service::is_down( void ) const
        {
            return not is_up( );
        }
        
        bool Service::is_suspended( void ) const
        {
            return m_pimpl->runloop->is_suspended( );
        }
        
        void Service::resume( void )
        {
            m_pimpl->runloop->resume( );
        }
        
        void Service::suspend( void )
        {
            m_pimpl->runloop->suspend( );
        }
        
        void Service::stop( void )
        {
            m_pimpl->runloop->stop( );
            m_pimpl->uptime = steady_clock::time_point::min( );
            
            for ( auto& component : m_pimpl->networks ) component->teardown( );
            for ( auto& component : m_pimpl->protocols ) component->teardown( );
            for ( auto& component : m_pimpl->middleware ) component->teardown( );
            
            if ( m_pimpl->session_manager not_eq nullptr )
                m_pimpl->session_manager->teardown( );
                
            if ( m_pimpl->resource_cache not_eq nullptr )
                m_pimpl->resource_cache->teardown( );
                
            m_pimpl->log( "Service operations retired." );
        }
        
        error_code Service::start( const shared_ptr< const Settings >& settings )
        {
            m_pimpl->settings = ( settings == nullptr ) ? make_shared< Settings >( ) : settings;
            
            auto failure = m_pimpl->initialise_component( m_pimpl->resource_cache, "Resource cache initialised.", "Failed to initialise resource cache." );
            if ( failure ) return failure;
            
            failure = m_pimpl->initialise_component( m_pimpl->session_manager, "Session management initialised.", "Failed to initialise session management." );
            if ( failure ) return failure;
            
            m_pimpl->log( "Initialising middleware layers" );
            failure = m_pimpl->initialise_layer< const Middleware >( m_pimpl->middleware );
            if ( failure ) return failure;
            
            m_pimpl->log( "Initialising protocol layers" );
            
            if ( m_pimpl->protocols.empty( ) )
                add_protocol( make_shared< HTTP >( ) );
                
            failure = m_pimpl->initialise_layer< Protocol >( m_pimpl->protocols );
            if ( failure ) return failure;
            
            m_pimpl->log( "Initialising network layers" );
            
            if ( m_pimpl->networks.empty( ) )
                add_network( TCPIPAdaptor::create( ) );
                
            failure = m_pimpl->initialise_layer< Adaptor >( m_pimpl->networks );
            if ( failure ) return failure;
            
            for ( const auto& layer : m_pimpl->networks )
            {
                layer->set_open_handler( [ this, layer ]( const shared_ptr< Adaptor > )
                {
                    m_pimpl->log( " " + layer->get_name( ) + " network layer enabled via " + layer->get_local_endpoint( ) );
                } );
                layer->set_error_handler( [ this, layer ]( const shared_ptr< Adaptor >, const error_code code )
                {
                    m_pimpl->error( code, layer->get_name( ) + " network layer failed at " + layer->get_local_endpoint( ), 2 );
                    stop( );
                } );
                //layer->listen( m_pimpl->settings, m_pimpl->acceptor );
            }
            
            m_pimpl->uptime = steady_clock::now( );
            //m_pimpl->runloop->enqueue( [ this ]( auto code )
            //{
            //    m_pimpl->ready_handler( );
            //    return code;
            //} );
            return m_pimpl->runloop->start( );
        }
        
        error_code Service::publish( const shared_ptr< const Resource >& resource )
        {
            if ( resource == nullptr )
            {
                return make_error_code( std::errc::bad_address );
            }
            
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->resources.emplace_back( resource );
            
            auto& middleware = resource->get_middleware( );
            
            // if ( not middleware.empty( ) )
            //{
            //    middleware.back( )->set_success_handler( m_pimpl->execute );
            //}
            
            //for ( auto& middleware : middleware )
            //{
            //    middleware->set_terminate_handler( m_pimpl->terminate );
            //}
            
            return error_code( );
        }
        
        error_code Service::suppress( const shared_ptr< const Resource >& resource )
        {
            if ( resource == nullptr )
            {
                return make_error_code( std::errc::bad_address );
            }
            
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            auto position = find( m_pimpl->resources.begin( ), m_pimpl->resources.end( ), resource );
            m_pimpl->resources.erase( position );
            
            return error_code( );
        }
        
        const seconds Service::get_uptime( void ) const
        {
            return ( is_down( ) ) ? seconds( 0 ) : duration_cast< seconds >( steady_clock::now( ) - m_pimpl->uptime );
        }
        
        const set< string > Service::get_destinations( void ) const
        {
            set< string > endpoints;
            
            for ( const auto& layer : m_pimpl->networks )
            {
                endpoints.insert( layer->get_local_endpoint( ) );
            }
            
            return endpoints;
        }
        
        const shared_ptr< RunLoop > Service::get_runloop( void ) const
        {
            return m_pimpl->runloop;
        }
        
        error_code Service::add_network( const shared_ptr< Adaptor >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            if ( value not_eq nullptr )
            {
                m_pimpl->networks.emplace_back( value );
            }
            
            return error_code( );
        }
        
        error_code Service::add_protocol( const shared_ptr< Protocol >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
                return make_error_code( std::errc::operation_in_progress );
                
            if ( value not_eq nullptr )
                m_pimpl->protocols.emplace_back( value );
                
            return error_code( );
        }
        
        error_code Service::add_middleware( const shared_ptr< Middleware >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            if ( value == nullptr )
            {
                return error_code( );
            }
            
            //if ( m_pimpl->middleware.empty( ) )
            //{
            //value->set_success_handler( m_pimpl->cache );
            //}
            //else
            //{
            //auto& middleware = m_pimpl->middleware.back( );
            //middleware->set_success_handler( bind( &Middleware::process, value, _1 ) );
            //value->set_success_handler( m_pimpl->cache );
            //}
            
            //value->set_terminate_handler( m_pimpl->terminate );
            //m_pimpl->middleware.emplace_back( value );
            
            return error_code( );
        }
        
        error_code Service::set_default_header( const string& name, const string& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            add_default_header( name, value );
            
            return error_code( );
        }
        
        error_code Service::set_default_header( const string& name, const function< string ( void ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            
            if ( value not_eq nullptr ) //on null hard set empty string like restless!
            {
                add_default_header( name, value );
            }
            
            return error_code( );
        }
        
        error_code Service::add_default_header( const string& name, const string& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->default_headers.emplace( name, value );
            return error_code( );
        }
        
        error_code Service::add_default_header( const string& name, const function< string ( void ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            if ( value not_eq nullptr )//on null hard set empty string like restless!
            {
                m_pimpl->dynamic_default_headers.emplace( name, value );
            }
            
            return error_code( );
        }
        
        error_code Service::set_log_handler( const function< void ( const int, const string ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->log_handler = value;
            return error_code( );
        }
        
        error_code Service::set_resource_cache( const shared_ptr< ResourceCache >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->resource_cache = value;
            return error_code( );
        }
        
        error_code Service::set_session_manager( const shared_ptr< SessionManager >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->session_manager = value;
            return error_code( );
        }
        
        error_code Service::set_error_handler( const function< void ( const error_code ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->error_handler = value;
            return error_code( );
        }
        
        error_code Service::set_ready_handler( const function< void ( void ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->ready_handler = value;
            return error_code( );
        }
        
        error_code Service::set_signal_handler( const int signal, const function< void ( void ) >& value )
        {
            //m_pimpl->runloop->enqueue_when( signal, [ value ]( auto code )
            //{
            //    value( );
            //    return code;
            //} );
            return error_code( );
        }
        
        error_code Service::set_resource_not_found_handler( const function< void ( const shared_ptr< Session > ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->resource_not_found_handler = value;
            return error_code( );
        }
        
        error_code Service::set_method_not_allowed_handler( const function< void ( const shared_ptr< Session > ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->method_not_allowed_handler = value;
            return error_code( );
        }
        
        error_code Service::set_method_not_implemented_handler( const function< void ( const shared_ptr< Session > ) >& value )
        {
            if ( is_up( ) and not is_suspended( ) )
            {
                return make_error_code( std::errc::operation_in_progress );
            }
            
            m_pimpl->method_not_implemented_handler = value;
            return error_code( );
        }
    }
}
