/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <functional>

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
            //Forward Declarations
            
            struct ResourceImpl
            {
                bool case_sensitivity = false;
                
                std::set< const std::string > paths { };
                
                std::vector< const std::shared_ptr< Middleware > > middleware { };
                
                std::multimap< const std::string, const std::string > default_headers { };
                
                std::multimap< const std::string, const std::function< std::string ( void ) > > dynamic_default_headers { };
                
                std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > error_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< const Request > ) > method_not_implemented_handler = nullptr;
                
                std::map< const std::string, const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< const Request > ) > > method_handlers { };
                
                bool compare( const std::string& lhs, const std::string& rhs ) const
                {
                    return ( case_sensitivity ) ? strcasecmp( lhs.c_str( ), rhs.c_str( ) ) == 0 : lhs == rhs;
                }
                
                static std::string uppercase( const std::string& value )
                {
                    std::string result { };
                    std::transform( value.begin( ), value.end( ), result.begin( ), ::toupper );
                    return result;
                }
            };
        }
    }
}
