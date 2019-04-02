#define CATCH_CONFIG_MAIN
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "other", "[test]" ) {
    REQUIRE( true );
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
