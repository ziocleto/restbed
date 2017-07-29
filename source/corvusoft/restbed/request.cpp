/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.hpp"

//External Includes

//System Namespaces
using std::map;
using std::stoi;
using std::stod;
using std::string;
using std::uint16_t;
using std::function;
using std::multimap;

//Project Namespaces

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::protocol::Message;

namespace corvusoft
{
    namespace restbed
    {
        Request::Request( void ) : protocol::Message( )
        {
            return;
        }
        
        Request::~Request( void )
        {
            return;
        }
        
        bool Request::has_header( const string& name ) const
        {
            return has( "request:header:" + name );
        }
        
        bool Request::has_path_parameter( const string& name ) const
        {
            return has( "request:parameter:" + name );
        }
        
        bool Request::has_query_parameter( const string& name ) const
        {
            return has( "request:query:" + name );
        }
        
        double Request::get_version( void ) const
        {
            const auto data = get( "request:version" );
            const string value( data.begin( ), data.end( ) );
            return stod( value );
        }
        
        const Bytes Request::get_body( void ) const
        {
            return get( "request:body", core::make_bytes( ) );
        }
        
        string Request::get_host( const function< string ( const string& ) >& transform ) const
        {
            const auto data = get( "request:host" );
            const string value( data.begin( ), data.end( ) );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_path( const function< string ( const string& ) >& transform ) const
        {
            const auto data = get( "request:path" );
            const string value( data.begin( ), data.end( ) );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_method( const function< string ( const string& ) >& transform ) const
        {
            const auto data = get( "request:method" );
            const string value( data.begin( ), data.end( ) );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_protocol( const function< string ( const string& ) >& transform ) const
        {
            const auto data = get( "request:protocol" );
            const string value( data.begin( ), data.end( ) );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        string Request::get_header( const string& name, const string& default_value ) const
        {
            const auto data = get( "request:header:" + name, make_bytes( default_value ) );
            return string( data.begin( ), data.end( ) );
        }
        
        string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_header( name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        multimap< string, string > Request::get_headers( const string& ) const
        {
            multimap< string, string > headers { };
            
            // for ( const auto& header : get_string_properties( ) )
            // {
            //     auto name = header.first;
            //     const auto position = name.find( "request:header:" );
            
            //     if ( position not_eq string::npos )
            //     {
            //         name.erase( 0, 15 );
            //         headers.emplace( name, header.second );
            //     }
            // }
            
            return headers;
        }
        
        string Request::get_query_parameter( const string& name, const string& default_value ) const
        {
            const auto data = get( "request:query:" + name, make_bytes( default_value ) );
            return string( data.begin( ), data.end( ) );
        }
        
        string Request::get_query_parameter( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_query_parameter( name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        multimap< string, string > Request::get_query_parameters( const string& ) const
        {
            multimap< string, string > parameters { };
            
            // for ( const auto& parameter : get_string_properties( ) )
            // {
            //     auto name = parameter.first;
            //     const auto position = name.find( "request:query:" );
            
            //     if ( position not_eq string::npos )
            //     {
            //         name.erase( 0, 6 );
            //         parameters.emplace( name, parameter.second );
            //     }
            // }
            
            return parameters;
        }
        
        string Request::get_path_parameter( const string& name, const string& default_value ) const
        {
            const auto data = get( "request:parameter:" + name, make_bytes( default_value ) );
            return string( data.begin( ), data.end( ) );
        }
        
        string Request::get_path_parameter( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_path_parameter( name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        map< string, string > Request::get_path_parameters( const string& ) const
        {
            map< string, string > parameters { };
            
            for ( const auto& parameter : get( ) )
            {
                auto name = parameter.first;
                const auto position = name.find( "request:parameter:" );
                
                if ( position not_eq string::npos )
                {
                    name.erase( 0, 18 );
                    parameters.emplace( name, parameter.second );
                }
            }
            
            return parameters;
        }
    }
}
