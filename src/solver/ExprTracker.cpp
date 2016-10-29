#include "ExprTracker.h"

void ExprTracker::addAddress(llvm::Value* address)
{
    this->addresses.insert(address);
}

const std::unordered_set<llvm::Value*>& ExprTracker::getAddresses() const
{
    return this->addresses;
}
