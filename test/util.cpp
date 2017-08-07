#include "util.h"

llvm::LLVMContext* llvmCtx = nullptr;
std::unique_ptr<PathGroup> pathGroup;
static std::unique_ptr<ISymbolicState> globalStateHolder;
static std::string FILENAME = "input.cc";

static int intAddr = 100;

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

std::unique_ptr<Context> handleCode(std::string code)
{
    testInit();

    code = "void se_mark(int id = 0);\n" + trim(code);

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
    pathGroup.reset();
    pathGroup = std::make_unique<PathGroup>(context);
    return pathGroup->addPath(std::make_unique<Path>(std::vector<ISymbolicState*>{ globalStateHolder.get() },
                                                     pathGroup.get(),
                                                     function->getFirstInstruction()));
}

std::unique_ptr<Path> createEmptyPath()
{
    return std::make_unique<Path>(std::vector<ISymbolicState*>(), nullptr, nullptr);
}
IntConstant* createInt(ISymbolicState* state, int64_t value)
{
    llvm::Value* address = addr(intAddr++);
    state->addExpr(address, new IntConstant(address, value, 64));
    return static_cast<IntConstant*>(state->getExpr(address));
}

std::string loc(int line)
{
    return FILENAME + ":" + std::to_string(line + 1);
}

bool check_int_eq(Path* path, std::string name, int64_t value)
{
    std::unique_ptr<Solver> solver = path->createSolver();
    path->setConditions(*solver);

    solver->addConstraint(solver->getContext().int_val(
            static_cast<int>(value)) == solver->getContext().int_const(name.c_str()));
    return solver->isSatisfiable();
}

llvm::Value* addr(int i)
{
    return reinterpret_cast<llvm::Value*>(i);
}
