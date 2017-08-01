/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes

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

//Project Namespaces
using corvusoft::restbed::detail::ResourceImpl;

//External Namespaces

namespace corvusoft
{
    namespace restbed
    {
        Resource::Resource( const string& path ) : m_pimpl( new ResourceImpl )
        {
            set_path( path );
        }
        
        Resource::Resource( const set< const string >& paths ) : m_pimpl( new ResourceImpl )
        {
            m_pimpl->paths.insert( paths.begin( ), paths.end( ) );
        }
        
        Resource::~Resource( void )
        {
            return;
        }
        
        const Resource::method_handler_t Resource::get_method_handler( const string& method ) const
        {
            const auto verb = ResourceImpl::uppercase( method );
            return ( m_pimpl->method_handlers.count( verb ) ) ? m_pimpl->method_handlers.at( verb ) : m_pimpl->method_not_implemented_handler;
        }
        
        const vector< const shared_ptr< Middleware > > Resource::get_middleware( void ) const
        {
            return m_pimpl->middleware;
        }
        
        const multimap< const string, const string > Resource::get_default_headers( void ) const
        {
            multimap< const string, const string > headers = m_pimpl->default_headers;
            for ( const auto& header : m_pimpl->dynamic_default_headers )
                headers.emplace( header.first, header.second( ) );
                
            return headers;
        }
        
        void Resource::set_path( const string& value )
        {
            m_pimpl->paths.clear( );
            m_pimpl->paths.emplace( value );
        }
        
        void Resource::set_path( const set< const string >& values )
        {
            m_pimpl->paths.insert( values.begin( ), values.end( ) );
        }
        
        void Resource::set_path_case_sensitivity( const bool value )
        {
            m_pimpl->case_sensitivity = value;
        }
        
        void Resource::set_middleware( const shared_ptr< Middleware >& value )
        {
            if ( value == nullptr ) return;
            m_pimpl->middleware.emplace_back( value );
        }
        
        void Resource::set_middleware( const vector< const shared_ptr< Middleware > >& values )
        {
            //m_pimpl->middleware.emplace( m_pimpl->middleware.begin( ),  values );
        }
        
        void Resource::set_default_header( const string& name, const string& value )
        {
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            m_pimpl->default_headers.emplace( name, value );
        }
        
        void Resource::set_default_header( const string& name, const function< string ( void ) >& value )
        {
            if ( value == nullptr ) return;
            m_pimpl->default_headers.erase( name );
            m_pimpl->dynamic_default_headers.erase( name );
            m_pimpl->dynamic_default_headers.emplace( name, value );
        }
        
        void Resource::set_default_headers( const multimap< const string, const string >& values )
        {
            //m_pimpl->default_headers.emplace( m_pimpl->default_headers.begin( ), values );
        }
        
        void Resource::set_method_handler( const string& method, const Resource::method_handler_t& callback )
        {
            if ( callback == nullptr ) return;
            m_pimpl->method_handlers.emplace( ResourceImpl::uppercase( method ), callback );
        }
        
        void Resource::set_method_not_implemented_handler( const Resource::method_handler_t& value )
        {
            m_pimpl->method_not_implemented_handler = value;
        }
        
        void Resource::set_error_handler( const function< void ( const shared_ptr< Session >, const error_code ) >& value )
        {
            m_pimpl->error_handler = value;
        }
        
        bool Resource::operator==( const string& rhs ) const
        {
            for ( const auto& lhs : m_pimpl->paths )
                if ( m_pimpl->compare( lhs, rhs ) )
                    return true;
                    
            return false;
        }
    }
}
