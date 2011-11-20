#ifndef FWK_NAMEDINTERFACE_H
#define FWK_NAMEDINTERFACE_H

#include "PtrInterface.h"

#include <string>

using std::string;

namespace Fwk {

class NamedInterface : public PtrInterface<NamedInterface>
{
public:
	string name() const { return name_; }

    /*
    template <typename Notifier>
    class NotifieeConst : virtual public BaseNotifiee<Notifier> {
    public:
        typedef Fwk::Ptr<NotifieeConst const> PtrConst;
        typedef Fwk::Ptr<NotifieeConst> Ptr;
    };

    template <typename Notifier>
    class Notifiee : virtual public NotifieeConst<Notifier> {
        typedef Fwk::Ptr<Notifiee const> PtrConst;
        typedef Fwk::Ptr<Notifiee> Ptr;
    };
    */
    

protected:
	NamedInterface(const string& name) : name_(name) { }

private:
	string name_;
};

}

#endif
