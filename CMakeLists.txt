cmake_minimum_required(VERSION 3.6)
project(clang_test)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CLANG_DIR "/home/kobzol/libraries/llvm3.9-binaries")
set(Z3_DIR "/home/kobzol/libraries/z3/build/build")

set(CMAKE_CXX_COMPILER "${CLANG_DIR}/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -fsanitize=address -fno-omit-frame-pointer -std=c++14 -fno-rtti -Wsign-compare -Wall -pedantic -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS")

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
    src/Context.cpp
    src/Pass.cpp
    src/path/Path.cpp
    src/expression/ExprBuilder.cpp
    src/instruction/Store.cpp
    src/program/Declaration.cpp
    src/program/Function.cpp
    src/solver/Solver.cpp
    src/util/DebugUtil.cpp
    src/expression/Expression.cpp
    src/expression/IntConstant.cpp
    src/expression/UnknownExpression.cpp
    src/expression/BinaryExpression.cpp
    src/expression/AddExpression.cpp
    src/instruction/Alloca.cpp
    src/util/Logger.cpp
    src/expression/LoadExpression.cpp
    src/instruction/Branch.cpp
    src/expression/CmpExpression.cpp
    src/expression/MemoryLocation.cpp
    src/util/DebugInfo.cpp
    src/util/compile/MemoryCompileAction.cpp
    src/util/compile/MemoryCompiler.cpp
    src/instruction/GetElementPtr.cpp
    src/expression/IndexExpression.cpp
    src/state/ISymbolicState.cpp
    src/state/SymbolicState.cpp
    src/state/StateWrapper.cpp
    src/path/PathGroup.cpp
    src/instruction/InstructionDispatcher.cpp
    src/instruction/InstructionHandler.cpp
    src/expression/Variable.cpp
    src/instruction/Return.cpp
    src/check/NullPointerChecker.cpp
    src/check/UndefinedLoadChecker.cpp
    src/check/OutOfBoundsChecker.cpp
    src/instruction/Load.cpp
    src/check/CheckError.cpp
    src/instruction/call/Call.cpp
    src/instruction/call/CallHandler.cpp
    src/instruction/call/LLVMCallHandler.cpp
    src/instruction/call/SEMarkCallHandler.cpp
    src/instruction/call/StandardCallHandler.cpp
)

# LLVM pass
add_library(llvmSE SHARED RegisterPass.cpp)
target_link_libraries(llvmSE src)
target_link_libraries(llvmSE ${Z3_LIB})

# Test
set(TEST_SOURCE_FILES
    test/run_test.cpp
    test/util.cpp
    test/test_path.cpp
    test/test_context.cpp
    test/test_check.cpp
    test/test_branch.cpp
    test/test_call.cpp
    test/unittest/unit_path.cpp
)

add_executable(unittest ${TEST_SOURCE_FILES})
target_link_libraries(unittest src)
target_link_libraries(unittest ${CLANG_LIB})
target_link_libraries(unittest ${Z3_LIB})

# Direct run
set (RUN_SOURCE_FILES
    DirectRun.cpp
)
add_executable(direct ${RUN_SOURCE_FILES})
target_link_libraries(direct src)
target_link_libraries(direct ${CLANG_LIB})
target_link_libraries(direct ${Z3_LIB})
