#include "../util.h"

TEST_CASE("Cloned path should not affect the original")
{
    Path* p1 = createEmptyPath();

    llvm::Value* address = addr(1);
    Expression* var = new Variable(address, 4, new IntConstant(nullptr, 5));
    p1->getState()->addExpr(address, var);

    std::unique_ptr<Path> p2 = p1->clone();
    REQUIRE(p2->getState()->getExpr(address) != var);

    MemoryLocation* varLoc = static_cast<MemoryLocation*>(p2->getState()->getExpr(address));
    varLoc->setContent(new IntConstant(nullptr, 6));

    Expression* content = static_cast<MemoryLocation*>(p1->getState()->getExpr(address))->getContent();
    REQUIRE(static_cast<IntConstant*>(content)->getConstant() == 5);

    content = static_cast<MemoryLocation*>(p2->getState()->getExpr(address))->getContent();
    REQUIRE(static_cast<IntConstant*>(content)->getConstant() == 6);
}

TEST_CASE("Path merge should copy the affected global expressions")
{
    Path* p1 = createEmptyPath();
    p1->getState()->addExpr(addr(1), new Variable(addr(1), 4, new IntConstant(nullptr, 5)));
    ISymbolicState* localState = p1->getState()->getLocalState();

    Path* p2 = new Path(std::vector<ISymbolicState*>{ localState }, nullptr, nullptr);
    p2->getState()->storeGlobalUpdate(addr(1), localState, new IntConstant(nullptr, 6));
    p2->mergeGlobalsTo(p1);

    MemoryLocation* loc = static_cast<MemoryLocation*>(p1->getState()->getExpr(addr(1)));
    REQUIRE(static_cast<IntConstant*>(loc->getContent())->getConstant() == 6);
}