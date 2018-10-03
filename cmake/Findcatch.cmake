find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/catch/single_include" "/usr/include/catch2/single_include" "/usr/local/include/catch2/single_include" "/opt/local/include/catch2/single_include" "/usr/local/include/catch)

if ( catch_INCLUDE )
    set( CATCH_FOUND TRUE )

    message( STATUS "Found Catch include at: ${catch_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate Catch dependency." )
endif ( )
