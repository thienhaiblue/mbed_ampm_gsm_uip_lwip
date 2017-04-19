

#include "gps/ampm_mbed_gps_api.h"
#include "gps/ampm_gps_io.h"
#include "lib/ringbuf.h"
#include "stm32f1xx.h"



void gpsPort_RxIrq(void)
{
	uint8_t c;
	c = AmpmGps::_fn->serial.getc();
	//c = (uint8_t)(USART2->DR & 0x1FF); 
	GPS_PutChar(&AmpmGps::_fn->gps,c);
}
 
void GPS_IO_Init(void)
{
	GPSInit(&AmpmGps::_fn->gps);
}


