#include "util.h"

#include "util/compile/MemoryCompiler.h"

Context CTX;
std::unique_ptr<llvm::Module> moduleHolder;

void handleCode(const std::string& code)
{
    moduleHolder = MemoryCompiler::get().compile(code);
    assert(moduleHolder.get());
    CTX.handleModule(moduleHolder.get());
}
