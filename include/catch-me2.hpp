#pragma once
/* Catch Me2 (if you can)
 * Simple test library compatible with Catch2
 * Focus on compile speed and compile time memory footprint at cost of features.
 * Copyright (c)2019 Jouni Roivas <jroivas@iki.fi>
 */

#include <iostream>

extern unsigned long __assertions;
extern unsigned long __assertions_failed;

typedef void (TestCase)(void);

class TestItem {
public:
    TestItem(std::string n, TestCase *t) : name(n), test(t), next(nullptr) {}
    static TestItem *add(TestItem *root, TestItem *item) {
        item->next = root;
        return item;
    }

    std::string name;
    TestCase *test;
    TestItem *next;
};

extern TestItem *__rootItem;
class TestCases
{
public:
    TestCases(std::string scope, std::string name, TestCase *test) {
        std::string scopename = scope + " " +name;
        __rootItem = TestItem::add(__rootItem, new TestItem(scopename, test));
    };
};

#define TEST_CASE_UNIQ_NAME(a) testCase ## a
#define TEST_CASE_UNIQ_OBJ_NAME(a) testCaseObj ## a
#define TEST_CASE_INT_WITH_NAME(DESC, SCOPE, ID, NAME) \
    static void NAME();\
    static TestCases TEST_CASE_UNIQ_OBJ_NAME(ID)(SCOPE, DESC, NAME);\
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
TestItem *__rootItem = nullptr;
unsigned long __assertions = 0;
unsigned long __assertions_failed = 0;

static void report(unsigned long __tests, unsigned long __pass)
{
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
}

static bool __test_runner(bool verbose=false)
{
    static unsigned long __tests = 0;
    static unsigned long __pass = 0;

    if (__rootItem == nullptr) {
        std::cout << "No tests!\n";
        return false;
    }
    TestItem *item = __rootItem;
    while (item != nullptr) {
        __tests++;

        unsigned int pre = __assertions_failed;
        if (verbose) std::cout << "++ " << item->name << "\n";
        item->test();
        if (pre == __assertions_failed) __pass++;

        item = item->next;
    }
    report(__tests, __pass);
    return __pass == __tests;
}

int main(int argc, char **argv)
{
    bool verbose = false;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-v") verbose = true;
    }

    if (!__test_runner(verbose)) return 1;
    return 0;
}
#endif
