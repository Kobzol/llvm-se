#include "UndefinedLoadChecker.h"

#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "expression/LoadExpression.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "util/DebugInfo.h"
#include "util/DebugUtil.h"


void UndefinedLoadChecker::check(llvm::LoadInst* load, Path* path)
{
    llvm::Value* sourceAddr = load->getPointerOperand();
    ISymbolicState* state = path->getState();

    assert(state->hasExpr(sourceAddr));
    MemoryLocation* source = static_cast<MemoryLocation*>(state->getExpr(sourceAddr));
    assert(source->isMemoryLocation());

    if (source->isLoad())
    {
        LoadExpression* loadExpr = static_cast<LoadExpression*>(source);
        if (loadExpr->getSource()->getContent()->isMemoryLocation())
        {
            source = static_cast<MemoryLocation*>(loadExpr->getSource()->getContent());
        }
    }

    // if the content of the memloc is undefined, the load is definitely invalid
    if (source->isUndefined())
    {
        path->getGroup()->getContext()->addError(
                std::make_unique<UndefinedLoadError>(DebugUtil::get().getInstructionLocation(load))
        );
    }
}
