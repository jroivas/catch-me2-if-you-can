#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE( "Simple test", "[catch]" ) {
    REQUIRE( 2 + 5 == 7 );
}
