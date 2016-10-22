#include "PathGroup.h"

void PathGroup::addPath(std::unique_ptr<Path> path)
{
    this->paths.push_back(std::move(path));
}

void PathGroup::exhaust()
{
    Path* path = this->paths[0].get();
    while (!path->isFinished())
    {
        path->executeInstruction();
    }
}
