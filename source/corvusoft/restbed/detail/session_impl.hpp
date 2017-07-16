/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_DETAIL_SESSION_IMPL_H
#define _CORVUSOFT_RESTBED_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <functional>

//Project Includes
#include "corvusoft/restbed/session_data.hpp"

//External Includes
#include <corvusoft/network/socket.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    namespace core
    {
        class Logger;
        class RunLoop;
    }
    
    namespace network
    {
        class Socket;
    }
    
    namespace protocol
    {
        class Protocol;
    }
    
    namespace restbed
    {
        //Forward Declarations
        class Request;
        class Resource;
        
        namespace detail
        {
            //Forward Declarations
            
            struct SessionImpl
            {
                std::shared_ptr< SessionData > data = nullptr;
                
                std::shared_ptr< const Request > request = nullptr;
                
                std::shared_ptr< const Resource > resource = nullptr;
                
                std::shared_ptr< core::Logger > logger = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< network::Socket > socket = nullptr;
                
                std::shared_ptr< protocol::Protocol > protocol = nullptr;
                
                std::multimap< const std::string, const std::string > default_headers { };
                
                std::multimap< const std::string, const std::function< std::string ( void ) > > dynamic_default_headers { };
                
                const std::function< void ( const std::shared_ptr< Session > session, const std::shared_ptr< network::Socket > socket, const std::function< void ( const std::shared_ptr< Session > ) > success ) > success_wrapper = [ ]( auto session, auto socket, auto success )
                {
                    assert( socket not_eq nullptr );
                    socket->close( );
                    
                    if ( success not_eq nullptr )
                    {
                        success( session );
                    }
                };
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTBED_DETAIL_SESSION_IMPL_H */
