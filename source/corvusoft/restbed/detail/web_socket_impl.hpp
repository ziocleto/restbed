/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

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
