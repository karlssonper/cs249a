/*
 * Debug.h
 *
 *  Created on: Nov 5, 2011
 *      Author: per
 */

#ifndef DEBUG_H_
#define DEBUG_H_
#include <iostream>

//#define DEBUG_OUTPUT

//#define DEBUG_SIM_OUTPUT
#define SIM_OUTPUT

#ifdef DEBUG_OUTPUT
#define FWK_DEBUG(arg) (std::cout << arg << std::endl)
#else
#define FWK_DEBUG(arg)
#endif

#ifdef DEBUG_SIM_OUTPUT
#define FWK_SIM_DEBUG(arg) (std::cout << arg << std::endl)
#else
#define FWK_SIM_DEBUG(arg)
#endif

#ifdef SIM_OUTPUT
#define SIM(arg) (std::cout << arg << std::endl)
#else
#define SIM(arg)
#endif


#endif /* DEBUG_H_ */
