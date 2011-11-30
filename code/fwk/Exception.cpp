#include "Exception.h"

using namespace Fwk;

Exception::~Exception() {
}

Exception::Id Exception::id() {
    return Exception::unknownException_;
}

Exception::Id RangeException::id() {
    return Exception::rangeException_;
}

Exception::Id NameInUseException::id() {
    return Exception::nameInUseException_;
}

Exception::Id MemoryException::id() {
    return Exception::memoryException_;
}

Exception::Id EntityNotFoundException::id() {
    return Exception::entityNotFoundException_;
}