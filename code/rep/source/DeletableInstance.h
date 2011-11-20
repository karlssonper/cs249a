#ifndef DELETABLEINSTANCE_H
#define DELETABLEINSTANCE_H

#include "Instance.h"
#include "ManagerImpl.h"

class DeletableInstance : public Instance {
public:
    DeletableInstance(const string& _name) : Instance(_name) {}
protected:
    virtual void del() = 0;
    friend class Shipping::ManagerImpl;
};

#endif