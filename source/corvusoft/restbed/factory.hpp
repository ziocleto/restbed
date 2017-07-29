/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_FACTORY_H
#define _CORVUSOFT_RESTBED_FACTORY_H 1

//System Includes
#include <memory>

//Project Includes

//External Includes

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
    
    namespace restbed
    {
        //Forward Declarations
        class Service;
        class Session;
        class Request;
        class Response;
        class Resource;
        class WebSocketMessage;
        
        class Factory
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Factory( const std::shared_ptr< core::RunLoop > runloop );
                
                //Functionality
                std::shared_ptr< Session > make_session( void );
                
                std::shared_ptr< Service > make_service( void );
                
                std::shared_ptr< Resource > make_resource( void );
                
                std::shared_ptr< Response > make_response( void );
                
                std::shared_ptr< const Request > make_request( void );
                
                std::shared_ptr< WebSocketMessage > make_web_socket_message( void );
                
                //Getters
                
                //Setters
                
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
                Factory( void ) = delete;
                
                Factory( const Factory& ) = delete;
                
                virtual ~Factory( void ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Factory& operator =( const Factory& ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_FACTORY_H */
