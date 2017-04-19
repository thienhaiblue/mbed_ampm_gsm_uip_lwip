
#ifndef __AMPM_GSM_API_H__
#define __AMPM_GSM_API_H__

#include "mbed.h"
#include "string"
#include "vector"
#include "lib/ringbuf.h"
#include "comm.h"
extern DigitalIn gsmCts;
extern DigitalIn gsmDCD;

extern DigitalOut gsmRTS;
extern DigitalOut gsmDTR;
extern DigitalOut gsmPWRKEY;
extern DigitalOut gsmRST;
extern DigitalInOut gsmPWRON;


void AmpmGsmApiInit(void);
void gsmPort_RxIrq(void);


#endif

