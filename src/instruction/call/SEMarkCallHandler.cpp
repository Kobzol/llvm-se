#include "SEMarkCallHandler.h"

#include <llvm/IR/Instructions.h>

#include "Context.h"
#include "path/Path.h"
#include "path/PathGroup.h"
#include "util/DebugUtil.h"

bool SEMarkCallHandler::shouldHandle(const CallInfo& info) const
{
    return info.getDemangledName() == "se_mark()";
}

void SEMarkCallHandler::handle(const CallInfo& info) const
{
    info.getPath()->getGroup()->getContext()->addError(
            CheckError(CheckErrorType::SEMark, DebugUtil::get().getInstructionLocation(info.getInst()))
    );

    CallHandler::handle(info);
}
