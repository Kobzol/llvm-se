#include "Store.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <util/Logger.h>

#include "expression/ExprBuilder.h"
#include "expression/MemoryLocation.h"
#include "state/StateWrapper.h"
#include "path/Path.h"
#include "util/DebugUtil.h"

void Store::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::StoreInst* st = static_cast<llvm::StoreInst*>(instruction);

    llvm::Value* targetAddr = st->getPointerOperand();
    llvm::Value* source = st->getValueOperand();

    ExprBuilder builder(path->getState());
    Expression* assignment = builder.build(source);

    StateWrapper* state = path->getState();
    StateExprMapping mapping = state->findExpr(targetAddr);

    Expression* target;
    if (state->isLocalState(mapping.getState()))
    {
        target = mapping.getExpr();
    }
    else
    {
        std::unique_ptr<Expression> copy = mapping.getExpr()->clone();
        state->storeGlobalUpdate(targetAddr, mapping.getState(), copy.get());
        state->addExpr(targetAddr, copy.get());
        target = copy.get();
        copy.release();
    }

    assignment->dump(0);
    target->dump(0);

    assert(target->isMemoryLocation());
    static_cast<MemoryLocation*>(target)->setContent(assignment);

    path->moveToNextInstruction();
}
