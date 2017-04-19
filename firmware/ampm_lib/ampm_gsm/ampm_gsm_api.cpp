

#include "mbed.h"
#include "lib/sys_tick.h"
#include "ampm_gsm_api.h"
#include "ampm_gsm_main_task.h"
#include "digitalInOut.h"
#include "ampm_gsm.h"




using namespace mbed;


extern Serial gsmPort;
extern Serial rs232;

uint8_t GSM_RxBuff[512];
RINGBUF GSM_RxRingBuff;

uint8_t GSM_TxBuff[512];
RINGBUF GSM_TxRingBuff;


void AmpmGsmApiInit(void)
{

	MODEM_MOSFET_On();
	RINGBUF_Init(&GSM_RxRingBuff,GSM_RxBuff,sizeof(GSM_RxBuff));
	RINGBUF_Init(&GSM_TxRingBuff,GSM_TxBuff,sizeof(GSM_TxBuff));
	
}


void gsmPort_RxIrq(void)
{
	uint8_t c;
	//c = gsmPort.getc();//have mutex
	c = (uint8_t)(UART5->DR & 0x1FF); //without mutex work faster and bester
	AT_ComnandParser(c);
	RINGBUF_Put(&GSM_RxRingBuff,c);
}




void MODEM_UartInit(uint32_t baudrate)
{
	//gsmPort.baud(baudrate);
}

void COMM_Putc(uint8_t c)
{
	//if(gsmCts == 0)
	{
		gsmPort.putc(c);
		RINGBUF_Put(&GSM_TxRingBuff,c);
		RINGBUF_Get(&GSM_TxRingBuff,&c);
	}
}

int32_t COMM_Getc(uint8_t *c)
{
	return RINGBUF_Get(&GSM_RxRingBuff,c);
}


void COMM_Puts(uint8_t *s)
{
	while(*s)
	{
		COMM_Putc(*s++);
	}
}

void MODEM_RTS_Set(void)
{ 
	AmpmGsm::_fn->MODEM_RTS_Set();
}
void MODEM_RTS_Clr(void)
{
	AmpmGsm::_fn->MODEM_RTS_Clr();
}
void MODEM_DTR_Set(void)
{
	AmpmGsm::_fn->MODEM_DTR_Set();
}
void MODEM_DTR_Clr(void)
{
	AmpmGsm::_fn->MODEM_DTR_Clr();
}
void MODEM_MOSFET_On(void)
{
	AmpmGsm::_fn->MODEM_MOSFET_On();
}
void MODEM_MOSFET_Off(void)
{
	AmpmGsm::_fn->MODEM_MOSFET_Off();
}
void MODEM_POWER_Set(void)
{
	AmpmGsm::_fn->MODEM_POWER_Set();
}
void MODEM_POWER_Clr(void)
{
	AmpmGsm::_fn->MODEM_POWER_Clr();
}
void MODEM_RESET_Set(void)
{
	AmpmGsm::_fn->MODEM_RESET_Set();
}
void MODEM_RESET_Clr(void)
{
	AmpmGsm::_fn->MODEM_RESET_Clr();
}
void MODEM_Wakeup(void)
{
	MODEM_RTS_Set();
	SysTick_DelayMs(100);
	MODEM_RTS_Clr();
}
