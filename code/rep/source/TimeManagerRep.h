#ifndef TIMEMANAGERREP_H
#define TIMEMANAGERREP_H

#include "DeletableInstance.h"

namespace Shipping {
    class EngineManager;
    class TimeManagerRep : public DeletableInstance {
    public:
        TimeManagerRep(const string &_name, Ptr<EngineManager>);
        virtual ~TimeManagerRep() {}
        virtual string attribute(const string &_attribute);
        virtual void attributeIs(const string &_name, const string &_v);
    protected:
        virtual void del(){};
    private:
        TimeManagerRep();
        TimeManagerRep(const TimeManagerRep&);
        Ptr<EngineManager> engineManager_;
    };
}

#endif