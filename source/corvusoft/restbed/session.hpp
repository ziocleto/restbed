/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_SESSION_H
#define _CORVUSOFT_RESTBED_SESSION_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/session_data.hpp>

//External Includes
#include <corvusoft/core/byte.hpp>

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
        class Adaptor;
    }
    
    namespace protocol
    {
        class Protocol;
    }
    
    namespace restbed
    {
        //Forward Declarations
        class Request;
        class Response;
        class WebSocket;
        
        namespace detail
        {
            struct SessionImpl;
        }
        
        class Session final : public std::enable_shared_from_this< Session >
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                virtual ~Session( void );
                
                //Functionality
                static std::shared_ptr< Session > create( const std::shared_ptr< network::Adaptor >& socket,
                        const std::shared_ptr< protocol::Protocol >& protocol );
                bool is_open( void ) const;
                
                bool is_closed( void ) const;
                
                void close( const std::shared_ptr< Response >& response = nullptr,
                            const std::function< void ( const std::shared_ptr< Session > ) > success = nullptr,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void close( const std::string body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success = nullptr,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void close( const core::Bytes body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success = nullptr,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void close( const int status,
                            const std::multimap< const std::string, const std::string >& headers = { },
                            const std::function< void ( const std::shared_ptr< Session > ) > success = nullptr,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void close( const int status,
                            const std::multimap< const std::string, const std::string >& headers,
                            const std::string body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success = nullptr,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void close( const int status,
                            const std::multimap< const std::string, const std::string >& headers,
                            const core::Bytes body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success = nullptr,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void yield( const std::shared_ptr< Response >& response,
                            const std::function< void ( const std::shared_ptr< Session > ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void yield( const std::string body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void yield( const core::Bytes body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void yield( const int status,
                            const std::multimap< const std::string, const std::string >& headers,
                            const std::function< void ( const std::shared_ptr< Session > ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void yield( const int status,
                            const std::multimap< const std::string, const std::string >& headers,
                            const std::string body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void yield( const int status,
                            const std::multimap< const std::string, const std::string >& headers,
                            const core::Bytes body,
                            const std::function< void ( const std::shared_ptr< Session > ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void fetch( const std::size_t length,
                            const std::function< void ( const std::shared_ptr< Session >, const core::Bytes ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void fetch( const std::string& delimiter,
                            const std::function< void ( const std::shared_ptr< Session >, const core::Bytes ) > success,
                            const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                            
                void upgrade( const std::shared_ptr< Response >& response,
                              const std::function< void ( const std::shared_ptr< WebSocket > ) >& success,
                              const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                              
                void upgrade( const int status,
                              const std::multimap< const std::string, const std::string >& headers,
                              const std::function< void ( const std::shared_ptr< WebSocket > ) >& success,
                              const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                              
                void upgrade( const int status,
                              const std::multimap< const std::string, const std::string >& headers,
                              const std::string body,
                              const std::function< void ( const std::shared_ptr< WebSocket > ) >& success,
                              const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                              
                void upgrade( const int status,
                              const std::multimap< const std::string, const std::string >& headers,
                              const core::Bytes body,
                              const std::function< void ( const std::shared_ptr< WebSocket > ) >& success,
                              const std::function< void ( const std::shared_ptr< Session >, const std::error_code ) > failure = nullptr );
                              
                //Getters
                const std::string get_origin( void ) const;
                
                const std::string get_destination( void ) const;
                
                const std::shared_ptr< SessionData > get_data( void ) const;
                
                const std::shared_ptr< core::RunLoop > get_runloop( void ) const;
                
                const std::shared_ptr< network::Adaptor > get_adaptor( void ) const;
                
                const std::shared_ptr< protocol::Protocol > get_protocol( void ) const;
                
                //Setters
                void set_data( const std::shared_ptr< SessionData >& value );
                
                void set_default_header( const std::string& name, const std::string& value );
                
                void set_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                void add_default_header( const std::string& name, const std::string& value );
                
                void add_default_header( const std::string& name, const std::function< std::string ( void ) >& value );
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                Session( void ) = delete;
                
                Session( const Session& original ) = delete;
                
                Session( const std::shared_ptr< network::Adaptor >& socket,
                         const std::shared_ptr< protocol::Protocol >& protocol  );
                         
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Session& operator =( const Session& value ) = delete;
                
                //Properties
                std::unique_ptr< detail::SessionImpl > m_pimpl;
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_SESSION_H */
