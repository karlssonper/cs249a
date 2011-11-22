/*
 * Shipping.h
 *
 *  Created on: Nov 21, 2011
 *      Author: per
 */

#ifndef SHIPPINGACTIVITYREACTOR_H_
#define SHIPPINGACTIVITYREACTOR_H_

#include "Engine.h"

namespace Shipping {

class ShippingActivityReactor : public Activity::Notifiee{
public:
    ShippingActivityReactor(Fwk::Ptr<Activity::Manager> manager, Activity*
                activity, EngineManager * engine_);

       void onStatus();
protected:
       Activity::Ptr activity_;
       Fwk::Ptr<Activity::Manager> manager_;
       enum Position{
           created_ = 0,
           moving_ = 1,
           idle_ = 2
       };
       Conn::PtrConst conn_;
       EntityManager::Ptr entityManager_;
       Position position_;
       Segment::PtrConst curSeg_;
       Location::PtrConst dest_;
private:

};

} //end namespace

#endif /* SHIPPING_H_ */
