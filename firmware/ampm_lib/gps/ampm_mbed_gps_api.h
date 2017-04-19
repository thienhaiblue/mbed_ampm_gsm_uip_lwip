/* 
*/
#ifndef __AMPM_MBED_GPS_API_H__
#define __AMPM_MBED_GPS_API_H__

#include "mbed.h"
#include "mbed_stats.h"
#include "gps/ampm_gps_io.h"
#include "SerialBase.h"

using namespace mbed;

class AmpmGps{
public:
	AmpmGps(PinName tx, PinName rx, int baud = 115200);
	static AmpmGps *_fn;
	virtual ~AmpmGps();
	RawSerial serial;
	AMPM_GPS gps;
	void Process(void);
};

#endif

