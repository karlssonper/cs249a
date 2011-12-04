#ifndef TIMEMANAGERREP_H
#define TIMEMANAGERREP_H

#include "DeletableInstance.h"
#include "VirtualTimeActivityManager.h"
#include "RealTimeActivityManager.h"

namespace Shipping {
    class EngineManager;
    class TimeManagerRep : public DeletableInstance {
    public:
        TimeManagerRep(const string &_name, Ptr<EngineManager>);
        virtual ~TimeManagerRep();
        virtual string attribute(const string &_attribute);
        virtual void attributeIs(const string &_name, const string &_v);
    protected:
        virtual void del(){};
    private:
        TimeManagerRep();
        TimeManagerRep(const TimeManagerRep&);
    };
}

#endif