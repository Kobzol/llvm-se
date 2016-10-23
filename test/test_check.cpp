#include "util.h"

std::string simpleUL = R"(
    void simpleUL()
    {
        int b;
        int a = b;
    }
)";
TEST_CASE("Check detects simple undefined loads") {
    std::unique_ptr<Context> ctx = handleCode(simpleUL);
    Function* fn = ctx->getFunctionByDemangledName("simpleUL");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    const CheckError& error = errors.at(0);
    REQUIRE(error.getType() == CheckErrorType::UndefinedLoad);
    REQUIRE(error.getLocation() == loc(4));
}

std::string transitiveUL = R"(
    void transitiveUL()
    {
        int a;
        int* p = &a;
        int c = *p;
    }
)";
TEST_CASE("Check recognizes transitive undefined loads") {
    std::unique_ptr<Context> ctx = handleCode(transitiveUL);
    Function* fn = ctx->getFunctionByDemangledName("transitiveUL");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);
    REQUIRE(errors.at(0).getType() == CheckErrorType::UndefinedLoad);
    REQUIRE(errors.at(0).getLocation() == loc(5));
}

std::string simpleNull = R"(
    void simpleNull()
    {
        int* b = nullptr;
        int a = *b;
    }
)";
TEST_CASE("Check detects simple null pointer dereferences") {
    std::unique_ptr<Context> ctx = handleCode(simpleNull);
    Function* fn = ctx->getFunctionByDemangledName("simpleNull");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    const CheckError& error = errors.at(0);
    REQUIRE(error.getType() == CheckErrorType::NullPointerDereference);
    REQUIRE(error.getLocation() == loc(4));
}

std::string intZero = R"(
    void intZero()
    {
        int b = 0;
        int a = b;
    }
)";
TEST_CASE("Check doesn't mistake zero integer for nullptr pointer") {
    std::unique_ptr<Context> ctx = handleCode(intZero);
    Function* fn = ctx->getFunctionByDemangledName("intZero");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 0);
}
