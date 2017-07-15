/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_MIDDLEWARE_H
#define _CORVUSOFT_RESTBED_MIDDLEWARE_H 1

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
    namespace core
    {
        class Logger;
        class RunLoop;
        class Settings;
    }
    
    namespace restbed
    {
        //Forward Declarations
        class Session;
        
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
                                               
                virtual void entry( const std::shared_ptr< Session > session ) const = 0;
                
                virtual void exit( const std::shared_ptr< Session > session ) const = 0;
                
                //Getters
                virtual std::string get_name( void ) const = 0;
                
                //Setters
                virtual void set_logger( const std::function< void ( const std::string ) >& value ) = 0;
                
                virtual void set_error_handler( const std::function< void ( const std::error_code ) >& value ) = 0;
                
                virtual void set_continue_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value ) = 0;
                
                virtual void set_terminate_handler( const std::function< void ( const std::shared_ptr< Session >, std::error_code ) >& value ) = 0;
                
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

#endif  /* _CORVUSOFT_RESTBED_MIDDLEWARE_H */
