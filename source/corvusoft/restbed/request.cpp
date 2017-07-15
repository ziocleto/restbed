/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.hpp"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::uint16_t;
using std::function;
using std::multimap;

//Project Namespaces

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::protocol::Message;

namespace corvusoft
{
    namespace restbed
    {
        Request::Request( void ) : Message( )
        {
            return;
        }
        
        Request::~Request( void )
        {
            return;
        }
        
        bool Request::has_header( const string& name ) const
        {
            return has_property( "header:" + name );
        }
        
        bool Request::has_path_parameter( const string& name ) const
        {
            return has_property( "path:" + name );
        }
        
        bool Request::has_query_parameter( const string& name ) const
        {
            return has_property( "query:" + name );
        }
        
        uint16_t Request::get_port( void ) const
        {
            uint16_t default_value = 0;
            return get_property( "version", default_value );
        }
        
        double Request::get_version( void ) const
        {
            double default_value = 0;
            return get_property( "version", default_value );
        }
        
        const Bytes Request::get_body( void ) const
        {
            static const Bytes default_value { };
            return get_property( "body", default_value );
        }
        
        string Request::get_host( const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "host" );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_path( const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "path" );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_method( const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "method" );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_protocol( const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "protocol" );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_header( const string& name, const string& default_value ) const
        {
            return get_property( "header:" + name, default_value );
        }
        
        string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "header:" + name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        multimap< string, string > Request::get_headers( const string& ) const
        {
            multimap< string, string > headers { };
            
            for ( const auto& header : get_string_properties( ) )
            {
                auto name = header.first;
                const auto position = name.find( "header:" );
                
                if ( position not_eq string::npos )
                {
                    name.erase( 0, 7 );
                    headers.emplace( name, header.second );
                }
            }
            
            return headers;
        }
        
        string Request::get_query_parameter( const string& name, const string& default_value ) const
        {
            return get_property( "query:" + name, default_value );
        }
        
        string Request::get_query_parameter( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "query:" + name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        multimap< string, string > Request::get_query_parameters( const string& ) const
        {
            multimap< string, string > parameters { };
            
            for ( const auto& parameter : get_string_properties( ) )
            {
                auto name = parameter.first;
                const auto position = name.find( "query:" );
                
                if ( position not_eq string::npos )
                {
                    name.erase( 0, 6 );
                    parameters.emplace( name, parameter.second );
                }
            }
            
            return parameters;
        }
        
        string Request::get_path_parameter( const string& name, const string& default_value ) const
        {
            return get_property( "path:" + name, default_value );
        }
        
        string Request::get_path_parameter( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_property( "path:" + name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        map< string, string > Request::get_path_parameters( const string& ) const
        {
            map< string, string > parameters { };
            
            for ( const auto& parameter : get_string_properties( ) )
            {
                auto name = parameter.first;
                const auto position = name.find( "path:" );
                
                if ( position not_eq string::npos )
                {
                    name.erase( 0, 5 );
                    parameters.emplace( name, parameter.second );
                }
            }
            
            return parameters;
        }
    }
}
