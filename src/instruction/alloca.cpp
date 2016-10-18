#include "alloca.h"

#include <llvm/IR/Instructions.h>
#include <util/logger.h>
#include <util/debug_util.h>
#include <expression/Array.h>
#include <expression/Scalar.h>

#include "path.h"
#include "program/function.h"

void Alloca::handle(Function* function, llvm::Instruction* instruction)
{
    llvm::AllocaInst* alloc = static_cast<llvm::AllocaInst*>(instruction);
    Logger::get().line(Logger::Prio::INFO, "Alloc %", alloc);
    /*Path* path = function->getActivePath();
    DebugInfo* debugInfo = DebugUtil::get().getDebugInfo(instruction);
    llvm::Type* type = alloc->getAllocatedType();

    if (llvm::isa<llvm::ArrayType>(type))
    {
        uint64_t size = alloc->getAllocatedType()->getArrayNumElements();
        path->addAlloc(std::make_shared<Array>(alloc, debugInfo->getName(), size));
    }
    else path->addAlloc(std::make_shared<Scalar>(alloc, debugInfo->getName()));*/
}
