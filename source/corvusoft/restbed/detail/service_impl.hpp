/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <chrono>
#include <vector>
#include <memory>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/status.hpp>
#include <corvusoft/restbed/session.hpp>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/resource.hpp>
#include <corvusoft/restbed/settings.hpp>
#include <corvusoft/restbed/middleware.hpp>
#include <corvusoft/restbed/resource_cache.hpp>
#include <corvusoft/restbed/session_manager.hpp>

//External Includes
#include <corvusoft/network/adaptor.hpp>
#include <corvusoft/protocol/protocol.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    namespace core
    {
        class RunLoop;
    }
    
    namespace network
    {
        class Socket;
    }
    
    namespace restbed
    {
        //Forward Declarations
        
        namespace detail
        {
            //Forward Declarations
            
            struct ServiceImpl
            {
                std::function< void ( const int, const std::string ) > log_handler = nullptr;
                
                std::shared_ptr< core::RunLoop > runloop = nullptr;
                
                std::shared_ptr< const Settings > settings = nullptr;
                
                std::shared_ptr< ResourceCache > resource_cache = nullptr;
                
                std::shared_ptr< SessionManager > session_manager = nullptr;
                
                std::chrono::steady_clock::time_point uptime = std::chrono::steady_clock::time_point::min( );
                
                std::vector< std::shared_ptr< const Resource > > resources { };
                
                std::vector< std::shared_ptr< Middleware > > middleware { };
                
                std::vector< std::shared_ptr< network::Adaptor > > networks { };
                
                std::vector< std::shared_ptr< protocol::Protocol > > protocols { };
                
                std::multimap< const std::string, const std::string > default_headers { };
                
                std::multimap< const std::string, const std::function< std::string ( void ) > > dynamic_default_headers { };
                
                std::function< void ( void ) > ready_handler = nullptr;
                
                std::function< void ( const std::error_code ) > error_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< Session > ) > resource_not_found_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< Session > ) > method_not_allowed_handler = nullptr;
                
                std::function< void ( const std::shared_ptr< Session > ) > method_not_implemented_handler = nullptr;
                
                std::vector< std::shared_ptr< network::Adaptor > > adaptors { }; //make sure to delete on destroy/timeout.
                
                const std::function< std::error_code ( const std::shared_ptr< network::Adaptor > ) > acceptor = [ this ]( auto adaptor )
                {
                    assert( adaptor not_eq nullptr );
                    
                    //adaptor->set_open_handler( load );
                    adaptor->set_message_handler( load );
                    //adaptor->set_close_handler( std::bind( Protocol::close_handler, protocol ) ); //session->unload( ); adaptors.erase( );
                    //adaptor->set_error_handler( std::bind( Protocol::error_handler, protocol ) );
                    adaptors.push_back( adaptor );
                    
                    return std::error_code( );
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor > ) > load = [ this ]( auto adaptor )
                {
                    // assert( adaptor not_eq nullptr );
                    
                    // std::shared_ptr< protocol::Protocol > protocol = load_protocol( adaptor );
                    
                    // if ( protocol == nullptr )
                    //     return error( std::make_error_code( std::errc::protocol_not_supported ),
                    //                   "Failed to locate appropriate protocol layer, terminating adaptor connection." );
                    
                    // auto session = Session::create( adaptor, protocol );
                    
                    // if ( session_manager == nullptr )
                    // {
                    //     parse( adaptor, session );
                    // }
                    // else
                    // {
                    //     const auto parse_wrapper = [ this ]( auto session )
                    //     {
                    //         parse( session->get_adaptor( ), session );
                    //     };
                    //     session_manager->load( session, parse_wrapper, terminate );
                    // }
                    
                    // adaptor->set_message_handler( std::bind( parse, std::placeholders::_1, session ) );
                };
                
                const std::function< void ( const std::shared_ptr< network::Adaptor >, const std::shared_ptr< Session > ) > parse = [ this ]( auto adaptor, auto session )
                {
                    // assert( adaptor not_eq nullptr );
                    // assert( session not_eq nullptr );
                    
                    // auto protocol = session->get_protocol( );
                    // assert( protocol not_eq nullptr );
                    
                    // auto message = std::make_shared< Request >( ); //we need to set the port of the request.
                    // auto failure = protocol->parse( adaptor, message );
                    
                    // if ( failure )
                    // {
                    //     error( failure, "Protocol failed to parse request." );
                    //     return;
                    // }
                    
                    // session->set_request( message );
                    
                    // if ( middleware.empty( ) )
                    // {
                    //     cache( session );
                    // }
                    // else
                    // {
                    //     middleware.front( )->process( session );
                    // }
                };
                
                const std::function< void ( const std::shared_ptr< Session > ) > cache = [ this ]( auto session )
                {
                    // assert( session not_eq nullptr );
                    
                    // if ( resource_cache == nullptr )
                    // {
                    //     route( session );
                    // }
                    // else
                    // {
                    //     resource_cache->load( session, route, terminate );
                    // }
                };
                
                const std::function< void ( const std::shared_ptr< Session > ) > route = [ this ]( auto session )
                {
                    //force dev to supply bot the /resource and /resource/ paths if they want them.
                    //this allows you to have different behaviour for /resource and /resource/ if you wnat.
                    // assert( session not_eq nullptr );
                    
                    // auto request = session->get_request( );
                    // assert( request not_eq nullptr );
                    
                    // auto path = request->get_path( );
                    // auto root = settings->get_root( );
                    
                    // if ( not root.empty( ) )
                    // {
                    //     if ( path.find( root ) not_eq std::string::npos )
                    //     {
                    //         path.erase( 0, root.length( ) );
                    //     }
                    //     else
                    //     {
                    //         return resource_not_found( session );
                    //     }
                    // }
                    
                    // size_t position = path.find( "//" );
                    
                    // while ( position not_eq std::string::npos )
                    // {
                    //     path.replace( position, 2, "/" );
                    //     position++;
                    // }
                    
                    // std::shared_ptr< const Resource > resource = nullptr;
                    
                    // for ( const auto& asset : resources )
                    //     if ( *asset == path )
                    //     {
                    //         resource = asset;
                    //         break;
                    //     }
                    
                    // if ( resource == nullptr )
                    // {
                    //     return resource_not_found( session );
                    // }
                    
                    // session->set_resource( resource );
                    
                    // auto& middleware = resource->get_middleware( );
                    
                    // if ( middleware.empty( ) )
                    // {
                    //     execute( session );
                    // }
                    // else
                    // {
                    //     middleware.front( )->process( session );
                    // }
                };
                
                const std::function< void ( const std::shared_ptr< Session > ) > execute = [ this ]( auto session )
                {
                    // assert( session not_eq nullptr );
                    
                    // auto request = session->get_request( );
                    // assert( request not_eq nullptr );
                    
                    // auto resource = session->get_resource( );
                    // assert( resource not_eq nullptr );
                    
                    // auto handler = resource->get_method_handler( request->get_method( ) );
                    
                    // ( handler not_eq nullptr ) ? handler( session ) : method_not_found( session );
                };
                
                const std::function< void ( const std::shared_ptr< Session >, std::error_code ) > terminate = [ this ]( auto session, auto code )
                {
                    // assert( session not_eq nullptr );
                    
                    // if ( code or session == nullptr )
                    // {
                    //     return;
                    // }
                    
                    return;
                };
                
                void resource_not_found( const std::shared_ptr< Session > session )
                {
                    // assert( session not_eq nullptr );
                    
                    // if ( resource_not_found_handler not_eq nullptr )
                    // {
                    //     return resource_not_found_handler( session );
                    // }
                    
                    // make_response( NOT_FOUND, session );
                }
                
                void method_not_found( const std::shared_ptr< Session > session )
                {
                    // assert( session  not_eq nullptr );
                    
                    // const auto& request = session->get_request( );
                    // const auto method = request->get_method( );
                    
                    // bool method_supported = false;
                    
                    // for ( const auto& resource : resources )
                    //     if ( resource->has_method_support( method ) )
                    //     {
                    //         method_supported = true;
                    //         break;
                    //     }
                    
                    // if ( method_supported )
                    // {
                    //     method_not_implemented( session );
                    // }
                    // else
                    // {
                    //     method_not_allowed( session );
                    // }
                }
                
                void method_not_allowed( const std::shared_ptr< Session > session )
                {
                    // assert( session not_eq nullptr );
                    
                    // if ( method_not_allowed_handler not_eq nullptr )
                    // {
                    //     return method_not_allowed_handler( session );
                    // }
                    
                    // make_response( METHOD_NOT_ALLOWED, session );
                }
                
                void method_not_implemented( const std::shared_ptr< Session > session )
                {
                    // assert( session not_eq nullptr );
                    
                    // const auto resource = session->get_resource( );
                    // assert( resource not_eq nullptr );
                    
                    // const auto handler = resource->get_method_not_implemented_handler( );
                    
                    // if ( handler not_eq nullptr )
                    // {
                    //     return handler( session );
                    // }
                    
                    // if ( method_not_implemented_handler not_eq nullptr )
                    // {
                    //     return method_not_implemented_handler( session );
                    // }
                    
                    // make_response( NOT_IMPLEMENTED, session );
                }
                
                std::shared_ptr< protocol::Protocol > load_protocol( const std::shared_ptr< network::Adaptor > adaptor )
                {
                    // static std::error_code failure { };
                    
                    // for ( const auto& layer : protocol )
                    // {
                    //     failure = layer->accept( adaptor );
                    
                    //     if ( not failure )
                    //     {
                    //         return layer;
                    //     }
                    //     else if ( failure not_eq std::errc::wrong_protocol_type )
                    //     {
                    //         error( failure, layer->get_name( ) + " protocol layer failed during request triage." );
                    //         break;
                    //     }
                    // }
                    
                    // return nullptr;
                }
                
                void make_response( const int status, const std::shared_ptr< Session > session )
                {
                    // assert( session not_eq nullptr );
                    
                    // std::multimap< const std::string, const std::string > headers = default_headers;
                    
                    // for ( const auto header : dynamic_default_headers )
                    // {
                    //     headers.emplace( header.first, header.second( ) );
                    // }
                    
                    // session->close( status, headers );
                }
                
                void log( const std::string& message, const int severity = 0 )
                {
                    std::error_code error { };
                    
                    //if ( logger not_eq nullptr )
                    //{
                    //error = logger->log_if( not message.empty( ), severity, message );
                    //}
                    
                    //if ( error )
                    //{
                    //    fprintf( stderr, "Logger failed with '%s' when reporting: %s\n", error.message( ).data( ), message.data( ) );
                    //}
                }
                
                std::error_code error( const std::error_code& failure, const std::string& message, const int severity = 1 )
                {
                    // if ( error_handler not_eq nullptr )
                    // {
                    //     error_handler( failure );
                    // }
                    
                    // log( message, severity );
                    // log( failure.message( ), severity );
                    // return failure;
                }
                
                template< typename Type >
                std::error_code initialise_component( Type& component, const std::string&& success_message, const std::string&& failure_message )
                {
                    // assert( component not_eq nullptr );
                    
                    // std::error_code failure = component->setup( runloop, settings );
                    
                    // if ( failure )
                    // {
                    //     error( failure, failure_message );
                    // }
                    // else
                    // {
                    //     log( success_message );
                    // }
                    
                    // return failure;
                }
                
                template< typename Type, typename Arg >
                std::error_code initialise_layer( Arg& layers )
                {
                    // std::error_code failure { };
                    
                    // for ( const auto& layer : layers )
                    // {
                    //     failure = initialise_component( layer, " " + layer->get_name( ) + " layer initialised.", "Failed to initialise " + layer->get_name( ) + " layer." );
                    
                    //     if ( failure )
                    //     {
                    //         return failure;
                    //     }
                    // }
                    
                    // return failure;
                }
            };
        }
    }
}
