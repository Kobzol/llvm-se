#include "util.h"

TEST_CASE("Functions are found and demangled")
{
    std::unique_ptr<Context> ctx = handleCode(R"(
        int testFunction2(int a, int b) { return a + b; }
        int testFunction(int a, int b) { return a + b; }
    )");
    Function* fn = ctx->getFunctionByDemangledName("testFunction");
    REQUIRE(fn);
    REQUIRE(ctx->demangle(fn->getName()) == "testFunction(int, int)");
    REQUIRE(fn->getReturnType() == llvm::Type::getInt32Ty(*llvmCtx));

    const std::vector<Declaration>& params = fn->getParameters();
    REQUIRE(params.size() == 2);

    REQUIRE(params[0].getType() == llvm::Type::getInt32Ty(*llvmCtx));
    REQUIRE(params[1].getType() == llvm::Type::getInt32Ty(*llvmCtx));
}
