#include "../util.h"

TEST_CASE("Cloned path should not affect the original")
{
    std::unique_ptr<Path> p1 = createEmptyPath();

    llvm::Value* address = addr(1);
    Variable* var = new Variable(address, 4, createInt(p1->getState(), 5));
    p1->getState()->addExpr(address, var);

    std::unique_ptr<Path> p2 = p1->clone();
    REQUIRE(p2->getState()->getExpr(address) != var);

    MemoryLocation* varLoc = static_cast<MemoryLocation*>(p2->getState()->getExpr(address));
    varLoc->setContent(createInt(p1->getState(), 6));

    Expression* content = static_cast<MemoryLocation*>(p1->getState()->getExpr(address))->getContent();
    REQUIRE(static_cast<IntConstant*>(content)->getConstant() == 5);

    content = static_cast<MemoryLocation*>(p2->getState()->getExpr(address))->getContent();
    REQUIRE(static_cast<IntConstant*>(content)->getConstant() == 6);
}

TEST_CASE("Path merge should copy the affected global expressions")
{
    std::unique_ptr<Path> p1 = createEmptyPath();
    p1->getState()->addExpr(addr(1), new Variable(addr(1), 4, createInt(p1->getState(), 5)));
    ISymbolicState* localState = p1->getState()->getLocalState();

    std::unique_ptr<Path> p2 = std::make_unique<Path>(std::vector<ISymbolicState*>{ localState }, nullptr, nullptr);
    p2->getState()->storeGlobalUpdate(addr(1), localState, createInt(p2->getState(), 6));
    p2->mergeGlobalsTo(p1.get());

    MemoryLocation* loc = static_cast<MemoryLocation*>(p1->getState()->getExpr(addr(1)));
    REQUIRE(static_cast<IntConstant*>(loc->getContent())->getConstant() == 6);
}