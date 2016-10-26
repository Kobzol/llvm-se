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
    while (true)
    {
        size_t size = this->paths.size();
        bool stop = true;
        for (size_t i = 0; i < size; i++)
        {
            Path* path = this->paths.at(i).get();
            if (!path->isFinished())
            {
                path->executeInstruction();
                stop = false;
            }
        }

        if (stop) break;
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

void PathGroup::forkPath(Path* path, Expression* condition, llvm::Instruction* instruction)
{
    std::unique_ptr<Path> forked = path->clone();
    forked->addCondition(condition);
    forked->jumpTo(instruction);
    this->paths.push_back(std::move(forked));
}

const std::vector<std::unique_ptr<Path>>& PathGroup::getPaths() const
{
    return this->paths;
}
