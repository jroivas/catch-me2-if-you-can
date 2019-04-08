#!/bin/bash

CXX=${CXX:-g++}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BDIR="${DIR}/build"
mkdir -p "${BDIR}"
mkdir -p "${DIR}/catch2"
curl -s "https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp" -o "${DIR}/catch2/catch.hpp"

build() {
    echo $@
    shift
    time $@
    echo
}

run() {
    echo "RUN == $1"
    if [ ! -e "$1" ]; then
        echo "MISSING BINARY!"
        exit 1
    fi
    if $@ 2> /dev/null 1> /dev/null; then
        echo " ALL PASSED"
    else
        echo " AT LEAST ONE TEST FAILED"
    fi
}

build "CATCH-ME2" $CXX -I"${DIR}/include" "${DIR}/test/test1.cpp" -o "${BDIR}"/test1-catch-me2
build "CATCH-ME2" $CXX -I"${DIR}/include" "${DIR}/test/test2a.cpp" "${DIR}/test/test2b.cpp" "${DIR}/test/test2.cpp" -o "${BDIR}"/test2-catch-me2
build "CATCH2" $CXX -I"${DIR}/catch2" "${DIR}/test/test1.cpp" -o "${BDIR}"/test1-catch2
build "CATCH2" $CXX -I"${DIR}/catch2" "${DIR}/test/test2a.cpp" "${DIR}/test/test2b.cpp" "${DIR}/test/test2.cpp" -o "${BDIR}"/test2-catch2

build "CATCH-ME2" $CXX -I"${DIR}/include" "${DIR}/test/test3.cpp"  -o "${BDIR}"/test3-catch-me2
build "CATCH2" $CXX -I"${DIR}/catch2" "${DIR}/test/test3.cpp"  -o "${BDIR}"/test3-catch2

build "CATCH-ME2" $CXX -I"${DIR}/include" "${DIR}/test/test4.cpp"  -o "${BDIR}"/test4-catch-me2
build "CATCH2" $CXX -I"${DIR}/catch2" "${DIR}/test/test4.cpp"  -o "${BDIR}"/test4-catch2

run "${BDIR}"/test1-catch-me2
run "${BDIR}"/test2-catch-me2
run "${BDIR}"/test1-catch2

run "${BDIR}"/test3-catch-me2
run "${BDIR}"/test3-catch2

run "${BDIR}"/test4-catch-me2
run "${BDIR}"/test4-catch2
