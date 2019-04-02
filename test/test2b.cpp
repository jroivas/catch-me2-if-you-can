#include "catch.hpp"





// Keep this on line 8 to match one in test2a.cpp
TEST_CASE( "other", "[test]" ) {
    REQUIRE( true );
    CHECK_THROWS(  std::string("ff") );
    CHECK_NOTHROW( throw std::string("ff") );
    REQUIRE_THROWS( throw std::string("ff") );
    REQUIRE_NOTHROW( std::string("ff") );
    CHECK( true );
    REQUIRE_FALSE( false );
}

TEST_CASE( "bail test", "[test]" ) {
    REQUIRE( true );
    CHECK( false );
    REQUIRE( 4 == 5 );
    CHECK( 4 == 3 );
}
