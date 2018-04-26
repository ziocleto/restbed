/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
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
    namespace core
    {
        class RunLoop;
        class Settings;
    }
    
    namespace restbed
    {
        //Forward Declarations
        
        class ResourceCache
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                virtual std::error_code teardown( void ) noexcept = 0;
                
                virtual std::error_code setup( const std::shared_ptr< core::RunLoop > runloop,
                                               const std::shared_ptr< const core::Settings > settings ) noexcept = 0;
                                               
                virtual void load( const std::shared_ptr< Session > session,
                                   const std::function< void ( const std::shared_ptr< Session > ) >& success,
                                   const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) >& failure ) noexcept = 0;
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
                ResourceCache( void )
                {
                    return;
                };
                
                virtual ~ResourceCache( void );
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                ResourceCache( const ResourceCache& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                ResourceCache& operator =( const ResourceCache& value ) = delete;
                
                //Properties
        };
    }
}
