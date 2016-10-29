#include "CheckError.h"

#include "util/Logger.h"

CheckError::CheckError(CheckErrorType type, std::string location) : type(type), location(location)
{

}
CheckError::~CheckError()
{

}

CheckErrorType CheckError::getType() const
{
    return this->type;
}
std::string CheckError::getLocation() const
{
    return this->location;
}

void CheckError::dump(int priority) const
{
    Logger::get().line(priority, "CheckError (type %) at %", static_cast<int>(this->getType()), this->getLocation());
}

NullDereferenceError::NullDereferenceError(std::string location)
        : CheckError(CheckErrorType::NullPointerDereference, location)
{

}

void NullDereferenceError::dump(int priority) const
{
    Logger::get().line(priority, "Null dereference at %", this->getLocation());
}

OutOfBoundsError::OutOfBoundsError(std::string location)
        : CheckError(CheckErrorType::OutOfBoundsAccess, location)
{

}

void OutOfBoundsError::dump(int priority) const
{
    Logger::get().line(priority, "OOB access at %", this->getLocation());
}

UndefinedLoadError::UndefinedLoadError(std::string location)
        : CheckError(CheckErrorType::UndefinedLoad, location)
{

}

void UndefinedLoadError::dump(int priority) const
{
    Logger::get().line(priority, "Undefined load at %", this->getLocation());
}

SEMarkError::SEMarkError(CheckErrorType type, std::string location, int64_t id): CheckError(type, location), id(id)
{

}

int64_t SEMarkError::getId() const
{
    return this->id;
}

void SEMarkError::dump(int priority) const
{
    Logger::get().line(priority, "SEMark at % (id %)", this->getLocation(), this->getId());
}
