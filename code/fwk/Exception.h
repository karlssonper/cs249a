#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <ostream>

namespace Fwk {

    class Exception {
    public:
        enum Id {
            noException_,
            unknownException_,
            rangeException_,
            nameInUseException_,
            memoryException_,
            entityNotFoundException_,
        };
        std::string what() const { return what_; }
        virtual ~Exception();
        virtual Id id();
    protected:
        Exception(const std::string &_str) : what_(_str) {}
        std::string what_;
    };

    std::ostream& operator<<( std::ostream&, Exception const &);

    class RangeException : public Exception {
    public:
        RangeException(const std::string &_what) : Exception(_what) {}
        virtual Id id();
    };

    class NameInUseException : public Exception {
    public:
        NameInUseException(const std::string &_what) : Exception(_what) {}
        virtual Id id();
    };

    class MemoryException : public Exception {
    public:
        MemoryException(const std::string &_what) : Exception(_what) {}
        virtual Id id();
    };

    class EntityNotFoundException : public Exception {
    public:
        EntityNotFoundException(const std::string &_what) : Exception(_what) {}
        virtual Id id();
    };

}


#endif