3rd party developers SHOULD rely on the factory interface.  The underlying objects make change API and therefore
break future applications, require a recompliation.

With forward delcations and pointers this can be avoided. reducing build time and easing any upgrades in the future.

e.g

#include <corvusoft/restbed/factory.hpp>

namespace restbed
{
    class Service;
    class Resource
    class Settings;
};

auto factory = make_shared< Factory >( );
auto service = factory->make_service( );
auto settings = factory->make_settings( map< string, string >( ) );
auto resource = factory->make_resource( );

service->publish( resource );
service->start( settings );
