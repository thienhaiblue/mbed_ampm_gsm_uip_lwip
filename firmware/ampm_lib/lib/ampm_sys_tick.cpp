





#include "lib/ampm_sys_tick.h"
#include "lib/sys_tick.h"


using namespace mbed;

AmpmSysTick *AmpmSysTick::_fn  = 0;
AmpmSysTick::AmpmSysTick()
{
	_fn = this;
	ampmTicker.attach_us(&SysTick_Task,1000);
}

AmpmSysTick::~AmpmSysTick()
    //delete all tables and card data registers
{
    delete this;
}







