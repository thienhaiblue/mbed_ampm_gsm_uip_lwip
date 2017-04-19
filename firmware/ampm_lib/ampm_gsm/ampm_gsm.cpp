

#include "mbed.h"
#include "rtos.h"
#include "mbed_stats.h"
#include "ampm_gsm_api.h"
#include "ampm_gsm.h"
#include "lib/sys_tick.h"
#include "lib/encoding.h"
#include "platform/platform.h"
#include "Stream.h"
#include "SerialBase.h"
#include "PlatformMutex.h"

//#ifdef CMSIS_OS_RTX
//osMutexId ampmGsmMutexId;
//osMutexDef(ampmGsmMutex);
//#endif
using namespace mbed;
//namespace mbed {

AmpmGsm *AmpmGsm::_fn  = 0;

AmpmGsm::AmpmGsm(PinName tx, PinName rx, int baud,
	PinName mosfet,
	PinName power,
	PinName reset,
	PinName DTR,
	PinName RTS,
	PinName CTS,
	PinName RI):
	serial(tx, rx, baud),
	GsmMosfet(mosfet), 
	GsmPwrOn(power),
	GsmReset(reset),
	GsmDTR(DTR), 
	GsmRTS(RTS),
	GsmCTS(reset),
	GsmRI(RI)
{
	_fn = this;
	serial.attach(&gsmPort_RxIrq,Serial::RxIrq); 
	GsmRI.rise(&Ampm_SetRinging);
	AmpmGsmApiInit();
} 

AmpmGsm::~AmpmGsm()
    //delete all tables and card data registers
{
    delete this;
}




void AmpmGsm::MODEM_RTS_Set()
{
	if(GsmMosfet.is_connected())
		GsmRTS.write(1);
}
void AmpmGsm::MODEM_RTS_Clr()
{
	if(GsmMosfet.is_connected())
		GsmMosfet.write(0);
}
void AmpmGsm::MODEM_DTR_Set()
{
	if(GsmDTR.is_connected())
		GsmDTR.write(1);
}
void AmpmGsm::MODEM_DTR_Clr()
{
	if(GsmDTR.is_connected())
		GsmDTR.write(0);
}
void AmpmGsm::MODEM_MOSFET_On()
{
	if(GsmMosfet.is_connected())
	{
		GsmMosfet.output();
		GsmMosfet.mode(OpenDrain);
		GsmMosfet.write(0);
	}
}
void AmpmGsm::MODEM_MOSFET_Off()
{
	if(GsmMosfet.is_connected())
	{
		GsmMosfet.input();
		GsmMosfet.mode(PullUp);
	}
}
void AmpmGsm::MODEM_POWER_Set()
{
	if(GsmPwrOn.is_connected())
		GsmPwrOn.write(1);
}
void AmpmGsm::MODEM_POWER_Clr()
{
	if(GsmPwrOn.is_connected())
		GsmPwrOn.write(0);
}
void AmpmGsm::MODEM_RESET_Set()
{
	if(GsmReset.is_connected())
		GsmReset.write(1);
}
void AmpmGsm::MODEM_RESET_Clr()
{
	if(GsmReset.is_connected())
		GsmReset.write(0);
}



void AmpmGsm::Init(char *apn, char *usr,char *pwr)
{
	AMPM_GSM_Init(apn,usr,pwr,NULL,NULL);
//	#ifdef CMSIS_OS_RTX
//	ampmGsmMutexId = osMutexCreate(osMutex(ampmGsmMutex));
//	#endif
}


void AmpmGsm::Init(char *apn, char *usr,char *pwr,uint8_t (*tcpIpCallback)(void),uint8_t (*tcpIpInit)(void))
{
	AMPM_GSM_Init(apn,usr,pwr,tcpIpCallback,tcpIpInit);
//	#ifdef CMSIS_OS_RTX
//	ampmGsmMutexId = osMutexCreate(osMutex(ampmGsmMutex));
//	#endif
}

void AmpmGsm::Process(void)
{
	AMPM_GSM_MainTask(NULL);
}

uint16_t AmpmGsm::SendSmsWait(char *phone,string sms)
{
	return SendSmsWait(phone,sms,SMS_TEXT_MODE);
}

