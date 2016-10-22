#include "util.h"

llvm::LLVMContext* llvmCtx = nullptr;
PathGroup pathGroup;
static std::unique_ptr<ISymbolicState> globalStateHolder;

void testInit()
{
    if (!llvmCtx)
    {
        llvmCtx = &MemoryCompiler::CTX;
    }
}

std::unique_ptr<Context> handleCode(const std::string& code)
{
    testInit();

    std::unique_ptr<llvm::Module> moduleHolder = MemoryCompiler::get().compile(code);
    assert(moduleHolder.get());

    std::unique_ptr<Context> ctx = std::make_unique<Context>();
    ctx->handleModule(moduleHolder.get());

    ctx->keepModule(std::move(moduleHolder));
    globalStateHolder = ctx->createGlobalState(ctx->getActiveModule());

    return ctx;
}

Path* createPath(Context* context, Function* function)
{
    pathGroup.clear();
    return pathGroup.addPath(std::make_unique<Path>(globalStateHolder.get(), function, &pathGroup));
}
