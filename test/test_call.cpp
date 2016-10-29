#include "util.h"

std::string simpleArgSub = R"(
    int test(int b) { return b; }
    void simpleArgSub()
    {
        int a = test(5);
        if (a == 5) se_mark();
    }
)";
TEST_CASE("Arguments are substituted with actual parameters")
{
    std::unique_ptr<Context> ctx = handleCode(simpleArgSub);
    Function* fn = ctx->getFunctionByDemangledName("simpleArgSub");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();
    REQUIRE(path->isFinished());

    REQUIRE(ctx->getErrors().size() == 1);
    REQUIRE(ctx->getErrors().at(0)->getLocation() == loc(5));
}

std::string simpleCall = R"(
    int test() { return 5; }
    void simpleCall()
    {
        int a = test();
        if (a == 5) se_mark();
    }
)";
TEST_CASE("Simple return values are transferred to the call site")
{
    std::unique_ptr<Context> ctx = handleCode(simpleCall);
    Function* fn = ctx->getFunctionByDemangledName("simpleCall");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();
    REQUIRE(path->isFinished());

    REQUIRE(ctx->getErrors().size() == 1);
    REQUIRE(ctx->getErrors().at(0)->getLocation() == loc(5));
}

std::string returnAndSub = R"(
    int test(int b)
    {
        if (b == 2) return 1;
        else return 2;
    }
    void returnAndSub()
    {
        int a = test(2);
        if (a == 1) se_mark();

        a = 6;
    }
)";
TEST_CASE("Return values work with substitutions")
{
    std::unique_ptr<Context> ctx = handleCode(returnAndSub);
    Function* fn = ctx->getFunctionByDemangledName("returnAndSub");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();
    REQUIRE(path->isFinished());

    REQUIRE(pathGroup->getPaths().size() == 1); // no additional path was created, because a must be 1

    REQUIRE(ctx->getErrors().size() == 1);
    REQUIRE(ctx->getErrors().at(0)->getLocation() == loc(9));
}
