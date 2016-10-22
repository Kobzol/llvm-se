#include "util.h"

std::string simpleReturn = R"(
    int simpleReturn()
    {
        int a = 5;
        int b = a + a;
        return 5;
    }
)";

TEST_CASE("Path gets simple return value") {
    std::unique_ptr<Context> ctx = handleCode(simpleReturn);
    Function* fn = ctx->getFunctionByDemangledName("simpleReturn");
    Path* path = createPath(ctx.get(), fn);
    pathGroup.exhaust();

    REQUIRE(path->isFinished());
    Expression* expr = path->getReturnValue();
    REQUIRE(expr->isConstant());
    REQUIRE(static_cast<IntConstant*>(expr)->getConstant() == 5);
}
