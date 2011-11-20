#ifndef BASENOTIFIEE_H
#define BASENOTIFIEE_H

#include "NamedInterface.h"
#include "Debug.h"

namespace Fwk {

    template<typename Notifier>
    class BaseNotifiee  : public NamedInterface{
    public:
        BaseNotifiee(std::string _name, Notifier* n=0) :  Fwk::NamedInterface(_name), notifier_(n) {
            FWK_DEBUG("BaseNotifiee constructor, name " << _name << ", notifier " << n->name());
            if (n) n->notifieeIs(name(), static_cast<typename Notifier::Notifiee*>(this));
            //FWK_DEBUG("BaseNotifiee constructor DONE, name " << _name << ", notifier " << n->name());
        }

        Notifier* notifier() { return notifier_; }

        void notifierIs(Notifier* n) {
            if (notifier_ == n) return;
            if (notifier_) notifier_->notifieeIs(name(), 0);
            notifier_ = n;
            if (n) n->notifieeIs(name(), static_cast<typename Notifier::Notifiee*>(this));
        }

        ~BaseNotifiee() {
            FWK_DEBUG("BaseNotifiee::~BaseNotifiee() with name: " << name());
            if (notifier_) notifier_->notifieeIs(name(), 0);
            //FWK_DEBUG("BaseNotifiee destructor DONE");
        }

    private:
        Notifier* notifier_;

    };

}

#endif
