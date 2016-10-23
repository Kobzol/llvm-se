#include "Store.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>

#include "expression/ExprBuilder.h"
#include "expression/MemoryLocation.h"
#include "path/Path.h"
#include "util/DebugUtil.h"

void Store::handle(Path* path, llvm::Instruction* instruction)
{
    llvm::StoreInst* st = static_cast<llvm::StoreInst*>(instruction);

    llvm::Value* targetAddr = st->getPointerOperand();
    llvm::Value* source = st->getValueOperand();

    ExprBuilder builder(path->getState());
    Expression* assignment = builder.build(source);
    Expression* target = path->getState()->getExpr(targetAddr);
    assert(target->isMemoryLocation());

    static_cast<MemoryLocation*>(target)->setContent(assignment);

    path->moveToNextInstruction();
}
