/*
 * ForwardActivityReactor.h
 *
 *  Created on: Nov 22, 2011
 *      Author: per
 */

#ifndef FORWARDACTIVITYREACTOR_H_
#define FORWARDACTIVITYREACTOR_H_

namespace Shipping{
class ForwardActivityReactor : public Activity::Notifiee {
public:
    ForwardActivityReactor(Fwk::Ptr<Activity::Manager>, Activity*);
    virtual void onStatus();
protected:
       Activity::Ptr activity_;
       Fwk::Ptr<Activity::Manager> manager_;
};
}//end namespace Shipping

#endif /* FORWARDACTIVITYREACTOR_H_ */
