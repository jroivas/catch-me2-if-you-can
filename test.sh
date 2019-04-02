#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
BDIR="${DIR}/build"
mkdir -p "${BDIR}"

time g++ -I"${DIR}/include" "${DIR}/test/test1.cpp" -o "${BDIR}"/test1-catch-me2
time g++ -I"${DIR}/include" "${DIR}/test/test2a.cpp" "${DIR}/test/test2b.cpp" "${DIR}/test/test2.cpp" -o "${BDIR}"/test2-catch-me2
time g++ -I"${DIR}/catch2" "${DIR}/test/test1.cpp" -o "${BDIR}"/test1-catch2
"${BDIR}"/test1-catch-me2
"${BDIR}"/test1-catch2
