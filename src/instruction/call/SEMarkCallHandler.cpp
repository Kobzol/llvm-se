#include "SEMarkCallHandler.h"

#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "expression/ExprBuilder.h"
#include "expression/IntConstant.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "util/DebugUtil.h"

bool SEMarkCallHandler::shouldHandle(const CallInfo& info) const
{
    return info.getDemangledName() == "se_mark(int)";
}

void SEMarkCallHandler::handle(const CallInfo& info) const
{
    Path* path = info.getPath();
    ExprBuilder builder(path->getState());

    Expression* expr = builder.build(info.getInst()->getArgOperand(0));
    assert(expr->isConstant());
    IntConstant* constant = static_cast<IntConstant*>(expr);

    info.getPath()->getGroup()->getContext()->addError(std::make_unique<SEMarkError>(
            CheckErrorType::SEMark,
            DebugUtil::get().getInstructionLocation(info.getInst()),
            constant->getConstant()
    ));

    CallHandler::handle(info);
}
