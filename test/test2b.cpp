#include "catch.hpp"





TEST_CASE( "other", "[factorial]" ) {
    REQUIRE( true );
    REQUIRE_THROWS( throw std::string("ff") );
    REQUIRE_NOTHROW( std::string("ff") );
}
