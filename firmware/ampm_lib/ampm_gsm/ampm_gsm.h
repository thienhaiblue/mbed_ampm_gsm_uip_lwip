/* 
*/
#ifndef __AMPM_GSM_H__
#define __AMPM_GSM_H__

#include "ampm_gsm_api.h"
#include "mbed.h"
#include "Serial.h"
#include "string"
#include "vector"
#include "ampm_gsm_main_task.h"
using namespace mbed;
//namespace mbed {
class AmpmGsm{
public:
	AmpmGsm(PinName tx, PinName rx, int baud = 115200,PinName mosfet = NC,PinName power=NC,PinName reset=NC,PinName DTR=NC,PinName RTS=NC,PinName CTS=NC,PinName RI=NC);
//	AmpmGsm(PinName tx, PinName rx, int baud = 115200,PinName power = NC,PinName reset = NC,PinName RI = NC);
//	AmpmGsm(PinName tx, PinName rx, int baud = 115200,PinName power,PinName RI);
//	AmpmGsm(PinName tx, PinName rx, int baud = 115200,PinName power,PinName DTR,PinName RTS,PinName CDC,PinName RI);
//	AmpmGsm(PinName tx, PinName rx, int baud = 115200,PinName power,PinName reset,PinName DTR,PinName RTS,PinName CDC,PinName RI);
	static AmpmGsm *_fn;
	virtual ~AmpmGsm();
	RawSerial serial;
	DigitalInOut GsmMosfet; 
	DigitalOut GsmPwrOn;
	DigitalOut GsmReset;
	DigitalOut GsmDTR;
	DigitalOut GsmRTS;
	DigitalIn GsmCTS;
	InterruptIn GsmRI;
	void Init(char *apn, char *usr,char *pwr,uint8_t (*tcpIpCallback)(void),uint8_t (*tcpIpInit)(void));
	void Init(char *apn, char *usr,char *pwr);
	void Process(void);
	void SendSms(char *phone,char *sms,uint16_t len);
  void RxDataCallback(void);
	void RingCallback(void);
	uint8_t vTcpIpTaskInit(void);
	uint8_t vTcpIpTask(void);
	uint16_t SendSmsWait(char *phone,string sms);
	uint16_t SendSmsWait(char *phone,string sms,SMS_MODE_TYPE type);
	uint16_t SendSms(char *phone,string sms,SMS_MODE_TYPE type,void (*callback)(struct SMS_LIST_TYPE *msg));
	uint16_t SendSms(char *phone,string sms,SMS_MODE_TYPE type);

	uint16_t SendSms(char *phone,string sms,void (*callback)(struct SMS_LIST_TYPE *msg));
	uint16_t SendSms(char *phone,string sms);
	uint16_t SendSms(uint8_t *status,char *phone,string sms,SMS_MODE_TYPE type,void (*callback)(struct SMS_LIST_TYPE *msg));
	virtual void MODEM_RTS_Set();
	virtual void MODEM_RTS_Clr();
  virtual void MODEM_DTR_Set();
  virtual void MODEM_DTR_Clr();
  virtual void MODEM_MOSFET_On();
  virtual void MODEM_MOSFET_Off();
  virtual void MODEM_POWER_Set();
  virtual void MODEM_POWER_Clr();
  virtual void MODEM_RESET_Set();
  virtual void MODEM_RESET_Clr();
	virtual void SetMode(AMPM_GSM_MODE mode);
};
//}
#endif

