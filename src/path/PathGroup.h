#pragma once

#include "Path.h"

class Context;

class PathGroup
{
public:
    PathGroup(Context* context);

    Context* getContext() const;

    Path* addPath(std::unique_ptr<Path> path);

    void exhaust();
    void clear();

private:
    Context* context;
    std::vector<std::unique_ptr<Path>> paths;
};
