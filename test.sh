#!/bin/bash

CXX=${CXX:-g++}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BDIR="${DIR}/build"
mkdir -p "${BDIR}"
mkdir -p "${DIR}/catch2"
curl -s "https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp" -o "${DIR}/catch2/catch.hpp"

time $CXX -I"${DIR}/include" "${DIR}/test/test1.cpp" -o "${BDIR}"/test1-catch-me2
time $CXX -I"${DIR}/include" "${DIR}/test/test2a.cpp" "${DIR}/test/test2b.cpp" "${DIR}/test/test2.cpp" -o "${BDIR}"/test2-catch-me2
time $CXX -I"${DIR}/catch2" "${DIR}/test/test1.cpp" -o "${BDIR}"/test1-catch2
time $CXX -I"${DIR}/catch2" "${DIR}/test/test2a.cpp" "${DIR}/test/test2b.cpp" "${DIR}/test/test2.cpp" -o "${BDIR}"/test2-catch2

"${BDIR}"/test1-catch-me2
"${BDIR}"/test2-catch-me2
"${BDIR}"/test1-catch2
