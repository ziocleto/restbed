/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

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
        class RunLoop;
    }
    
    namespace network
    {
        class Adaptor;
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
                //move complex constructors to a factory. remove nullptr default.
                //remove runloop argument and just use set_runloop.
                //produces clean constructors and a well known default state
                //Service( const std::shared_ptr< core::RunLoop >& runloop = nullptr ); //ref
                Service( void );
                
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
                
                //const std:shared_ptr< core::Settings > get_settings( void ) const; //get access to default setitngs.
                
                //Setters //remove error_code response!
                std::error_code add_middleware( const std::shared_ptr< Middleware >& value );
                
                std::error_code add_network( const std::shared_ptr< network::Adaptor >& value );
                
                std::error_code add_protocol( const std::shared_ptr< protocol::Protocol >& value );
                
                std::error_code set_default_header( const std::string& name, const std::string& value );
                
                std::error_code set_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                std::error_code add_default_header( const std::string& name, const std::string& value );
                
                std::error_code add_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                std::error_code set_log_handler( const std::function< void ( const int, const std::string ) >& value );
                
                std::error_code set_resource_cache( const std::shared_ptr< ResourceCache >& value );
                
                std::error_code set_session_manager( const std::shared_ptr< SessionManager >& value );
                
                std::error_code set_error_handler( const std::function< void ( const std::error_code ) >& value );
                
                std::error_code set_ready_handler( const std::function< void ( void ) >& value );
                
                std::error_code set_signal_handler( const int signal, const std::function< void ( void ) >& value );
                
                std::error_code set_connection_timeout_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
                
                std::error_code set_resource_not_found_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value ); //return error_code from handler? see restless, help people void exceptions.
                
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
