#include "PathGroup.h"

PathGroup::PathGroup(Context* context) : context(context)
{

}


Path* PathGroup::addPath(std::unique_ptr<Path> path)
{
    this->paths.push_back(std::move(path));
    return this->paths.at(this->paths.size() - 1).get();
}

void PathGroup::exhaust()
{
    Path* path = this->paths[0].get();
    while (!path->isFinished())
    {
        path->executeInstruction();
    }
}

void PathGroup::clear()
{
    this->paths.clear();
}

Context* PathGroup::getContext() const
{
    return this->context;
}
