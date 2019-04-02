#include "catch.hpp"





// Keep this on line 8 to match one in test2a.cpp
TEST_CASE( "other", "[factorial]" ) {
    REQUIRE( true );
    REQUIRE_THROWS( throw std::string("ff") );
    REQUIRE_NOTHROW( std::string("ff") );
    CHECK( true );
}
