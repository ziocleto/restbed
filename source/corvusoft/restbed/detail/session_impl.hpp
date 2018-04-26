/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <memory>
#include <functional>

//Project Includes
#include "corvusoft/restbed/session_data.hpp"

//External Includes
#include <corvusoft/network/adaptor.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    namespace core
    {
        class RunLoop;
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
                
                std::function< void ( const int, const std::string ) > log_handler = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< network::Adaptor > adaptor = nullptr;
                
                std::shared_ptr< protocol::Protocol > protocol = nullptr;
                
                std::multimap< const std::string, const std::string > default_headers { };
                
                std::multimap< const std::string, const std::function< std::string ( void ) > > dynamic_default_headers { };
                
                const std::function< void ( const std::shared_ptr< Session > session, const std::shared_ptr< network::Adaptor > socket, const std::function< void ( const std::shared_ptr< Session > ) > success ) > success_wrapper = [ ]( auto session, auto adaptor, auto success )
                {
                    assert( adaptor not_eq nullptr );
                    adaptor->close( );
                    
                    if ( success not_eq nullptr )
                    {
                        success( session );
                    }
                };
            };
        }
    }
}
