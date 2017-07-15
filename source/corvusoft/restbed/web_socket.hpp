/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_WEB_SOCKET_H
#define _CORVUSOFT_RESTBED_WEB_SOCKET_H 1

//System Includes
#include <memory>
#include <cstdint>
#include <functional>
#include <system_error>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    namespace core
    {
        class Logger;
    }
    
    namespace restbed
    {
        //Forward Declarations
        class Session;
        class WebSocketMessage;
        enum OperationCode : std::uint8_t;
        
            namespace detail
        {
            struct WebSocketImpl;
        }
        
        class WebSocket final
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                WebSocket( void );
                
                virtual ~WebSocket( void );
                
                //Functionality
                bool is_open( void ) const;
                
                bool is_closed( void ) const;
                
                void close( void );
                
                void send( const core::Bytes body,
                           const std::function< void ( const std::shared_ptr< WebSocket > ) > success = nullptr,
                           const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > failure = nullptr );
                           
                void send( const OperationCode code,
                           const std::function< void ( const std::shared_ptr< WebSocket > ) > success = nullptr,
                           const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > failure = nullptr );
                           
                void send( const std::shared_ptr< WebSocketMessage > message,
                           const std::function< void ( const std::shared_ptr< WebSocket > ) > success = nullptr,
                           const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > failure = nullptr );
                //Getters
                const std::shared_ptr< Session > get_session( void ) const;
                
                const std::function< void ( const std::shared_ptr< WebSocket > ) > get_open_handler( void ) const;
                
                const std::function< void ( const std::shared_ptr< WebSocket > ) > get_close_handler( void ) const;
                
                const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > get_error_handler( void ) const;
                
                const std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) > get_message_handler( void ) const;
                
                //Setters
                void set_session( const std::shared_ptr< Session >& value );
                
                void set_open_handler( const std::function< void ( const std::shared_ptr< WebSocket > ) >& value );
                
                void set_close_handler( const std::function< void ( const std::shared_ptr< WebSocket > ) >& value );
                
                void set_error_handler( const std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) >& value );
                
                void set_message_handler( const std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) >& value );
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                WebSocket( const WebSocket& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                WebSocket& operator =( const WebSocket& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::WebSocketImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_WEB_SOCKET_H */
