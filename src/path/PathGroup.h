#pragma once

#include "Path.h"

class Context;

class PathGroup
{
public:
    PathGroup(Context* context);

    Context* getContext() const;

    Path* addPath(std::unique_ptr<Path> path);
    const std::vector<std::unique_ptr<Path>>& getPaths() const;

    void exhaust();
    void clear();

    void forkPath(Path* path, Expression* condition, llvm::Instruction* instruction);

private:
    Context* context;
    std::vector<std::unique_ptr<Path>> paths;
};
