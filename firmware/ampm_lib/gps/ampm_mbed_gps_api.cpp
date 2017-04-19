


#include "gps/ampm_mbed_gps_api.h"
#include "platform/platform.h"
#include "Serial.h"



using namespace mbed;

AmpmGps *AmpmGps::_fn  = 0;

AmpmGps::AmpmGps(PinName tx, PinName rx, int baud):
	serial(tx, rx, baud)
{
	_fn = this;
	serial.attach(&gpsPort_RxIrq,Serial::RxIrq);
	GPS_IO_Init();
}

AmpmGps::~AmpmGps()
    //delete all tables and card data registers
{
    delete this;
}



void AmpmGps::Process(void)
{
	GPS_Task(&gps);
}







