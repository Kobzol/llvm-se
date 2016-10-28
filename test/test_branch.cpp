#include "util.h"

std::string simpleBranch = R"(
    void simpleBranch()
    {
        int b = 5;
        int c = b + 2;
        if (b + b + 2 > c)
        {
            se_mark();
        }
        else se_mark();
    }
)";
TEST_CASE("Satisfiable branch is taken and unsatisfiable is ignored") {
    std::unique_ptr<Context> ctx = handleCode(simpleBranch);
    Function* fn = ctx->getFunctionByDemangledName("simpleBranch");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    REQUIRE(pathGroup->getPaths().size() == 2);

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 2);

    const CheckError& error = errors.at(0);
    REQUIRE(error.getType() == CheckErrorType::SEMark);

    bool valid = (error.getLocation() == loc(7)) || (error.getLocation() == loc(9));
    REQUIRE(valid);
}

std::string simpleCow = R"(
    void simpleCow(int a)
    {
        int b = 5;
        if (a > 5) b = 6;
        else b = 7;
    }
)";
TEST_CASE("Copy-on-write prevents expression collisions in different paths") {
    std::unique_ptr<Context> ctx = handleCode(simpleCow);
    Function* fn = ctx->getFunctionByDemangledName("simpleCow");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    REQUIRE(pathGroup->getPaths().size() == 2);

    REQUIRE(check_int_eq(path, "b", 7));
    REQUIRE(check_int_eq(pathGroup->getPaths().at(1).get(), "b", 6));
}
