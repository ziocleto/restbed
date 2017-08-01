/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _CORVUSOFT_RESTBED_LOG_LEVEL_H
#define _CORVUSOFT_RESTBED_LOG_LEVEL_H 1

//System Includes

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace corvusoft
{
    namespace restbed
    {
        enum LogLevel : int
        {
            INFO     = 0,
            WARNING  = 1,
            ERROR    = 2,
            FATAL    = 3,
            SECURITY = 4
        };
    }
}

#endif  /* _CORVUSOFT_RESTBED_LOG_LEVEL_H */
