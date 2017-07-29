Description
-----------

Middleware presents an opportunity for interacting with an incoming request and/or out-going response
before and/or after interacting with the core business logic contained within a method handler.

Middleware promotes the development of small concise chunks of code that can be tested and reused across many server codebases.
Increasing clean design, testability, reliability, readability and software maintaince.

It is an ideal approach to header validation, de/compressing data, authentication, logging and other fundamental networked API requirements.

[gzip middleware]    [content-type middleware]    [method handler]
       |                          |                      |
       |--+                       |                      |
       |  |                       |                      |
       |  | request hook          |                      |
       |  |                       |                      |
       |<-+                       |                      |
       |------------------------->|                      |
       |                          |--+                   |
       |                          |  |                   |
       |                          |  | request hook      |
       |                          |  |                   |
       |                          |<-+                   |
       |                          |--------------------->|
       |                          |                      |--+
       |                          |                      |  |
       |                          |                      |  | Method logic
       |                          |                      |  |
       |                          |                      |<-+
       |                          |<---------------------|
       |                          |--+                   |
       |                          |  |                   |
       |                          |  | response hook     |
       |                          |  |                   |
       |                          |<-+                   |
       |<-------------------------|                      |
       |--+                       |                      |
       |  |                       |                      |
       |  | response hook         |                      |
       |  |                       |                      |
       |<-+                       |                      |

Note: Middleware must be thread safe and reentrant.
Note: The order of processing is front-to-back for a request and back-to-front for a response; as shown above; the first middleware added to the service is run first for a request, last for a response.

Design
------

```
+------------------+
|   <<interface>>  |
|    Middleware    |
+------------------+
|                  |
+---------@--------+
          |
          |
          |
 +--------+-------+
 |   <<typedef>>  |
 |      Byte      |
 +----------------+
 |     uint8_t    |
 +----------------+
```

Attributes
----------

None.

Methods
-------

-	[setup](#middlewaresetup)
-	[teardown](#middlewareteardown)
-	[request hook](#middlewarehook)
-	[response hook](#middlewarehook)
-	[set_log_handler](#middlewareset_log_handler)
-	[set_error_handler](#middlewareset_error_handler)

#### Middleware Setup

```C++
 virtual std::error_code setup( const std::shared_ptr< core::RunLoop > runloop,
                                const std::shared_ptr< const core::Settings > settings ) noexcept = 0;
```

Initialisation function for the configuration and setup of a new Middleware instance.  This method will
be invoked once during [restbed::Service](#service) start-up.

If your instance requires lengthy setup such as database, LDAP, or socket connections this is the desired location for such logic.

The parameters passed to this function are the same as those provided to [Service Start](#servicestart).

##### Parameters

|  parameter  | type                           | default value | direction |
|:-----------:|--------------------------------|:-------------:|:---------:|
|   runloop   | [core::RunLoop](#request)      |      n/a      |   input   |
|   settings  | [core::Settings](#response)    |      n/a      |   input   |

##### Return Value

A default error_code (0) is returned on success,
A [std::error_code]() can be returned, which in turn will halt service start and be indicated within the 
error log or stderr if one has not been provided.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Middleware Teardown

```C++
 virtual std::error_code teardown( void ) noexcept = 0;
```

Clean-up function to allow an instance to reclaim any resources it my have acquired during its 
life-cycle i.e closing network, database, LDAP connections, and releasing allocated memory.

##### Parameters

n/a

##### Return Value

A default error_code (0) is returned on success,
A [std::error_code]() can be returned, which in turn will halt service start and be indicated within the 
error log or stderr if one has not been provided.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Middleware Request Hook

```C++
 virtual void hook( const std::shared_ptr< Session > session,
                    const std::shared_ptr< Request > request,
                    const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Request > ) > success,
                    const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Response > ) > failure ) const = 0;
```

 //document these response don't go thru the after hooks because they failed to enter the server logic so are not after.

Clean-up function to allow an instance to reclaim any resources it my have acquired during its 
life-cycle i.e closing network, database, LDAP connections, and releasing allocated memory.

##### Parameters

|  parameter  | type                           | default value | direction |
|:-----------:|--------------------------------|:-------------:|:---------:|
|   session   | [core::RunLoop](#request)      |      n/a      |   input   |
|   request/response  | [core::Settings](#response)    |      n/a      |   input   |
|   success  | [core::Settings](#response)    |      n/a      |   input   |
|   failure  | [core::Settings](#response)    |      n/a      |   input   |

##### Return Value

A default error_code (0) is returned on success,
A [std::error_code]() can be returned, which in turn will halt service start and be indicated within the 
error log or stderr if one has not been provided.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).

#### Middleware Response Hook

```C++
 virtual void hook( const std::shared_ptr< Session > session,
                    const std::shared_ptr< Response > response,
                    const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Response > ) > success,
                    const std::function< void ( const std::shared_ptr< Session >, const std::shared_ptr< Response > ) > failure ) const = 0;
```

 //document these response don't go thru the after hooks because they failed to enter the server logic so are not after.

Clean-up function to allow an instance to reclaim any resources it my have acquired during its 
life-cycle i.e closing network, database, LDAP connections, and releasing allocated memory.

##### Parameters

|  parameter  | type                           | default value | direction |
|:-----------:|--------------------------------|:-------------:|:---------:|
|   session   | [core::RunLoop](#request)      |      n/a      |   input   |
|   response  | [core::Settings](#response)    |      n/a      |   input   |
|   success  | [core::Settings](#response)    |      n/a      |   input   |
|   failure  | [core::Settings](#response)    |      n/a      |   input   |

##### Return Value

A default error_code (0) is returned on success,
A [std::error_code]() can be returned, which in turn will halt service start and be indicated within the 
error log or stderr if one has not been provided.

##### Exceptions

No exceptions allowed specification: [noexcept](http://en.cppreference.com/w/cpp/language/noexcept_spec).
