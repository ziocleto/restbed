/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::stod;
using std::string;
using std::function;
using std::multimap;

//Project Namespaces
using corvusoft::restbed::detail::RequestImpl;
using corvusoft::restbed::detail::filter_fields_by_tag;

//External Namespaces
using corvusoft::core::Bytes;
using corvusoft::core::make_bytes;
using corvusoft::core::make_string;
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
            return stod( make_string( get( "request:version" ) ) );
        }
        
        Bytes Request::get_body( void ) const
        {
            return get( "request:body" );
        }
        
        string Request::get_path( void ) const
        {
            return make_string( get( "request:path" ) );
        }
        
        string Request::get_method( void ) const
        {
            return make_string( get( "request:method" ) );
        }
        
        string Request::get_protocol( void ) const
        {
            return make_string( get( "request:protocol" ) );
        }
        
        string Request::get_header( const string& name, const string& default_value ) const
        {
            return make_string( get( "request:header:" + name, make_bytes( default_value ) ) );
        }
        
        multimap< string, string > Request::get_headers( const string& name ) const
        {
            return filter_fields_by_tag< multimap< string, string > >( "request:header:" + name, get( ) );
        }
        
        string Request::get_query_parameter( const string& name, const string& default_value ) const
        {
            return make_string( get( "request:query:" + name, make_bytes( default_value ) ) );
        }
        
        multimap< string, string > Request::get_query_parameters( const string& name ) const
        {
            return filter_fields_by_tag< multimap< string, string > >( "request:query:" + name, get( ) );
        }
        
        string Request::get_path_parameter( const string& name, const string& default_value ) const
        {
            return make_string( get( "request:parameter:" + name, make_bytes( default_value ) ) );
        }
        
        map< string, string > Request::get_path_parameters( ) const
        {
            return filter_fields_by_tag< map< string, string > >( "request:parameter:", get( ) );
        }
        
        void Request::set_version( const double value )
        {
        
        }
        
        void Request::set_body( const Bytes& value )
        {
        
        }
        
        void Request::set_body( const string& value )
        {
        
        }
        
        void Request::set_path( const string& value )
        {
        
        }
        
        void Request::set_method( const string& value )
        {
        
        }
        
        void Request::set_protocol( const string& value )
        {
        
        }
        
        void Request::set_header( const string& name, const string& value )
        {
        
        }
        
        void Request::set_headers( const multimap< string, string >& values )
        {
        
        }
        
        void Request::set_path_parameter( const string& name, const string& value )
        {
        
        }
        
        void Request::set_path_parameters( const map< string, string >& values )
        {
        
        }
        
        void Request::set_query_parameter( const string& name, const string& value )
        {
        
        }
        
        void Request::set_query_parameters( const multimap< string, string >& values )
        {
        
        }
    }
}
