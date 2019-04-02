#pragma once
/* Catch Me2 (if you can)
 * Simple test library compatible with Catch2
 * Focus on compile speed and compile time memory footprint at cost of features.
 * Copyright (c)2019 Jouni Roivas <jroivas@iki.fi>
 */

#include <iostream>
#include <unordered_map>

static unsigned long __assertions = 0;
static unsigned long __assertions_failed = 0;

typedef void (TestCase)(void);

class TestCases
{
public:
    TestCases(std::string scope, std::string name, TestCase test) {
        std::string scopename = scope + " " +name;
        auto tmp = cases.find(scopename);
        if (tmp != cases.end()) {
            std::string err = "Test case already defined: " + scopename;
            std::cerr << "ERROR: " << err << "\n";
            throw err;
        }
        cases[scopename] = test;
    };
    static std::unordered_map<std::string, TestCase*> cases;
};

#define TEST_CASE_UNIQ_NAME(a) testCase ## a
#define TEST_CASE_UNIQ_OBJ_NAME(a) testCaseObj ## a
#define TEST_CASE_INT_WITH_NAME(DESC, SCOPE, ID, NAME) \
    static void NAME();\
    TestCases TEST_CASE_UNIQ_OBJ_NAME(ID)(SCOPE, DESC, NAME);\
    static void NAME()
#define TEST_CASE_INT(DESC, SCOPE, ID) \
    TEST_CASE_INT_WITH_NAME(DESC, SCOPE, ID, TEST_CASE_UNIQ_NAME(ID))
#define TEST_CASE(DESC, SCOPE) TEST_CASE_INT(DESC, SCOPE, __LINE__)

#define REQUIRE(X) \
    if (!(X)) {\
       std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  REQUIRE( " << #X << " )\n";\
        __assertions_failed++;\
    } else __assertions++;

#define REQUIRE_THROWS(X) \
    try {\
        do { X; } while(0);\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  REQUIRE_THROWS( " << #X << " )\n";\
        std::cerr << "because no exception was thrown where one was expected\n";\
        __assertions_failed++;\
    } catch (...) {\
        __assertions++;\
    }

#define REQUIRE_NOTHROW(X) \
    try {\
        do { X; } while(0);\
        __assertions++;\
    } catch (std::string e) {\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  REQUIRE_NOTHROW( " << #X << " )\n";\
        std::cerr << "due unexpected error with message:\n";\
        std::cerr << "  " << e << "\n";\
        __assertions_failed++;\
    } catch (char *e) {\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  REQUIRE_NOTHROW( " << #X << " )\n";\
        std::cerr << "due unexpected error with message:\n";\
        std::cerr << "  " << e << "\n";\
        __assertions_failed++;\
    } catch (...) {\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  REQUIRE_NOTHROW( " << #X << " )\n";\
        std::cerr << "due unexpected error:\n";\
        __assertions_failed++;\
    }


#ifdef CATCH_CONFIG_MAIN
std::unordered_map<std::string, TestCase*> TestCases::cases;
bool runner(bool verbose=false)
{
    static unsigned long __tests = 0;
    static unsigned long __pass = 0;
    auto iter = TestCases::cases.begin();
    while (iter != TestCases::cases.end()) {
        __tests++;
        unsigned int pre = __assertions_failed;
        if (verbose) std::cout << "++ " << iter->first << "\n";
        iter->second();
        if (pre == __assertions_failed) __pass++;
        iter++;
    }
    unsigned long __failed = __tests - __pass;
    if (__failed) {
        std::cout << "test cases: " << __tests;
        if (__pass > 0) std::cout << " | " <<  __pass << " passed";
        std::cout << " | " <<  __failed << " failed";
        std::cout << "\n";

        std::cout << "assertions: " << (__assertions + __assertions_failed);
        if (__assertions > 0) std::cout << " | " <<  __assertions << " passed";
        std::cout << " | " <<  __assertions_failed << " failed";
        std::cout << "\n";
    } else {
        std::string plural = __tests > 1 ? "s" : "";
        std::cout << "All tests passed (" <<
            __assertions <<
            " assertions in " << __tests <<
            " test case" << plural << ")\n";
    }
    return __pass == __tests;
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    if (!runner()) return 1;
    return 0;
}
#endif
