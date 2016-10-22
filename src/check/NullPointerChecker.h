#pragma once

namespace llvm {
    class LoadInst;
}

class Path;

class NullPointerChecker
{
public:
    void check(llvm::LoadInst* load, Path* path);
};
