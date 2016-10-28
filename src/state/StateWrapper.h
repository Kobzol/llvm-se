#pragma once

#include <vector>
#include <unordered_map>

#include "ISymbolicState.h"

class Expression;
class Path;

struct StateExprMapping
{
public:
    StateExprMapping();
    StateExprMapping(ISymbolicState* state, Expression* expression);

    bool isValid() const;
    ISymbolicState* getState() const;
    Expression* getExpr() const;

private:
    ISymbolicState* state = nullptr;
    Expression* expression = nullptr;
};

class StateWrapper : public ISymbolicState
{
public:
    StateWrapper(std::vector<ISymbolicState*> states);

    virtual bool hasExpr(llvm::Value* address) const override;
    virtual Expression* getExpr(llvm::Value* address) const override;
    virtual void addExpr(llvm::Value* address, Expression* expression) override;
    StateExprMapping findExpr(llvm::Value* address) const;

    const std::vector<ISymbolicState*>& getStates() const;
    bool isLocalState(ISymbolicState* state) const;
    ISymbolicState* getLocalState() const;

    const std::unordered_map<llvm::Value*, StateExprMapping>& getGlobalUpdates() const;
    void storeGlobalUpdate(llvm::Value* address, ISymbolicState* state, Expression* expression);

    virtual std::unique_ptr<ISymbolicState> clone() override;

    virtual void dump(int priority) override;

private:
    std::unordered_map<llvm::Value*, StateExprMapping> globalUpdates;
    std::vector<ISymbolicState*> states;
};
