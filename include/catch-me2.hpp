#ifndef __CATCH_ME_TOO_IF_YOU_CAN
#define __CATCH_ME_TOO_IF_YOU_CAN
/* Catch Me2 (if you can)
 *
 * Simple test library compatible with Catch2:
 * https://github.com/catchorg/Catch2
 * Focus on compile speed and compile time memory footprint at cost of features.
 *
 * Copyright (c)2019 Jouni Roivas <jroivas@iki.fi>
 */

#include <iostream>
#include <string>

extern unsigned long __assertions;
extern unsigned long __assertions_failed;

typedef void (TestCase)(void);

// Contains information and implementation about test cases as linked list
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
// Registers TestCase
class TestCases
{
public:
    TestCases(std::string scope, std::string name, TestCase *test) {
        // Add test case to global TestItem linked list
        __rootItem = TestItem::add(
                __rootItem,
                new TestItem(scope + " " +name, test));
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

#define __REQUIRE(X, OX, NAME, EXIT) \
    try {\
        if (!(X)) {\
            std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
            std::cerr << "  " NAME "( " << #OX << " )\n";\
            __assertions_failed++;\
            if (EXIT) return;\
        } else __assertions++;\
    } catch (const char *s) {\
       std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
       std::cerr << "  " NAME "( " << #OX << " )\n";\
       std::cerr << "due to unexpected exception with message:\n";\
       std::cerr << "  " << s << "\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    } catch (std::string s) {\
       std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
       std::cerr << "  " NAME "( " << #OX << " )\n";\
       std::cerr << "due to unexpected exception with message:\n";\
       std::cerr << "  " << s << "\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    } catch (...) {\
       std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
       std::cerr << "  " NAME "( " << #OX << " )\n";\
       std::cerr << "due to unexpected exception with message:\n  Unknown exception\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    }
#define REQUIRE(X) __REQUIRE(X, X, "REQUIRE", true)
#define CHECK(X) __REQUIRE(X, X, "CHECK", false)
#define REQUIRE_FALSE(X) __REQUIRE(!(X), X, "REQUIRE_FALSE", true)
#define CHECK_FALSE(X) __REQUIRE(!(X), X, "CHECK_FALSE", false)

#define __REQUIRE_THROWS(X, NAME, EXIT) \
    try {\
        X;\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  " NAME "( " << #X << " )\n";\
        std::cerr << "because no exception was thrown where one was expected\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    } catch (...) {\
        __assertions++;\
    }
#define REQUIRE_THROWS(X) __REQUIRE_THROWS(X, "REQUIRE_THROWS", true)
#define CHECK_THROWS(X) __REQUIRE_THROWS(X, "CHECK_THROWS", false)

#define __REQUIRE_NOTHROW(X, NAME, EXIT) \
    try {\
        X;\
        __assertions++;\
    } catch (std::string e) {\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  " NAME "( " << #X << " )\n";\
        std::cerr << "due unexpected error with message:\n";\
        std::cerr << "  " << e << "\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    } catch (char *e) {\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  " NAME "( " << #X << " )\n";\
        std::cerr << "due unexpected error with message:\n";\
        std::cerr << "  " << e << "\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    } catch (...) {\
        std::cerr << __FILE__ << ":" << __LINE__ << " FAILED:\n";\
        std::cerr << "  " NAME "( " << #X << " )\n";\
        std::cerr << "due unexpected error:\n";\
        __assertions_failed++;\
        if (EXIT) return;\
    }
#define REQUIRE_NOTHROW(X) __REQUIRE_NOTHROW(X, "REQUIRE_NOTHROW", true)
#define CHECK_NOTHROW(X)  __REQUIRE_NOTHROW(X, "CHECK_NOTHROW", false)


#define REQUIRE_THROWS_AS(X, E) std::cout << "ERROR: Unimplemented: REQUIRE_THROWS_AS\n";
#define CHECK_THROWS_AS(X, E) std::cout << "ERROR: Unimplemented: CHECK_THROWS_AS\n";

#define REQUIRE_THROWS_WITH(X, E) std::cout << "ERROR: Unimplemented: REQUIRE_THROWS_WITH\n";
#define CHECK_THROWS_WITH(X, E) std::cout << "ERROR: Unimplemented: CHECK_THROWS_WITH\n";

#define REQUIRE_THROWS_MATCHES(X, E, F) std::cout << "ERROR: Unimplemented: REQUIRE_THROWS_MATCHES\n";
#define CHECK_THROWS_MATCHES(X, E, F) std::cout << "ERROR: Unimplemented: CHECK_THROWS_MATCHES\n";


#ifdef CATCH_CONFIG_MAIN
TestItem *__rootItem = nullptr;
unsigned long __assertions = 0;
unsigned long __assertions_failed = 0;

static void report(unsigned long tests, unsigned long pass)
{
    unsigned long failed = tests - pass;
    if (failed) {
        std::cout << "test cases: " << tests;
        if (pass > 0) std::cout << " | " <<  pass << " passed";
        std::cout << " | " << failed << " failed";
        std::cout << "\n";

        std::cout << "assertions: " << (__assertions + __assertions_failed);
        if (__assertions > 0) std::cout << " | " <<  __assertions << " passed";
        std::cout << " | " <<  __assertions_failed << " failed";
        std::cout << "\n";
    } else {
        std::cout << "All tests passed (" <<
            __assertions <<
            " assertions in " << tests <<
            " test case" << (tests > 1 ? "s" : "") << ")\n";
    }
}

static bool __test_runner(bool verbose=false)
{
    static unsigned long tests = 0;
    static unsigned long pass = 0;

    if (__rootItem == nullptr) {
        std::cout << "No tests!\n";
        return false;
    }
    TestItem *item = __rootItem;
    while (item != nullptr) {
        tests++;

        unsigned int pre = __assertions_failed;
        if (verbose) std::cout << "++ " << item->name << "\n";
        item->test();
        if (pre == __assertions_failed) pass++;

        item = item->next;
    }
    report(tests, pass);
    return pass == tests;
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
#endif
