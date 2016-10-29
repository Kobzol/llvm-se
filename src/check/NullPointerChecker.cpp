#include "NullPointerChecker.h"

#include <memory>
#include <llvm/IR/Instructions.h>
#include <expression/LoadExpression.h>

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

    if (source->isLoad())
    {
        LoadExpression* loadExpr = static_cast<LoadExpression*>(source);
        MemoryLocation* pointer = loadExpr->getSource();
        if (!pointer->isUndefined() && pointer->getContent()->isConstant())
        {
            IntConstant* constant = static_cast<IntConstant*>(pointer->getContent());
            if (constant->getConstant() == 0)
            {
                path->getGroup()->getContext()->addError(
                        std::make_unique<NullDereferenceError>(DebugUtil::get().getInstructionLocation(load))
                );
            }
        }
    }
}
