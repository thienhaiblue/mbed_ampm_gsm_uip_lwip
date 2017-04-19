/* 
*/
#ifndef __AMPM_SYS_TICK_H__
#define __AMPM_SYS_TICK_H__

#include "mbed.h"

using namespace mbed;

class AmpmSysTick{
public:
	AmpmSysTick();
	Ticker  ampmTicker;
	static AmpmSysTick *_fn;
	virtual ~AmpmSysTick();
};
#endif

