/*
 * ConnRep.h
 *
 *  Created on: Nov 4, 2011
 *      Author: per
 */

#ifndef OUTPUT_FLT_PNTING_H
#define OUTPUT_FLT_PNTING_H
#include <sstream>
#include <iomanip>
namespace Shipping {
    template <typename T>
    inline string fltPnt2str(T x) {
        stringstream ss;
        ss << fixed << setprecision(2) << x;
        return ss.str();
    };
};//end namespace


#endif /* CONNREP_H_ */
