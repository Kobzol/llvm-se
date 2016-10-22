#include "OutOfBoundsChecker.h"

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>

#include "expression/MemoryLocation.h"
#include "util/Logger.h"

void OutOfBoundsChecker::check(llvm::GetElementPtrInst* gep, MemoryLocation* base, int64_t index, Path* path)
{
    llvm::Type* type = base->getValue()->getType()->getContainedType(0);
    uint64_t count = 0;

    if (type->isArrayTy())
    {
        llvm::Type* arrayElemType = type->getArrayElementType();
        count = (arrayElemType->getPrimitiveSizeInBits() / 8) * type->getArrayNumElements();
    }
    else
    {
        count = base->getCount() * (type->getContainedType(0)->getPrimitiveSizeInBits() * 8);
    }

    if (count <= index)
    {
        Logger::get().line(Logger::Prio::ERROR, "Invalid index %", index);
    }
}
