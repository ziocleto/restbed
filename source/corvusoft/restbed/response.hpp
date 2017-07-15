/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_RESPONSE_H
#define _CORVUSOFT_RESTBED_RESPONSE_H 1

//System Includes
#include <map>
#include <string>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/core/byte.hpp>
#include <corvusoft/protocol/message.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    //Forward Declarations
    
    namespace restbed
    {
        //Forward Declarations
        
        class Response final : public protocol::Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Response( const std::string& body );
                
                Response( const core::Bytes& body = { } );
                
                Response( const int status, const std::multimap< const std::string, const std::string >& headers, const std::string& body );
                
                Response( const int status, const std::multimap< const std::string, const std::string >& headers, const core::Bytes& body = { } );
                
                virtual ~Response( void );
                
                //Functionality
                
                //Getters
                
                //Setters
                void set_version( const double value );
                
                void set_status_code( const int value );
                
                void set_protocol( const std::string& protocol );
                
                void set_status_message( const std::string& value );
                
                void set_body( const std::string& value );
                
                void set_body( const core::Bytes& value );
                
                void set_header( const std::string& name, const std::string& value );
                
                void add_header( const std::string& name, const std::string& value );
                
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
                Response( void ) = delete;
                
                Response( const Response& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Response& operator =( const Response& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_RESPONSE_H */
