/* 
*/
#ifndef __AMPM_GPS_IO_H__
#define __AMPM_GPS_IO_H__

#include "mbed.h"
#include "mbed_stats.h"
#include "Serial.h"
#include "gps/ampm_gps.h"


void gpsPort_RxIrq(void);
void GPS_IO_Init(void);

#endif

