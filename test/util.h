#pragma once

#include "catch.hpp"

#include "Context.h"
#include "expression/IntConstant.h"
#include "path/PathGroup.h"
#include "util/compile/MemoryCompiler.h"

extern llvm::LLVMContext* llvmCtx;
extern PathGroup pathGroup;

void testInit();
std::unique_ptr<Context> handleCode(const std::string& code);
Path* createPath(Context* context, Function* function);
