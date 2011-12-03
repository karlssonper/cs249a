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

#ifdef DEBUG_OUTPUT
#define FWK_DEBUG(arg) (std::cout << arg << std::endl)
#else
#define FWK_DEBUG(arg)
#endif

#endif /* DEBUG_H_ */
