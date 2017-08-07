#!/usr/bin/env bash

CLANG_PATH=$1
BUILD_DIR="cmake-build-debug"

${CLANG_PATH}/bin/clang++ -std=c++11 -static-libgcc -static-libstdc++ -emit-llvm -g -O0 -o ${BUILD_DIR}/test.bc -c input/test.cpp
${CLANG_PATH}/bin/opt -load ./${BUILD_DIR}/libllvmSE.so -se < ${BUILD_DIR}/test.bc
