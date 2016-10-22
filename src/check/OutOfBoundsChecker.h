#pragma once

#include <cstdint>

namespace llvm {
    class GetElementPtrInst;
}

class MemoryLocation;
class Path;

class OutOfBoundsChecker
{
public:
    void check(llvm::GetElementPtrInst* gep, MemoryLocation* base, int64_t index, Path* path);
};
