/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/status.hpp"
#include "corvusoft/restbed/response.hpp"

//External Includes

//System Namespaces
using std::string;
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
        Response::Response( const string& body ) : Message( )
        {
            set_body( body );
        }
        
        Response::Response( const Bytes& body ) : Message( )
        {
            set_body( body );
        }
        
        Response::Response( const int status, const multimap< const string, const string >& headers, const string& body ) : Response( status, headers, make_bytes( body ) )
        {
            return;
        }
        
        Response::Response( const int status, const multimap< const string, const string >& headers, const Bytes& body ) : Message( )
        {
            set_body( body );
            set_status_code( status );
            
            for ( const auto& header : headers )
            {
                set_header( header.first, header.second );
            }
        }
        
        Response::~Response( void )
        {
            return;
        }
        
        double Response::get_version( void ) const
        {
        
        }
        
        int Response::get_status_code( void ) const
        {
        
        }
        
        string Response::get_status_message( void ) const
        {
        
        }
        
        string Response::get_protocol( void ) const
        {
        
        }
        
        Bytes Response::get_body( void ) const
        {
        
        }
        
        string Response::get_header( const string& name ) const
        {
        
        }
        
        multimap< string, string > Response::get_headers( void ) const
        {
        
        }
        
        void Response::set_version( const double value )
        {
            //set( "version", value );
        }
        
        void Response::set_status_code( const int value )
        {
            //set( "status:code", value );
            //set_status_message( make_status_message( value ) );
        }
        
        void Response::set_status_message( const string& value )
        {
            //set( "status:message", value );
        }
        
        void Response::set_protocol( const string& value )
        {
            //set( "protocol", value );
        }
        
        void Response::set_body( const string& value )
        {
            //set( "body", make_bytes( value ) );
        }
        
        void Response::set_body( const Bytes& value )
        {
            //set( "body", value );
        }
        
        void Response::set_header( const string& name, const string& value )
        {
            //erase( "header:" + name );
            //add_header( name, value );
        }
        
        void Response::set_headers( const multimap< string, string >& values )
        {
            //erase( "header:" + name );
            //add_header( name, value );
        }
    }
}
