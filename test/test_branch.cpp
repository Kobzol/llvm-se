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
TEST_CASE("Satisfiable branch is taken and unsatisftiable is ignored") {
    std::unique_ptr<Context> ctx = handleCode(simpleBranch);
    Function* fn = ctx->getFunctionByDemangledName("simpleBranch");
    Path* path = createPath(ctx.get(), fn);
    pathGroup->exhaust();

    REQUIRE(pathGroup->getPaths().size() == 1);

    const std::vector<CheckError>& errors = ctx->getErrors();
    REQUIRE(errors.size() == 1);

    const CheckError& error = errors.at(0);
    REQUIRE(error.getType() == CheckErrorType::SEMark);
    REQUIRE(error.getLocation() == loc(7));
}