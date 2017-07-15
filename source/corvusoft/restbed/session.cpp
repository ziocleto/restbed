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
#include <corvusoft/network/socket.hpp>
#include <corvusoft/protocol/message.hpp>
#include <corvusoft/protocol/protocol.hpp>

//System Namespaces
using std::bind;
using std::string;
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
using corvusoft::network::Socket;
using corvusoft::protocol::Message;
using corvusoft::protocol::Protocol;

namespace corvusoft
{
    namespace restbed
    {
        shared_ptr< Session > Session::create( const shared_ptr< Socket >& socket, const shared_ptr< Protocol >& protocol )
        {
            return shared_ptr< Session >( new Session( socket, protocol ) );
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
            return m_pimpl->socket not_eq nullptr and m_pimpl->socket->is_closed( );
        }
        
        void Session::close( const shared_ptr< Response >& response, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            yield( response, bind( m_pimpl->success_wrapper, _1, m_pimpl->socket, success ), failure );
        }
        
        void Session::close( const string body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            close( make_bytes( body ), success, failure );
        }
        
        void Session::close( const core::Bytes body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            assert( m_pimpl->socket not_eq nullptr );
            assert( m_pimpl->protocol not_eq nullptr );
            
            error_code error;
            m_pimpl->socket->produce( body, error );
            
            if ( not error and success not_eq nullptr )
            {
                success( shared_from_this( ) );
            }
            else if ( failure not_eq nullptr )
            {
                failure( shared_from_this( ), error );
            }
        }
        
        void Session::close( const int status, const multimap< const string, const string >& headers, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            close( make_shared< Response >( status, headers ), success, failure );
        }
        
        void Session::close( const int status, const multimap< const string, const string >& headers, const string body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            close( make_shared< Response >( status, headers, body ), success, failure );
        }
        
        void Session::close( const int status, const multimap< const string, const string >& headers, const core::Bytes body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            close( make_shared< Response >( status, headers, body ), success, failure );
        }
        
        void Session::yield( const shared_ptr< Response >& response, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            assert( m_pimpl->socket not_eq nullptr );
            assert( m_pimpl->protocol not_eq nullptr );
            
            if ( not response->has_property( "status:code" ) )
            {
                response->set_property( "status:code", "200" );
            }
            
            if ( not response->has_property( "status:message" ) )
            {
                response->set_property( "status:message", "OK" );
            }
            
            if ( not response->has_property( "version" ) )
            {
                response->set_property( "version", m_pimpl->request->get_property( "version" ) );
            }
            
            if ( not response->has_property( "protocol" ) )
            {
                response->set_property( "protocol", m_pimpl->request->get_property( "protocol" ) );
            }
            
            const auto error = m_pimpl->protocol->compose( m_pimpl->socket, response );
            
            if ( not error and success not_eq nullptr )
            {
                success( shared_from_this( ) );
            }
            else if ( failure not_eq nullptr )
            {
                failure( shared_from_this( ), error );
            }
        }
        
        void Session::yield( const string body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            yield( make_bytes( body ), success, failure );
        }
        
        void Session::yield( const core::Bytes body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            assert( m_pimpl->socket not_eq nullptr );
            assert( m_pimpl->protocol not_eq nullptr );
            
            error_code error;
            m_pimpl->socket->produce( body, error );
            
            if ( not error and success not_eq nullptr )
            {
                success( shared_from_this( ) );
            }
            else if ( failure not_eq nullptr )
            {
                failure( shared_from_this( ), error );
            }
        }
        
        void Session::yield( const int status, const multimap< const string, const string >& headers, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            yield( make_shared< Response >( status, headers ), success, failure );
        }
        
        void Session::yield( const int status, const multimap< const string, const string >& headers, const string body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            yield( make_shared< Response >( status, headers, body ), success, failure );
        }
        
        void Session::yield( const int status, const multimap< const string, const string >& headers, const core::Bytes body, const function< void ( const shared_ptr< Session > ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            yield( make_shared< Response >( status, headers, body ), success, failure );
        }
        
        void Session::fetch( const size_t length, const function< void ( const shared_ptr< Session >, const Bytes ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
        
        }
        
        void Session::fetch( const string& delimiter, const function< void ( const shared_ptr< Session >, const Bytes ) > success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
        
        }
        
        void Session::upgrade( const shared_ptr< Response >& response, const function< void ( const shared_ptr< WebSocket > ) >& success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            //build websocket.
            //yield response
        }
        
        void Session::upgrade( const int status, const multimap< const string, const string >& headers, const function< void ( const shared_ptr< WebSocket > ) >& success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            upgrade( make_shared< Response >( status, headers ), success, failure );
        }
        
        void Session::upgrade( const int status, const multimap< const string, const string >& headers, const string body, const function< void ( const shared_ptr< WebSocket > ) >& success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            upgrade( make_shared< Response >( status, headers, body ), success, failure );
        }
        
        void Session::upgrade( const int status, const multimap< const string, const string >& headers, const core::Bytes body, const function< void ( const shared_ptr< WebSocket > ) >& success, const function< void ( const shared_ptr< Session >, const error_code ) > failure )
        {
            upgrade( make_shared< Response >( status, headers, body ), success, failure );
        }
        
        const string Session::get_origin( void ) const
        {
            if ( m_pimpl->socket == nullptr )
            {
                return "";
            }
            
            return m_pimpl->socket->get_remote_endpoint( );
        }
        
        const string Session::get_destination( void ) const
        {
            if ( m_pimpl->socket == nullptr )
            {
                return "";
            }
            
            return m_pimpl->socket->get_local_endpoint( );
        }
        
        const shared_ptr< SessionData > Session::get_data( void ) const
        {
            return m_pimpl->data;
        }
        
        const shared_ptr< Socket > Session::get_socket( void ) const
        {
            return m_pimpl->socket;
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
        
        Session::Session( const shared_ptr< Socket >& socket, const shared_ptr< Protocol >& protocol ) : m_pimpl( new SessionImpl )
        {
            assert( socket not_eq nullptr );
            assert( protocol not_eq nullptr );
            
            m_pimpl->socket = socket;
            m_pimpl->protocol = protocol;
        }
    }
}
