/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_DETAIL_WEB_SOCKET_IMPL_H
#define _CORVUSOFT_RESTBED_DETAIL_WEB_SOCKET_IMPL_H 1

//System Includes
#include <memory>
#include <functional>
#include <system_error>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restbed
    {
        //Forward Declarations
        class Session;
        class WebSocket;
        class WebSocketMessage;
        
        namespace detail
        {
            //Forward Declarations
            
            struct WebSocketImpl
            {
                std::shared_ptr< Session > session = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket > ) > open_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket > ) > close_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket >, const std::error_code ) > error_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< WebSocket >, const std::shared_ptr< WebSocketMessage > ) > message_handler = nullptr;
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTBED_DETAIL_WEB_SOCKET_IMPL_H */
