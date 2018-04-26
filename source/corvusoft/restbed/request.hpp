/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <functional>
#include <type_traits>

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
        
        class Request final : public protocol::Message
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                Request( void );
                
                virtual ~Request( void );
                
                //Functionality
                bool has_header( const std::string& name ) const;
                
                bool has_path_parameter( const std::string& name ) const;
                
                bool has_query_parameter( const std::string& name ) const;
                
                //Getters
                double get_version( void ) const;
                
                core::Bytes get_body( void ) const;
                
                std::string get_path( void ) const;
                
                std::string get_method( void ) const;
                
                std::string get_protocol( void ) const;
                
                std::string get_header( const std::string& name, const std::string& default_value = "" ) const;
                
                std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
                
                std::string get_query_parameter( const std::string& name, const std::string& default_value = "" ) const;
                
                std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "" ) const;
                
                std::string get_path_parameter( const std::string& name, const std::string& default_value = "" ) const;
                
                std::map< std::string, std::string > get_path_parameters( void ) const;
                
                //Setters
                void set_version( const double value );
                
                void set_body( const core::Bytes& value );
                
                void set_body( const std::string& value );
                
                void set_path( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_protocol( const std::string& value );
                
                void set_header( const std::string& name, const std::string& value );
                
                void set_headers( const std::multimap< std::string, std::string >& values );
                
                void set_path_parameter( const std::string& name, const std::string& value );
                
                void set_path_parameters( const std::map< std::string, std::string >& values );
                
                void set_query_parameter( const std::string& name, const std::string& value );
                
                void set_query_parameters( const std::multimap< std::string, std::string >& values );
                
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
                Request( const Request& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                Request& operator =( const Request& value ) = delete;
                
                //Properties
        };
    }
}
