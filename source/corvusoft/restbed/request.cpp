/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::stoi;
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
            return stod( RequestImpl::make_string( get( "request:version" ) ) );
        }
        
        const Bytes Request::get_body( void ) const
        {
            return get( "request:body" );
        }
        
        string Request::get_host( const function< string ( const string& ) >& transform ) const
        {
            return RequestImpl::make_string( get( "request:host" ), transform );
        }
        
        string Request::get_path( const function< string ( const string& ) >& transform ) const
        {
            return RequestImpl::make_string( get( "request:path" ), transform );
        }
        
        string Request::get_method( const function< string ( const string& ) >& transform ) const
        {
            return RequestImpl::make_string( get( "request:method" ), transform );
        }
        
        string Request::get_protocol( const function< string ( const string& ) >& transform ) const
        {
            return RequestImpl::make_string( get( "request:protocol" ), transform );
        }
        
        string Request::get_header( const string& name, const string& default_value ) const
        {
            return RequestImpl::make_string( get( "request:header:" + name, make_bytes( default_value ) ) );
        }
        
        string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_header( name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        multimap< string, string > Request::get_headers( const string& ) const
        {
            return filter_fields_by_tag< multimap< string, string > >( "request:header:", get( ) );
        }
        
        string Request::get_query_parameter( const string& name, const string& default_value ) const
        {
            return RequestImpl::make_string( get( "request:query:" + name, make_bytes( default_value ) ) );
        }
        
        string Request::get_query_parameter( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_query_parameter( name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        multimap< string, string > Request::get_query_parameters( const string& ) const
        {
            return filter_fields_by_tag< multimap< string, string > >( "request:query:", get( ) );
        }
        
        string Request::get_path_parameter( const string& name, const string& default_value ) const
        {
            return RequestImpl::make_string( get( "request:parameter:" + name, make_bytes( default_value ) ) );
        }
        
        string Request::get_path_parameter( const string& name, const function< string ( const string& ) >& transform ) const
        {
            const string value = get_path_parameter( name );
            return ( transform == nullptr ) ? value : transform( value );
        }
        
        map< string, string > Request::get_path_parameters( const string& ) const
        {
            return filter_fields_by_tag< map< string, string > >( "request:parameter:", get( ) );
        }
    }
}
