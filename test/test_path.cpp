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
    pathGroup->exhaust();

    REQUIRE(path->isFinished());
    Expression* expr = path->getReturnValue();
    REQUIRE(expr->isConstant());
    REQUIRE(static_cast<IntConstant*>(expr)->getConstant() == 5);
}

std::string simpleUL = R"(
    void simpleUL()
    {
        int b;
        int a = b;
    }
)";
TEST_CASE("Path detects simple undefined loads") {
    std::unique_ptr<Context> ctx = handleCode(simpleUL);
    Function* fn = ctx->getFunctionByDemangledName("simpleUL");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    REQUIRE(path->isFinished());

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    const CheckError& error = errors.at(0);
    REQUIRE(error.getType() == CheckErrorType::UndefinedLoadChecker);
    const DebugInfo* info = error.getDebugInfo();
    REQUIRE(info->getName() == "b");
    REQUIRE(info->getLine() == 3);
}

std::string simpleNull = R"(
    void simpleNull()
    {
        int* b = nullptr;
        int a = *b;
    }
)";
TEST_CASE("Path detects simple null pointer dereferences") {
    std::unique_ptr<Context> ctx = handleCode(simpleNull);
    Function* fn = ctx->getFunctionByDemangledName("simpleNull");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    REQUIRE(path->isFinished());

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    const CheckError& error = errors.at(0);
    REQUIRE(error.getType() == CheckErrorType::NullPointerDereference);
    const DebugInfo* info = error.getDebugInfo();
    REQUIRE(info->getName() == "b");
    REQUIRE(info->getLine() == 3);
}