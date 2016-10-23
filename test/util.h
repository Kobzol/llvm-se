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
std::unique_ptr<Context> handleCode(const std::string& code);
Path* createPath(Context* context, Function* function);
std::string loc(int line);
