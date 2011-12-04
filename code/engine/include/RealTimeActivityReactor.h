/*
 * RealTimeActivityReactor.h
 *
 *  Created on: Nov 24, 2011
 *      Author: per
 */

#ifndef REALTIMEACTIVITYREACTOR_H_
#define REALTIMEACTIVITYREACTOR_H_

#include "Activity.h"

namespace Shipping{
class VirtualTimeActivityManager;
class RealTimeActivityManager;
class RealTimeActivityReactor : public Fwk::Activity::Notifiee {
public:
    RealTimeActivityReactor(const std::string &_name,
                           Fwk::Activity*,
                           Fwk::Ptr<VirtualTimeActivityManager>,
                           Fwk::Ptr<RealTimeActivityManager>,
                           Fwk::Time _nextVirtualTime);
    virtual void onStatus();
protected:
    Fwk::Activity::Ptr activity_;
    Fwk::Ptr<RealTimeActivityManager> manager_;
    Fwk::Time nextVirtualTime_;
    Fwk::Ptr<VirtualTimeActivityManager> virtualTimeActivityManager_;
    RealTimeActivityReactor();
    RealTimeActivityReactor(const RealTimeActivityReactor &);
};
}//end namespace Shipping

#endif /* REALTIMEACTIVITYREACTOR_H_ */
