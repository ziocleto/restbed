/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
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
    namespace core
    {
        class RunLoop;
        class Settings;
    }
    
    namespace restbed
    {
        //Forward Declarations
        class Session;
        class Request;
        class Response;
        
        class Middleware
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                virtual std::error_code teardown( void ) noexcept = 0;
                
                virtual std::error_code setup( const std::shared_ptr< core::RunLoop > runloop,
                                               const std::shared_ptr< const core::Settings > settings ) noexcept = 0;
                                               
                virtual void hook( const std::shared_ptr< Session > session,
                                   const std::shared_ptr< Request > request,
                                   const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Request > ) > success,
                                   const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Response > ) > failure ) const = 0;
                                   
                virtual void hook( const std::shared_ptr< Session > session,
                                   const std::shared_ptr< Response > response,
                                   const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Response > ) > success,
                                   const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Response > ) > failure ) const = 0;
                //Getters
                
                //Setters
                virtual void set_error_handler( const std::function< void ( const std::error_code ) >& value ) = 0;
                
                virtual void set_log_handler( const std::function< void ( const int, const std::string ) >& value ) = 0;
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                Middleware( void )
                {
                    return;
                };
                
                virtual ~Middleware( void );
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                Middleware( const Middleware& ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Middleware& operator =( const Middleware& ) = delete;
                
                //Properties
        };
    }
}
