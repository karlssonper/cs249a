#ifndef __ACTIVITY_H__
#define __ACTIVITY_H__

#include <string>
#include "Ptr.h"
#include "NamedInterface.h"
#include "Nominal.h"
#include "BaseNotifiee.h"

using std::string;
namespace Fwk{
/* Define the type 'Time' */
class Time : public Ordinal<Time,double> {
public:
Time() : Ordinal<Time, double>(0.0) {}
    Time(double time) : Ordinal<Time,double>(time)
    {}
};

class Activity : public NamedInterface {
public:
    typedef Fwk::Ptr<Activity> Ptr;

    /* Notifiee class for Activities */
    class Notifiee : public Fwk::BaseNotifiee<Activity> {
    public:
        typedef Fwk::Ptr<Notifiee> Ptr;
        Notifiee(const string &_name, Activity* act)
            : BaseNotifiee<Activity>(_name,act) {}
        virtual void onNextTime() {}
        virtual void onStatus() {}
    };

    //Comparison class for activities
    class Comp : public std::binary_function<Activity::Ptr, Activity::Ptr, bool> {
    public:
        Comp() {}
        bool operator()(Activity::Ptr a, Activity::Ptr b) const {
            return (a->nextTime() > b->nextTime());
        }
    };

    class Manager : public NamedInterface {
    public:
        typedef Fwk::Ptr<Activity::Manager> Ptr;
        virtual Fwk::Ptr<Activity> activityNew(const string &name) = 0;
        virtual Fwk::Ptr<Activity> activity(const string &name) const = 0;
        virtual void activityDel(const string &name) = 0;
        virtual void lastActivityIs(Activity::Ptr) = 0;
        virtual Time now() const = 0;
        virtual void nowIs(Time) = 0;
    protected:
        Manager(const string &name) : NamedInterface(name) {};
    };

    enum Status {
        free, waiting, ready, executing, nextTimeScheduled, deleted
    };
    Activity(const string& name, Fwk::Ptr<class Manager> manager)
        : NamedInterface(name), status_(free), nextTime_(0.0),
          notifiee_(NULL), manager_(manager) {}
    Fwk::Ptr<class Manager> manager() const { return manager_; }
    virtual Status status() const { return status_; }
    virtual void statusIs(Status s) {
        status_ = s;
        if (notifiee_ != NULL) {
            notifiee_->onStatus();
        }
    }
    virtual Time nextTime() const { return nextTime_; }
    virtual void nextTimeIs(Time t) {
        nextTime_ = t;
        if (notifiee_ != NULL) {
            notifiee_->onNextTime();
        }
    }
    virtual Notifiee::Ptr notifiee() const { return notifiee_; }
    virtual void notifieeIs(const string &_name, Notifiee* n) {
        Activity* me = const_cast<Activity*>(this);
        me->notifiee_ = n;
    }

    virtual void lastNotifieeIs(Notifiee* n) {
        Activity* me = const_cast<Activity*>(this);
        me->notifiee_ = n;
    };

protected:
    Activity();
    Activity(const Activity &);
    friend class Manager;
    Status status_;
    Time nextTime_;
    Notifiee* notifiee_;
    Fwk::Ptr<Manager> manager_;
};

} // fwk

#endif
