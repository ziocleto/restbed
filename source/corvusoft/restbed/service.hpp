/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_SERVICE_H
#define _CORVUSOFT_RESTBED_SERVICE_H 1

//System Includes
#include <set>
#include <chrono>
#include <memory>
#include <string>
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
        class Session;
        class Resource;
        class Settings;
        class Middleware;
        class ResourceCache;
        class SessionManager;
        
        namespace detail
        {
            struct ServiceImpl;
        }
        
        class Service final
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Service( const std::shared_ptr< core::RunLoop >& runloop = nullptr );
                
                virtual ~Service( void );
                
                //Functionality
                bool is_up( void ) const;
                
                bool is_down( void ) const;
                
                bool is_suspended( void ) const;
                
                void resume( void );
                
                void suspend( void );
                
                void stop( void );
                
                std::error_code start( const std::shared_ptr< const Settings >& settings = nullptr );
                
                std::error_code publish( const std::shared_ptr< const Resource >& resource );
                
                std::error_code suppress( const std::shared_ptr< const Resource >& resource );
                
                //Getters
                const std::chrono::seconds get_uptime( void ) const;
                
                const std::set< std::string > get_destinations( void ) const;
                
                const std::shared_ptr< core::RunLoop > get_runloop( void ) const;
                
                //Setters
                std::error_code add_middleware( const std::shared_ptr< Middleware >& value );
                
                std::error_code add_network( const std::shared_ptr< network::Socket >& value );
                
                std::error_code add_protocol( const std::shared_ptr< protocol::Protocol >& value );
                
                std::error_code set_default_header( const std::string& name, const std::string& value );
                
                std::error_code set_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                std::error_code add_default_header( const std::string& name, const std::string& value );
                
                std::error_code add_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                std::error_code set_logger( const std::shared_ptr< core::Logger >& value );
                
                std::error_code set_resource_cache( const std::shared_ptr< ResourceCache >& value );
                
                std::error_code set_session_manager( const std::shared_ptr< SessionManager >& value );
                
                std::error_code set_error_handler( const std::function< void ( const std::error_code ) >& value );
                
                std::error_code set_ready_handler( const std::function< void ( void ) >& value );
                
                std::error_code set_signal_handler( const int signal, const std::function< void ( void ) >& value );
                
                std::error_code set_connection_timeout_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
                
                std::error_code set_resource_not_found_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
                
                std::error_code set_method_not_allowed_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
                
                std::error_code set_method_not_implemented_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
                
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
                Service( const Service& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Service& operator =( const Service& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::ServiceImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_SERVICE_H */
