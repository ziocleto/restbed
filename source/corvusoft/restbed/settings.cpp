/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/settings.hpp"

//External Includes

//System Namespaces
using std::string;
using std::uint16_t;
using std::chrono::milliseconds;

//Project Namespaces

//External Namespaces
using corvusoft::core::Settings;

namespace corvusoft
{
    namespace restbed
    {
        Settings::Settings( void ) : core::Settings( )
        {
            return;
        }
        
        Settings::~Settings( void )
        {
            return;
        }
        
        uint16_t Settings::get_port( void ) const
        {
            return get( "port", 80 );
        }
        
        string Settings::get_root( void ) const
        {
            return get( "root", "/" );
        }
        
        string Settings::get_bind_address( void ) const
        {
            return get( "bind:address" );
        }
        
        unsigned int Settings::get_connection_limit( void ) const
        {
            return get( "connection:limit", 0 );
        }
        
        milliseconds Settings::get_connection_timeout( void ) const
        {
            return milliseconds( get( "connection:timeout", 10000 ) );
        }
        
        void Settings::set_port( const uint16_t value )
        {
            set( "port", value );
        }
        
        void Settings::set_root( const string& value )
        {
            set( "root", value );
        }
        
        void Settings::set_bind_address( const string& value )
        {
            set( "bind:address", value );
        }
        
        void Settings::set_connection_limit( const unsigned int value )
        {
            set( "connection:limit", value );
        }
        
        void Settings::set_connection_timeout( const milliseconds& value )
        {
            set( "connection:timeout", value.count( ) );
        }
    }
}