uint16_t AmpmGsm::SendSmsWait(char *phone,string sms,SMS_MODE_TYPE type)
{
	uint8_t *smsStatus = (uint8_t *)malloc(sizeof(uint8_t));
	uint16_t timeout = 60;//60s
	AMPM_GSM_LIB_DBG("\r\n AmpmGsm::SendSmsWait:Send Sms \r\n");
	if(SendSms(smsStatus,phone, sms,type,NULL) == SMS_OK)
	{
		while((*smsStatus != SMS_OK) && timeout)
		{
			Thread::wait(1000);
			if(timeout) timeout--;
			//AMPM_GSM_LIB_DBG("\r\n AmpmGsm::SendSmsWait:%d \r\n",timeout);
		}
	}
	if(*smsStatus == SMS_OK)
	{
		AMPM_GSM_LIB_DBG("\r\n AmpmGsm::SendSmsWait:Sms Sent\r\n");
		Ampm_UpdateStatus(smsStatus,0xff);
		return SMS_OK;
	}
	Ampm_UpdateStatus(smsStatus,0xff);
	AMPM_GSM_LIB_DBG("\r\n AmpmGsm::SendSmsWait:Sms Fail\r\n");
	return SMS_ERROR;
}



uint16_t AmpmGsm::SendSms(char *phone,string sms,SMS_MODE_TYPE type,void (*callback)(struct SMS_LIST_TYPE *msg))
{
	return SendSms(NULL,phone, sms,type,callback);
}

uint16_t AmpmGsm::SendSms(char *phone,string sms,SMS_MODE_TYPE type)
{
	return SendSms(NULL,phone, sms,type,NULL);
}

uint16_t AmpmGsm::SendSms(char *phone,string sms,void (*callback)(struct SMS_LIST_TYPE *msg))
{
	return SendSms(NULL,phone, sms,SMS_TEXT_MODE,callback);
}

uint16_t AmpmGsm::SendSms(char *phone,string sms)
{
	return SendSms(NULL,phone, sms,SMS_TEXT_MODE,NULL);
}



uint16_t AmpmGsm::SendSms(uint8_t *status,char *phone,string sms,SMS_MODE_TYPE type,void (*callback)(struct SMS_LIST_TYPE *msg))
{
	uint16_t smsLen,res,flag = 0;
//	#ifdef CMSIS_OS_RTX
//	if(osMutexWait(ampmGsmMutexId, 3000) == osOK)
//	#endif
	{
//		if(status == NULL)
//		{
//			status = (uint8_t *)malloc(sizeof(uint8_t));
//			flag = 1;
//		}
		if(type == SMS_PDU16_MODE)
		{
			uint8_t *smsBuf = (uint8_t *)malloc(sms.length()*2);
			smsLen = utf8s_to_ucs2s((int16_t *)smsBuf,(uint8_t *)sms.c_str());
			big2litel_endian((uint16_t *)smsBuf,unilen((uint16_t *)smsBuf));
			smsLen *= 2;
			res =  Ampm_Sms_SendMsg(status,callback,(uint8_t *)phone,(uint8_t *)smsBuf,smsLen,SMS_PDU16_MODE,10/*interval resend in sec*/,3/*resend times*/);
			free(smsBuf);
		}
		else
		{
			AMPM_GSM_LIB_DBG("\r\n AmpmGsm::SMS Sending:%d:%s\r\n",sms.length(),sms.c_str());
			res = Ampm_Sms_SendMsg(status,callback,(uint8_t *)phone,(uint8_t *)sms.c_str(),sms.length(),SMS_TEXT_MODE,10/*interval resend in sec*/,3/*resend times*/);
		}
//		if(flag)
//			free(status);
//		#ifdef CMSIS_OS_RTX
//		osMutexRelease(ampmGsmMutexId);
//		#endif
	}
	return res;
}


void AmpmGsm::RxDataCallback(void)
{
	gsmPort_RxIrq();
}

void AmpmGsm::RingCallback(void)
{
	Ampm_SetRinging();
}

void AmpmGsm::SetMode(AMPM_GSM_MODE mode)
{
	Ampm_GsmSetMode(mode);
}

//}



