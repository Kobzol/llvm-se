#pragma once

#include "Path.h"

class PathGroup
{
public:
    void addPath(std::unique_ptr<Path> path);

    void exhaust();

private:
    std::vector<std::unique_ptr<Path>> paths;
};
