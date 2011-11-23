#ifndef ACTIVITYREACTOR_H
#define ACTIVITYREACTOR_H

#include "ActivityImpl.h"
#include "Activity.h"

class InjectActivityReactor : public Fwk::Activity::Notifiee {
public:
    InjectActivityReactor(
        const string &_name,
        Fwk::Activity::Manager::Ptr _manager, 
        Fwk::Activity::Ptr _activity,
        double _rate);

    void onStatus();

protected:
    double rate_;
    Fwk::Activity::Ptr activity_;
    Fwk::Activity::Manager::Ptr manager_;
};

#endif