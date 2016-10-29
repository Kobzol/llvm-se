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

    const std::vector<std::unique_ptr<CheckError>>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    CheckError* error = errors.at(0).get();
    REQUIRE(error->getType() == CheckErrorType::UndefinedLoad);
    REQUIRE(error->getLocation() == loc(4));
}

std::string transitiveUL = R"(
    void transitiveUL()
    {
        int a;
        int* p = &a;
        int** pp = &p;
        int c = *(*pp);
    }
)";
TEST_CASE("Check detects transitive undefined loads") {
    std::unique_ptr<Context> ctx = handleCode(transitiveUL);
    Function* fn = ctx->getFunctionByDemangledName("transitiveUL");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<std::unique_ptr<CheckError>>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);
    REQUIRE(errors.at(0)->getType() == CheckErrorType::UndefinedLoad);
    REQUIRE(errors.at(0)->getLocation() == loc(6));
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

    const std::vector<std::unique_ptr<CheckError>>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    CheckError* error = errors.at(0).get();
    REQUIRE(error->getType() == CheckErrorType::NullPointerDereference);
    REQUIRE(error->getLocation() == loc(4));
}

std::string transitiveNull = R"(
    void transitiveNull()
    {
        int* p = nullptr;
        int** pp = &p;
        int b = *(*pp);
    }
)";
TEST_CASE("Check detects transitive null pointer dereferences") {
    std::unique_ptr<Context> ctx = handleCode(transitiveNull);
    Function* fn = ctx->getFunctionByDemangledName("transitiveNull");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<std::unique_ptr<CheckError>>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);
    REQUIRE(errors.at(0)->getType() == CheckErrorType::NullPointerDereference);
    REQUIRE(errors.at(0)->getLocation() == loc(5));
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

    REQUIRE(ctx->getErrors().size() == 0);
}

std::string simpleIf = R"(
    void simpleIf()
    {
        int b = 5;
        int *p = &b;
        if (*p > 4)
        {
            se_mark();
        }
        if (*p < 4)
        {
            se_mark();
        }
    }
)";
TEST_CASE("Check handles transitive conditions") {
    std::unique_ptr<Context> ctx = handleCode(simpleIf);
    Function* fn = ctx->getFunctionByDemangledName("simpleIf");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    const std::vector<std::unique_ptr<CheckError>>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);
    REQUIRE(errors.at(0)->getType() == CheckErrorType::SEMark);
    REQUIRE(errors.at(0)->getLocation() == loc(7));
}
