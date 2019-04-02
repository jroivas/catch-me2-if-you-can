# Catch Me2 (if you can)

Pronounced as: Catch Me too (if you can)

Simple C++ test library, header-only.
Meant to be compatible drop-in replacement for Catch2:
https://github.com/catchorg/Catch2/

Focus on compile speed and compile time memory footprint at cost of features.
Supports basic Catch2 features.


## Why another test framework?

Catch2 is great, but unfortunately it has known issues to be very slow to compile.
They even have dedicated info page for slow compiles:
https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md

Problem is not just slow compiles, but very heavy memory usage.
Simple test with Catch2 can require up to 512MiB memory to be compiled.
Sometimes that's just unacceptable.

### Benchmarks

There's simple test.sh script to compile and run some test cases from test folder.
It prints out the compile times of test with different headers and use cases.
On fairly powerful laptop with 16GiB of memory results are:

Catch Me2 single file test:

    real    0m0,288s
    user    0m0,266s
    sys     0m0,022s


Catch Me2 multi file test:

    real    0m0,681s
    user    0m0,590s
    sys     0m0,090s

Catch2 single file test:

    real    0m7,436s
    user    0m7,165s
    sys     0m0,268s

Catch2 multi file test:

    real    0m8,311s
    user    0m7,943s
    sys     0m0,355s


Compile time for Catch Me2 is fraction of Catch2 compile time,
still providing same results.


## Supported features

- REQUIRE
- CHECK
- REQUIRE_FALSE
- CHECK_FALSE
- REQUIRE_THROWS
- CHECK_THROWS
- REQUIRE_NOTHROW
- CHECK_NOTHROW

Please consult Catch2 documentation about usage:
https://github.com/catchorg/Catch2/blob/master/docs/assertions.md#top
