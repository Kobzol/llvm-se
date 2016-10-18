#include "MemoryCompiler.h"

#include <clang/Tooling/Tooling.h>

#include "MemoryCompileAction.h"

static llvm::LLVMContext CTX;

MemoryCompiler::MemoryCompiler()
{

}

std::unique_ptr<llvm::Module> MemoryCompiler::compile(std::string code)
{
    std::unique_ptr<llvm::Module> moduleHolder;
    clang::tooling::runToolOnCode(new MemoryCompileAction(&moduleHolder, CTX), code);
    return moduleHolder;
}
