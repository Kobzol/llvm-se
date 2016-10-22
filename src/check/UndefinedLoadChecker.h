#pragma once

namespace llvm {
    class LoadInst;
}

class Path;

class UndefinedLoadChecker
{
public:
    void check(llvm::LoadInst* load, Path* path);
};