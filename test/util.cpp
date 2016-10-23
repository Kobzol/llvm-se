#include "util.h"

llvm::LLVMContext* llvmCtx = nullptr;
std::unique_ptr<PathGroup> pathGroup;
static std::unique_ptr<ISymbolicState> globalStateHolder;
static std::string FILENAME = "input.cc";

void testInit()
{
    if (!llvmCtx)
    {
        llvmCtx = &MemoryCompiler::CTX;
    }
}

static std::string trim(const std::string &s)
{
    auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) -> bool { return std::isspace(c) != 0; });
    auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) -> bool { return std::isspace(c) != 0; }).base();
    return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

std::unique_ptr<Context> handleCode(const std::string& code)
{
    testInit();

    std::unique_ptr<llvm::Module> moduleHolder = MemoryCompiler::get().compile(trim(code));
    assert(moduleHolder.get());

    std::unique_ptr<Context> ctx = std::make_unique<Context>();
    ctx->handleModule(moduleHolder.get());

    ctx->keepModule(std::move(moduleHolder));
    globalStateHolder = ctx->createGlobalState(ctx->getActiveModule());

    return ctx;
}

Path* createPath(Context* context, Function* function)
{
    pathGroup.reset();
    pathGroup = std::make_unique<PathGroup>(context);
    return pathGroup->addPath(std::make_unique<Path>(globalStateHolder.get(), function, pathGroup.get()));
}

std::string loc(int line)
{
    return FILENAME + ":" + std::to_string(line);
}