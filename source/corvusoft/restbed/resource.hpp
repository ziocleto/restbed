/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_RESOURCE_H
#define _CORVUSOFT_RESTBED_RESOURCE_H 1

//System Includes
#include <map>
#include <set>
#include <vector>
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
    namespace restbed
    {
        //Forward Declarations
        class Session;
        class Settings;
        class Middleware;
        
        namespace detail
        {
            struct ResourceImpl;
        }
        
        class Resource final
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Resource( const std::string& path = "" );
                
                Resource( const std::set< std::string >& paths );
                
                virtual ~Resource( void );
                
                //Functionality
                bool has_method_support( const std::string& verb ) const;
                
                //Getters
                const std::vector< std::shared_ptr< Middleware > >& get_middleware_layers( void ) const;
                
                const std::multimap< const std::string, const std::string > get_default_headers( void ) const;
                
                const std::function< void ( const std::shared_ptr< Session > ) > get_method_not_implemented_handler( void ) const;
                
                const std::function< void ( const std::shared_ptr< Session > ) > get_method_handler( const std::string& method ) const;
                
                //Setters
                void set_path( const std::string& value );
                
                void add_path( const std::string& value );
                
                void set_path_case_sensitivity( const bool value );
                
                void add_middleware_layer( const std::shared_ptr< Middleware >& value );
                
                void set_default_header( const std::string& name, const std::string& value );
                
                void set_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                void add_default_header( const std::string& name, const std::string& value );
                
                void add_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                void set_error_handler( const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) >& value );
                
                void set_method_handler( const std::string& method, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
                
                void set_method_not_implemented_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
                
                //Operators
                bool operator==( const std::string& rhs ) const;
                
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
                Resource( const Resource& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Resource& operator =( const Resource& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::ResourceImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_RESOURCE_H */
