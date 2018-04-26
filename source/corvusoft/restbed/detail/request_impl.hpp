/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restbed
    {
        //Forward Declarations
        
        namespace detail
        {
            //Forward Declarations
            
            struct RequestImpl
            {
            
            };
            
            //move to core library for test visibility
            template< typename Type >
            Type filter_fields_by_tag( const std::string& tag, const std::multimap< std::string, core::Bytes >& fields )
            {
                Type values { };
                std::string name { };
                std::string value { };
                
                for ( const auto& field : fields )
                {
                    name = field.first;
                    
                    if ( name.find( tag ) not_eq std::string::npos )
                    {
                        name.erase( 0, tag.length( ) );
                        value.assign( field.second.begin( ), field.second.end( ) );
                        values.emplace( name, value );
                    }
                }
                
                return values;
            }
        }
    }
}
