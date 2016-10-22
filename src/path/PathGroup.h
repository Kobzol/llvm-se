#pragma once

#include "Path.h"

class PathGroup
{
public:
    Path* addPath(std::unique_ptr<Path> path);

    void exhaust();
    void clear();

private:
    std::vector<std::unique_ptr<Path>> paths;
};
