/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_DETAIL_RESOURCE_IMPL_H
#define _CORVUSOFT_RESTBED_DETAIL_RESOURCE_IMPL_H 1

//System Includes
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>
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
                
                std::set< std::string > paths { };
                
                std::vector< std::shared_ptr< Middleware > > middleware { };
                
                std::multimap< const std::string, const std::string > default_headers { };
                
                std::multimap< const std::string, const std::function< std::string ( void ) > > dynamic_default_headers { };
                
                std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< const Request > ) > method_not_implemented_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > error_handler = nullptr;
                
                std::map< const std::string, const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< const Request > ) > > method_handlers { };
                
                bool compare( const std::string& lhs, const std::string& rhs ) const
                {
                    assert( not lhs.empty( ) );
                    assert( not rhs.empty( ) );
                    
                    if ( case_sensitivity )
                    {
                        return strcasecmp( lhs.c_str( ), rhs.c_str( ) ) == 0;
                    }
                    else
                    {
                        return lhs == rhs;
                    }
                }
            };
        }
    }
}

#endif  /* _CORVUSOFT_RESTBED_DETAIL_RESOURCE_IMPL_H */
