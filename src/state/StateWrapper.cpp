#include "StateWrapper.h"

StateExprMapping::StateExprMapping()
{

}
StateExprMapping::StateExprMapping(ISymbolicState* state, Expression* expression)
        : state(state), expression(expression)
{

}

StateExprMapping StateWrapper::findExpr(llvm::Value* address) const
{
    for (ISymbolicState* state : this->states)
    {
        if (state->hasExpr(address))
        {
            return StateExprMapping(state, state->getExpr(address));
        }
    }

    return StateExprMapping();
}

bool StateExprMapping::isValid() const
{
    return this->state != nullptr;
}

ISymbolicState* StateExprMapping::getState() const
{
    return this->state;
}

Expression* StateExprMapping::getExpr() const
{
    return this->expression;
}

StateWrapper::StateWrapper(std::vector<ISymbolicState*> states): states(std::move(states))
{

}

bool StateWrapper::hasExpr(llvm::Value* address) const
{
    return this->findExpr(address).isValid();
}

Expression* StateWrapper::getExpr(llvm::Value* address) const
{
    return this->findExpr(address).getExpr();
}

void StateWrapper::addExpr(llvm::Value* address, Expression* expression)
{
    this->states.back()->addExpr(address, expression);
}

void StateWrapper::dump(int priority)
{

}

const std::vector<ISymbolicState*>& StateWrapper::getStates() const
{
    return this->states;
}

std::unique_ptr<ISymbolicState> StateWrapper::clone()
{
    assert(0);
    return std::unique_ptr<ISymbolicState>();
}

bool StateWrapper::isLocalState(ISymbolicState* state) const
{
    return state == this->getLocalState();
}

void StateWrapper::storeGlobalUpdate(llvm::Value* address, ISymbolicState* state, Expression* expression)
{
    this->globalUpdates[address] = StateExprMapping(state, expression);
}

const std::unordered_map<llvm::Value*, StateExprMapping>& StateWrapper::getGlobalUpdates() const
{
    return this->globalUpdates;
}

ISymbolicState* StateWrapper::getLocalState() const
{
    return this->states.back();
}
