Restbed [![Unix Build Status](https://travis-ci.org/Corvusoft/restbed.svg?branch=master)](https://travis-ci.org/Corvusoft/restbed)
[![Windows Build Status](https://ci.appveyor.com/api/projects/status/75wqogaks13xp817/branch/master?svg=true)](https://ci.appveyor.com/project/corvusoft/restbed/branch/master)
=============================================================================================================================

---

Restbed is a comprehensive and consistent programming model for building applications that require seamless and secure communication over HTTP, with the ability to model a range of business processes, designed to target mobile, tablet, desktop and embedded production environments.

> It's akin to embedding NGINX into your companies own product line. -- Solutions Architect, Bellrock Technology

Example
-------

```C++
#include <memory>
#include <cstdlib>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/session.hpp>
#include <corvusoft/restbed/service.hpp>
#include <corvusoft/restbed/resource.hpp>
#include <corvusoft/restbed/settings.hpp>

using namespace std;
using namespace restbed;

void post_method_handler( const shared_ptr< Session > session, const shared_ptr< Request > request )
{
    const int length = request->get_header( "Content-Length", 0 );

    session->fetch( length, [ ]( const shared_ptr< Session > session, const Bytes & body )
    {
        fprintf( stdout, "%.*s\n", ( int ) body.size( ), body.data( ) );
        session->close( OK, "Hello, World!", { { "Content-Length", "13" } } );
    } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_default_header( "Connection", "close" );
    resource->set_method_handler( "POST", post_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );

    Service service;
    service.set_default_header( "Date", [ ]( ) { return gmtime( ); } );
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
```

Documentation
-------------

The latest Design and API documentation can be located [here](https://github.com/Corvusoft/restbed/tree/master/documentation).

Build
-----

```bash
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake ..
make install
make test
```

You will now find all required components installed in the distribution folder.

Please submit all enhancements, proposals, and defects via the [issue](http://github.com/corvusoft/restbed/issues) tracker; Alternatively ask a question on [StackOverflow](http://stackoverflow.com/questions/ask) tagged [#restbed](http://stackoverflow.com/questions/tagged/restbed).

For Microsoft Visual Studio instructions please see feature [#17](https://github.com/Corvusoft/restbed/issues/17).

License
-------

&copy; 2013-2017 Corvusoft Limited, United Kingdom. All rights reserved.

The Restbed framework is dual licensed; See [LICENSE](LICENSE) for full details.

Support
-------

Please contact sales@corvusoft.co.uk, for support and licensing options, including bespoke software development, testing, design consultation, training, and code review.

Minimum Requirements
--------------------

| Resource | Requirement                                 |
|:--------:|:-------------------------------------------:|
| Compiler |          C++14 compliant or above           |
|    OS    |      BSD, Linux, OSX, Windows, Raspbian     |

Contact
-------

| Method                                      | Description                                 |
|:--------------------------------------------|:--------------------------------------------|
| [Twitter](http://www.twitter.com/corvusoft) | Tweet us your questions & feature requests. |
| support@corvusoft.co.uk                     | Support related queries.                    |
| sales@corvusoft.co.uk                       | Sale related queries.                       |
