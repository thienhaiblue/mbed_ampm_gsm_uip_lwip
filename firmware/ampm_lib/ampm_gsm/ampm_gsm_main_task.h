/******************************************************************************
Name: Hai Nguyen Van
Cellphone: (84) 97-8779-222
Mail:thienhaiblue@ampm.com.vn 
----------------------------------
AMPM ELECTRONICS EQUIPMENT TRADING COMPANY LIMITED.,
Add: 22 Phan Van Suu street , Ward 13, Tan Binh District, HCM City, VN
******************************************************************************/
#ifndef __AMPM_GSM_MAIN_TASK_H__
#define __AMPM_GSM_MAIN_TASK_H__
#include "at_command_parser.h"
#include "ampm_gsm_common.h"
#include "ampm_gsm_startup.h"
#include "ampm_gsm_dial_up.h"
#include "ampm_gsm_ring.h"
#include "ampm_gsm_sms.h"
#include "ppp/ppp.h"


#define PPP_LWIP

#ifdef PPP_UIP
#elif defined(PPP_LWIP)
#include "lwip/init.h"
#endif
#ifdef AMPM_GSM_OS_RTX
  #include "cmsis_os.h"
#endif    
#ifdef __cplusplus
 extern "C" {
#endif


typedef enum{
	AMPM_GSM_NONE = 0,
	AMPM_GSM_GPRS_ENABLE,
	AMPM_GSM_SLEEP_MODE
}AMPM_GSM_MODE;

typedef enum{
	AMPM_GSM_MAIN_INIT_PHASE = 0,
	AMPM_GSM_MAIN_STARTUP_PHASE,
	AMPM_GSM_MAIN_SMS_RECV_PHASE,
	AMPM_GSM_MAIN_SMS_SEND_PHASE,
	AMPM_GSM_MAIN_VOICECALL_PHASE,
	AMPM_GSM_MAIN_DATACALL_PHASE,
	AMPM_GSM_MAIN_DIAL_UP_PHASE,
	AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE,
	AMPM_GSM_MAIN_GOTO_CMD_MODE_CHECK_PHASE,
	AMPM_GSM_MAIN_WAIT_GOTO_CMD_MODE_PHASE,
	AMPM_GSM_MAIN_GOTO_DATA_MODE_PHASE,
	AMPM_GSM_MAIN_WAIT_GOTO_DATA_MODE_PHASE,
	AMPM_GSM_MAIN_IDLE_PHASE,
	AMPM_GSM_MAIN_GO_TO_SLEEP_PHASE,
	AMPM_GSM_MAIN_SLEEP_PHASE,
	AMPM_GSM_MAIN_WAKEUP_PHASE
} AMPM_GSM_MAIN_PHASE_TYPE;
uint8_t Ampm_GsmIsGood(void);
uint8_t Ampm_GsmIsWorking(void);
void AMPM_GSM_MainTask(void const * argument);
void AMPM_GSM_Init(char *apn, char *usr,char *pwr,uint8_t (*tcpIpCallback)(void),uint8_t (*tcpIpInit)(void));
uint8_t Ampm_Gsm_IsIdle(void);
extern AMPM_GSM_MODE ampm_GSM_mode;
AMPM_GSM_MAIN_PHASE_TYPE Ampm_GsmGetPhase(void);
void Ampm_GsmSetMode(AMPM_GSM_MODE mode);
#ifdef __cplusplus
}
#endif
#endif

