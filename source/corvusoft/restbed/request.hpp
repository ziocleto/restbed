/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_REQUEST_H
#define _CORVUSOFT_RESTBED_REQUEST_H 1

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
                
                const core::Bytes get_body( void ) const;
                
                std::string get_path( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                std::string get_method( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
                Type get_header( const std::string& name, const Type default_value ) const
                {
                    return default_value;
                }
                
                std::string get_header( const std::string& name, const std::string& default_value ) const;
                
                std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
                
                template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
                Type get_query_parameter( const std::string& name, const Type default_value ) const
                {
                    return default_value;
                }
                
                std::string get_query_parameter( const std::string& name, const std::string& default_value ) const;
                
                std::string get_query_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "" ) const;
                
                template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
                Type get_path_parameter( const std::string& name, const Type default_value ) const
                {
                    return default_value;
                }
                
                std::string get_path_parameter( const std::string& name, const std::string& default_value ) const;
                
                std::string get_path_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
                
                std::map< std::string, std::string > get_path_parameters( const std::string& name = "" ) const;
                
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

#endif  /* _CORVUSOFT_RESTBED_REQUEST_H */
