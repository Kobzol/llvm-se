cmake_minimum_required(VERSION 3.6)
project(clang_test)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CLANG_DIR "/home/kobzol/libraries/llvm3.9-binaries")
set(Z3_DIR "/home/kobzol/libraries/z3/build/build")

set(CMAKE_CXX_COMPILER "${CLANG_DIR}/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++14 -fno-rtti -Wsign-compare -Wall -pedantic -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS")

include_directories(${CLANG_DIR}/include)
link_directories(${CLANG_DIR}/lib)

include_directories(${Z3_DIR}/include)
link_directories(${Z3_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(Z3_LIB z3)
set(CLANG_LIB
        clangCodeGen
        clangFrontend
        clangSerialization
        clangDriver
        clangParse
        clangSema
        clangAnalysis
        clangAST
        clangBasic
        clangEdit
        clangLex
        clangTooling
        LLVMLinker
        LLVMIRReader
        LLVMMIRParser # AsmParser
        LLVMAsmParser
        LLVMBitWriter
        LLVMLTO
        LLVMObjCARCOpts
        LLVMInstrumentation
        LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
        LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
        LLVMX86AsmPrinter # MC, Support, X86Utils
        LLVMX86Info # MC, Support, Target
        LLVMX86Utils # Core, Support
        LLVMipo
        LLVMCoverage
        LLVMProfileData
        LLVMScalarOpts
        LLVMInstCombine
        LLVMCodeGen
        LLVMTransformUtils
        LLVMVectorize
        LLVMAnalysis
        LLVMTarget
        LLVMOption # Support
        LLVMMCParser # MC, Support
        LLVMMCJIT
        LLVMObject # BitReader, Core, Support
        LLVMMC # Object, Support
        LLVMExecutionEngine
        LLVMBitReader # Core, Support
        LLVMCore # Support
        LLVMSupport
        dl
        pthread
)

add_library(src
    src/context.cpp
    src/pass.cpp
    src/path.cpp
    src/expression/ExprBuilder.cpp
    src/instruction/store.cpp
    src/program/declaration.cpp
    src/program/function.cpp
    src/solver/solver.cpp
    src/analysis/Analyser.cpp
    src/util/debug_util.cpp
    src/expression/Expression.cpp
    src/expression/IntConstant.cpp
    src/expression/UnknownExpression.cpp
    src/expression/BinaryExpression.cpp
    src/expression/AddExpression.cpp
    src/instruction/alloca.cpp
    src/util/logger.cpp
    src/expression/LoadExpression.cpp
    src/instruction/branch.cpp
    src/expression/CmpExpression.cpp
    src/expression/MemoryLocation.cpp
        src/expression/Scalar.cpp
    src/util/debug_info.cpp
    src/util/compile/MemoryCompileAction.cpp
    src/util/compile/MemoryCompiler.cpp src/expression/Array.h src/expression/Array.cpp src/instruction/GetElementPtr.cpp src/instruction/GetElementPtr.h src/instruction/InstructionHandler.cpp src/expression/IndexExpression.cpp src/expression/IndexExpression.cpp src/expression/IndexExpression.h)

# LLVM pass
add_library(llvmSE SHARED register_pass.cpp)
target_link_libraries(llvmSE src)
target_link_libraries(llvmSE ${Z3_LIB})

# Test
set(TEST_SOURCE_FILES
        test/run_test.cpp
        test/test_expression.cpp test/util.cpp)

add_executable(unittest ${TEST_SOURCE_FILES})
target_link_libraries(unittest src)
target_link_libraries(unittest ${CLANG_LIB})
target_link_libraries(unittest ${Z3_LIB})