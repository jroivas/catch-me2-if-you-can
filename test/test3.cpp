#define CATCH_CONFIG_MAIN
#include "catch.hpp"

bool test1()
{
    throw std::string("a");
    return true;
}

bool test2()
{
    throw "b";
    return true;
}

class B
{};

bool test3()
{
    throw new B();
    return true;
}

bool test4()
{
    throw nullptr;
    return true;
}

TEST_CASE( "Catch error", "[catch]" ) {
    REQUIRE( 1 == 1 );
    CHECK( test1() == true );
    CHECK( test2() == true );
    CHECK( test3() == true );
    CHECK( test4() == true );
}
