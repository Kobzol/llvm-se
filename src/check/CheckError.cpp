#include "CheckError.h"

CheckError::CheckError(CheckErrorType type) : type(type)
{

}

CheckError::CheckError(CheckErrorType type, const DebugInfo* info) : type(type), debugInfo(info)
{

}

CheckErrorType CheckError::getType() const
{
    return this->type;
}

const DebugInfo* CheckError::getDebugInfo() const
{
    return this->debugInfo;
}

NullDereferenceError::NullDereferenceError(const DebugInfo* info) : CheckError(CheckErrorType::NullPointerDereference, info)
{

}

OutOfBoundsError::OutOfBoundsError(const DebugInfo* info) : CheckError(CheckErrorType::OutOfBoundsAccess, info)
{

}

UndefinedLoadError::UndefinedLoadError(const DebugInfo* info) : CheckError(CheckErrorType::UndefinedLoadChecker, info)
{

}
