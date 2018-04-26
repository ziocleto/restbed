/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"

//External Includes

//System Namespaces
using std::function;
using std::error_code;
using std::shared_ptr;

//Project Namespaces
using corvusoft::restbed::detail::WebSocketImpl;

//External Namespaces
using corvusoft::core::Bytes;

namespace corvusoft
{
    namespace restbed
    {
        WebSocket::WebSocket( void ) : m_pimpl( new WebSocketImpl )
        {
            return;
        }
        
        WebSocket::~WebSocket( void )
        {
            try
            {
                close( );
            }
            catch ( ... )
            {
                // auto logger = m_pimpl->session->get_logger( );
                
                // if ( logger not_eq nullptr )
                // {
                //     logger->log( Logger::WARNING, "WebSocket failed graceful retirement." );
                // }
            }
        }
        
        bool WebSocket::is_open( void ) const
        {
            return m_pimpl->session->is_open( );
        }
        
        bool WebSocket::is_closed( void ) const
        {
            return m_pimpl->session->is_closed( );
        }
        
        void WebSocket::close( void )
        {
            //m_pimpl->session->close( );
            
            //if ( m_pimpl->close_handler not_eq nullptr )
            //    m_pimpl->close_handler( ); // “code”, “reason”, and “wasClean" or just error_code?
        }
        
        void WebSocket::send( const Bytes body, const function< void ( const shared_ptr< WebSocket > ) > success, const function< void ( const shared_ptr< WebSocket >, const error_code ) > failure )
        {
            //send( make_shared< WebSocketMessage >( WebSocketMessage::BINARY_FRAME, body ), success, failure );
        }
        
        void WebSocket::send( const OperationCode code, const function< void ( const shared_ptr< WebSocket > ) > success, const function< void ( const shared_ptr< WebSocket >, const error_code ) > failure )
        {
            //send( make_shared< WebSocketMessage >( code ), success, failure );
        }
        
        void WebSocket::send( const shared_ptr< WebSocketMessage > message, const function< void ( const shared_ptr< WebSocket > ) > success, const function< void ( const shared_ptr< WebSocket >, const error_code ) > failure )
        {
            //session->yield( message, success, failure );
        }
        
        const shared_ptr< Session > WebSocket::get_session( void ) const
        {
            return m_pimpl->session;
        }
        
        const function< void ( const shared_ptr< WebSocket > ) > WebSocket::get_open_handler( void ) const
        {
            return m_pimpl->open_handler;
        }
        
        const function< void ( const shared_ptr< WebSocket > ) > WebSocket::get_close_handler( void ) const
        {
            return m_pimpl->close_handler;
        }
        
        const function< void ( const shared_ptr< WebSocket >, const error_code ) > WebSocket::get_error_handler( void ) const
        {
            return m_pimpl->error_handler;
        }
        
        const function< void ( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) > WebSocket::get_message_handler( void ) const
        {
            return m_pimpl->message_handler;
        }
        
        void WebSocket::set_session( const shared_ptr< Session >& value )
        {
            m_pimpl->session = value;
        }
        
        void WebSocket::set_open_handler( const function< void ( const shared_ptr< WebSocket > ) >& value )
        {
            m_pimpl->open_handler = value;
        }
        
        void WebSocket::set_close_handler( const function< void ( const shared_ptr< WebSocket > ) >& value )
        {
            m_pimpl->close_handler = value;
        }
        
        void WebSocket::set_error_handler( const function< void ( const shared_ptr< WebSocket >, const error_code ) >& value )
        {
            m_pimpl->error_handler = value; //when call the handler make sure its not be called before! no error loops
        }
        
        void WebSocket::set_message_handler( const function< void ( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > ) >& value )
        {
            m_pimpl->message_handler = value;
        }
    }
}
