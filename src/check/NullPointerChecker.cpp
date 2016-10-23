#include "NullPointerChecker.h"

#include <memory>
#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "expression/IntConstant.h"
#include "util/DebugInfo.h"
#include "util/DebugUtil.h"

void NullPointerChecker::check(llvm::LoadInst* load, Path* path)
{
    ISymbolicState* state = path->getState();
    llvm::Value* sourceAddr = load->getPointerOperand();

    Expression* source = state->getExpr(sourceAddr);

    if (!source->isMemoryLocation() && source->isConstant())
    {
        IntConstant* constant = static_cast<IntConstant*>(source);
        if (constant->getConstant() == 0)
        {
            path->getGroup()->getContext()->addError(NullDereferenceError(DebugUtil::get().getInstructionLocation(load)));
        }
    }
}
