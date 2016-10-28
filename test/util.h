#pragma once

#include "catch.hpp"

#include <cassert>

#include "Context.h"
#include "expression/IntConstant.h"
#include "path/PathGroup.h"
#include "util/compile/MemoryCompiler.h"
#include "util/DebugInfo.h"

extern llvm::LLVMContext* llvmCtx;
extern std::unique_ptr<PathGroup> pathGroup;

void testInit();
std::unique_ptr<Context> handleCode(std::string code);
Path* createPath(Context* context, Function* function);
std::string loc(int line);

bool check_int_eq(Path* path, std::string name, int64_t value);