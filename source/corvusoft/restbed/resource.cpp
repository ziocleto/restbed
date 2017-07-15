/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/middleware.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"

//External Includes

//System Namespaces
using std::set;
using std::vector;
using std::string;
using std::multimap;
using std::function;
using std::shared_ptr;
using std::error_code;
using std::placeholders::_1;

//Project Namespaces
using corvusoft::restbed::detail::ResourceImpl;

//External Namespaces

namespace corvusoft
{
    namespace restbed
    {
        Resource::Resource( const string& path ) : m_pimpl( new ResourceImpl )
        {
            add_path( path );
        }
        
        Resource::Resource( const set< string >& paths ) : m_pimpl( new ResourceImpl )
        {
            m_pimpl->paths = paths;
        }
        
        Resource::~Resource( void )
        {
            return;
        }
        
        bool Resource::has_method_support( const string& verb ) const
        {
            return m_pimpl->method_handlers.count( verb ) not_eq 0;
        }
        
        const vector< shared_ptr< Middleware > >& Resource::get_middleware_layers( void ) const
        {
            return m_pimpl->middleware_layers;
        }
        
        const multimap< const string, const string > Resource::get_default_headers( void ) const
        {
            multimap< const string, const string > headers = m_pimpl->default_headers;
            
            for ( const auto& header : m_pimpl->dynamic_default_headers )
            {
                headers.emplace( header.first, header.second( ) );
            }
            
            return headers;
        }
        
        const function< void ( const shared_ptr< Session >, const shared_ptr< Request > ) > Resource::get_method_handler( const string& method ) const
        {
            return ( m_pimpl->method_handlers.count( method ) ) ? //method case?
                   m_pimpl->method_handlers.at( method ) :
                   m_pimpl->method_not_implemented_handler;
        }
        
        void Resource::set_path( const string& value )
        {
            m_pimpl->paths.clear( );
            m_pimpl->paths.emplace( value );
        }
        
        void Resource::add_path( const string& value )
        {
            m_pimpl->paths.emplace( value );
        }
        
        void Resource::set_path_case_sensitivity( const bool value )
        {
            m_pimpl->case_sensitivity = value;
        }
        
        void Resource::add_middleware( const shared_ptr< Middleware >& value )
        {
            if ( value == nullptr )
            {
                return;
            }
            
            if ( not m_pimpl->middleware.empty( ) )
            {
                auto& middleware = m_pimpl->middlewareback( );
                middleware->set_continue_handler( bind( &Middleware::process, value, _1 ) );
            }
            
            m_pimpl->middleware.emplace_back( value );
        }
        
        void Resource::set_default_header( const string& name, const string& value )
        {
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            add_default_header( name, value );
        }
        
        void Resource::set_default_header( const string& name, const function< string ( void ) >& value )
        {
            if ( value == nullptr )
            {
                return;
            }
            
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            add_default_header( name, value );
        }
        
        void Resource::add_default_header( const string& name, const string& value )
        {
            m_pimpl->default_headers.emplace( name, value );
        }
        
        void Resource::add_default_header( const string& name, const function< string ( void ) >& value )
        {
            if ( value == nullptr )
            {
                return;
            }
            
            m_pimpl->dynamic_default_headers.emplace( name, value );
        }
        
        void Resource::set_error_handler( const function< void ( const shared_ptr< Session >, const error_code ) >& value )
        {
            m_pimpl->error_handler = value;
        }
        
        void Resource::set_method_not_implemented_handler( const function< void ( const shared_ptr< Session > ) >& value )
        {
            m_pimpl->method_not_implemented_handler = value;
        }
        
        void Resource::set_method_handler( const string& method, const function< void ( const shared_ptr< Session >, const shared_ptr< Response > ) >& callback )
        {
            m_pimpl->method_handlers.emplace( method, callback );
        }
        
        bool Resource::operator==( const string& rhs ) const
        {
            for ( const auto& lhs : m_pimpl->paths )
                if ( m_pimpl->compare( lhs, rhs ) )
                {
                    return true;
                }
                
            return false;
        }
    }
}
