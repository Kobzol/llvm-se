#include "Store.h"

#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <util/Logger.h>

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

    instruction->dump();

    std::unique_ptr<Expression> target = path->getState()->copyExpr(targetAddr);
    path->getState()->addExpr(targetAddr, target.get());
    assert(target->isMemoryLocation());

    static_cast<MemoryLocation*>(target.get())->setContent(assignment);

    path->dump(Logger::DEBUG);

    target.release();

    path->moveToNextInstruction();
}
