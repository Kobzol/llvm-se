#include "path.h"

#include "solver/solver.h"

z3::context Path::CTX;

Path::Path()
{

}

void Path::addAlloc(std::shared_ptr<MemoryLocation> var)
{
    this->variables[var->getValue()] = var;
}
void Path::storeIntoAlloc(llvm::Value* addr, Expression* expr)
{
    assert(this->variables.count(addr));
    this->variables.at(addr)->setContent(expr);
}
bool Path::hasAlloc(llvm::Value* addr) const
{
    return this->variables.count(addr) > 0;
}
Expression* Path::getAlloc(llvm::Value* addr) const
{
    assert(this->hasAlloc(addr));
    return this->variables.at(addr).get();
}

void Path::addExpr(llvm::Value* addr, Expression* expr)
{
    if (this->hasExpr(expr->getValue()))    // the old value is already here, co we copy the shared_ptr
    {
        assert(false);  // cyclic add
        this->exprs[addr] = this->exprs[expr->getValue()];
    }
    else this->exprs[addr] = std::shared_ptr<Expression>(expr); // no old value found, create a new shared_ptr
}
bool Path::hasExpr(llvm::Value* addr) const
{
    return this->exprs.count(addr) > 0;
}
Expression* Path::getExpr(llvm::Value* addr) const
{
    assert(this->hasExpr(addr));
    return this->exprs.at(addr).get();
}

void Path::dump(int priority)
{
    for (auto& expr : this->exprs)
    {
        expr.second->dump(priority);
    }
}

z3::context& Path::getContext()
{
    return Path::CTX;
}

std::unique_ptr<Solver> Path::createSolver()
{
    std::unique_ptr<Solver> solver = std::make_unique<Solver>(&this->getContext());

    for (auto& var : this->variables)
    {
        if (!var.second->isUndefined() && var.second->hasIdentifier())
        {
            z3::expr varName = var.second->createConstraint(this);
            z3::expr varValue = var.second->getContent()->createConstraint(this);
            solver->addConstraint(varName == varValue);
        }
    }

    return solver;
}

void Path::setIndexer(std::shared_ptr<IndexExpression> index)
{
    /*for (auto& existingIndex : this->indices)
    {
       IndexExpression* indexExp = static_cast<IndexExpression*>(existingIndex.second.get());
        if (indexExp->hasSameIndex(index.get()))
        {
            return;
        }
    }

    this->indices[index->getValue()] = index;
    this->exprs*/
}
