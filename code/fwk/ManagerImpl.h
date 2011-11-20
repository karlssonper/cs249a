#ifndef MANAGERIMPL_H
#define MANAGERIMPL_H

#include "Instance.h"
#include "Engine.h"

class ManagerImpl : public Instance::Manager {
    public:

        ManagerImpl(string &name) {
            engineManager_ = Shipping::EngineManager::EngineManagerNew(name);
        }

        Ptr<Instance> instanceNew(const string& name, const string& type);
        Ptr<Instance> instance(const string& name);
        void instanceDel(const string& name);
        Shipping::EngineManager::Ptr engineManager() const { return engineManager_; }
        void engineManagerIs(Shipping::EngineManager::Ptr);

    private:
        ManagerImpl();
        ManagerImpl(const ManagerImpl&);

        map<string,Ptr<Instance> > instance_;
        Shipping::EngineManager::Ptr engineManager_;
    };

#endif
