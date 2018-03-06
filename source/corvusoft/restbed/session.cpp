/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <cassert>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"

//External Includes
#include <corvusoft/core/run_loop.hpp>
#include <corvusoft/network/adaptor.hpp>
#include <corvusoft/protocol/message.hpp>
#include <corvusoft/protocol/protocol.hpp>

//System Namespaces
using std::bind;
using std::string;
using std::size_t;
using std::function;
using std::multimap;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;

//Project Namespaces
using corvusoft::restbed::detail::SessionImpl;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::core::RunLoop;
using corvusoft::network::Adaptor;
using corvusoft::protocol::Message;
using corvusoft::protocol::Protocol;

namespace corvusoft
{
    namespace restbed
    {
        shared_ptr< Session > Session::create( const shared_ptr< Adaptor >& adaptor, const shared_ptr< Protocol >& protocol )
        {
            return shared_ptr< Session >( new Session( adaptor, protocol ) );
        }
        
        Session::~Session( void )
        {
            return;
        }
        
        bool Session::is_open( void ) const
        {
            return not is_closed( );
        }
        
        bool Session::is_closed( void ) const
        {
            return true;//m_pimpl->adaptor not_eq nullptr and m_pimpl->adaptor->is_closed( );
        }
        
        void Session::close( const shared_ptr< Response > response, const function< void ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            //yield( response, bind( m_pimpl->success_wrapper, _1, m_pimpl->adaptor, success ), failure );
        }
        
        void Session::close( const string body, const function< void ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            //close( make_bytes( body ), success, failure );
        }
        
        void Session::close( const core::Bytes body, const function< void ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            // assert( m_pimpl->adaptor not_eq nullptr );
            // assert( m_pimpl->protocol not_eq nullptr );
            
            // error_code error;
            // m_pimpl->adaptor->produce( body, error );
            
            // if ( not error and success not_eq nullptr )
            // {
            //     success( shared_from_this( ) );
            // }
            // else if ( failure not_eq nullptr )
            // {
            //     failure( shared_from_this( ), error );
            // }
        }
        
        void Session::yield( const shared_ptr< Response > response, const function< void ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            // assert( m_pimpl->adaptor not_eq nullptr );
            // assert( m_pimpl->protocol not_eq nullptr );
            
            // if ( not response->has_property( "status:code" ) )
            // {
            //     response->set_property( "status:code", "200" );
            // }
            
            // if ( not response->has_property( "status:message" ) )
            // {
            //     response->set_property( "status:message", "OK" );
            // }
            
            // if ( not response->has_property( "version" ) )
            // {
            //     response->set_property( "version", m_pimpl->request->get_property( "version" ) );
            // }
            
            // if ( not response->has_property( "protocol" ) )
            // {
            //     response->set_property( "protocol", m_pimpl->request->get_property( "protocol" ) );
            // }
            
            // const auto error = m_pimpl->protocol->compose( m_pimpl->adaptor, response );
            
            // if ( not error and success not_eq nullptr )
            // {
            //     success( shared_from_this( ) );
            // }
            // else if ( failure not_eq nullptr )
            // {
            //     failure( shared_from_this( ), error );
            // }
        }
        
        void Session::yield( const string body, const function< void ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            //yield( make_bytes( body ), success, failure );
        }
        
        void Session::yield( const core::Bytes body, const function< void ( const shared_ptr< Session >, const error_code ) > completion_handler )
        {
            // assert( m_pimpl->adaptor not_eq nullptr );
            // assert( m_pimpl->protocol not_eq nullptr );
            
            // error_code error;
            // m_pimpl->adaptor->produce( body, error );
            
            // if ( not error and success not_eq nullptr )
            // {
            //     success( shared_from_this( ) );
            // }
            // else if ( failure not_eq nullptr )
            // {
            //     failure( shared_from_this( ), error );
            // }
        }
        
        void Session::fetch( const size_t length, const function< void ( const shared_ptr< Session >, const Bytes, const error_code ) > completion_handler )
        {
        
        }
        
        void Session::fetch( const string delimiter, const function< void ( const shared_ptr< Session >, const Bytes, const error_code ) > completion_handler )
        {
        
        }
        
        void Session::upgrade( const shared_ptr< Response > response, const function< void ( const shared_ptr< Session >, const shared_ptr< WebSocket >, const error_code ) > completion_handler )
        {
            //build webadaptor.
            //yield response
        }
        
        const string Session::get_origin( void ) const
        {
            if ( m_pimpl->adaptor == nullptr )
            {
                return "";
            }
            
            return m_pimpl->adaptor->get_remote_endpoint( );
        }
        
        const string Session::get_destination( void ) const
        {
            if ( m_pimpl->adaptor == nullptr )
            {
                return "";
            }
            
            return m_pimpl->adaptor->get_local_endpoint( );
        }
        
        const shared_ptr< SessionData > Session::get_data( void ) const
        {
            return m_pimpl->data;
        }
        
        const shared_ptr< Adaptor > Session::get_adaptor( void ) const
        {
            return m_pimpl->adaptor;
        }
        
        const shared_ptr< Protocol > Session::get_protocol( void ) const
        {
            return m_pimpl->protocol;
        }
        
        const shared_ptr< RunLoop > Session::get_runloop( void ) const
        {
            return m_pimpl->runloop;
        }
        
        void Session::set_data( const shared_ptr< SessionData >& value )
        {
            m_pimpl->data = value;
        }
        
        void Session::set_default_header( const string& name, const string& value )
        {
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            add_default_header( name, value );
        }
        
        void Session::set_default_header( const string& name, const function< string ( void ) >& value )
        {
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            add_default_header( name, value );
        }
        
        void Session::add_default_header( const string& name, const string& value )
        {
            m_pimpl->default_headers.emplace( name, value );
        }
        
        void Session::add_default_header( const string& name, const function< string ( void ) >& value )
        {
            m_pimpl->dynamic_default_headers.emplace( name, value );
        }
        
        Session::Session( const shared_ptr< Adaptor >& adaptor, const shared_ptr< Protocol >& protocol ) : m_pimpl( new SessionImpl )
        {
            assert( adaptor not_eq nullptr );
            assert( protocol not_eq nullptr );
            
            m_pimpl->adaptor = adaptor;
            m_pimpl->protocol = protocol;
        }
    }
}
