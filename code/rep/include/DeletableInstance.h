#ifndef DELETABLEINSTANCE_H
#define DELETABLEINSTANCE_H

#include "Instance.h"

class DeletableInstance : public Instance {
public:
    DeletableInstance(const string& _name) : Instance(_name) {}
    virtual void del() = 0;
};

#endif