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

    MemoryLocation* source = state->getMemoryLoc(sourceAddr);
    if (!source->isUndefined() && source->getContent()->isConstant())
    {
        IntConstant* constant = static_cast<IntConstant*>(source->getContent());
        if (constant->getConstant() == 0)
        {
            MemoryLocation* origin = source->getOrigin();
            DebugInfo* di = DebugUtil::get().getDebugInfo(origin->getValue());
            path->getGroup()->getContext()->addError(NullDereferenceError(di));
        }
    }
}
