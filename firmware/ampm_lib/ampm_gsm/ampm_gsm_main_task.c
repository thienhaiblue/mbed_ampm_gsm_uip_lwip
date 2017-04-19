
/**********************************************************************
Name: Hai Nguyen Van
Cellphone: (84) 97-8779-222
Mail:thienhaiblue@ampm.com.vn 
----------------------------------
AMPM ELECTRONICS EQUIPMENT TRADING COMPANY LIMITED.,
Add: 634/6 Phan Van Suu street , Ward 13, Tan Binh District, HCM City, VN

*********************************************************************/
//#include "resolv.h"
//#include "resolver.h"
#include "ampm_gsm_main_task.h"
#include "ppp/ppp.h"
#include "lwip/tcpip.h"
#ifdef CMSIS_OS_RTX 
osThreadDef(AMPM_GSM_MainTask, osPriorityNormal, 1024);
#endif
/*
D =  AT CMD DEFAULT
F = AT CMD do not check sucess
0 =  AT CMD
1 =  GSM POWER PIN CLR
2 =  GSM POWER PIN SET
3 = DELAY
4 =  GSM RESET PIN CLR
5 =  GSM RESET PIN SET
6 =  GSM DTR PIN CLR
7 =  GSM DTR PIN SET
S = STOP	@@D$AT+IPR=0\r$\r\n\
*/

const uint8_t ampm_AtGsmCmdStart[] = {
	"@@1\r\n\
	@@3$100\r\n\
	@@2$\r\n\
	@@3$100\r\n\
	@@1\r\n\
	@@3$1500\r\n\
	@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@0$ATI\r$ATI\r\r\n$3$OK$ERROR$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT+CNMI=2,1,0,0,0\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$1000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};

const uint8_t ampm_AtGsmCmdStartBGS2_W[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&D1\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT^SCFG=\"URC/Datamode/Ringline\",\"on\"\r$\r\n\
	@@D$AT+CNMI=3,1,0,0,1\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@D$AT^SM20=0\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$1000$100\r\n\
	@@0$AT^SCID\r$^SCID: $2$OK$ERROR$3$1000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};

const uint8_t ampm_AtGsmCmdStartBGS2_E[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&D1\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT^SCFG=\"URC/Datamode/Ringline\",\"on\"\r$\r\n\
	@@D$AT+CNMI=3,1,0,0,1\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@D$AT^SM20=0\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$1000$100\r\n\
	@@0$AT^SCID\r$^SCID: $2$OK$ERROR$3$1000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};


const uint8_t ampm_AtGsmCmdStartBG2_E[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&D1\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT\\Q3\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT^SCFG=\"URC/Datamode/Ringline\",\"on\"\r$\r\n\
	@@D$AT+CNMI=3,1,0,0,1\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$1000$100\r\n\
	@@0$AT^SCID\r$^SCID: $2$OK$ERROR$3$1000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};





const uint8_t ampm_AtGsmCmdStartM95[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT+CNMI=2,1,0,0,0\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$3000$100\r\n\
	@@0$AT+QCCID\r$+QCCID\r\r\n$2$OK$ERROR$3$3000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};


const uint8_t ampm_AtGsmCmdStartM26[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT+CNMI=2,1,0,0,0\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$3000$100\r\n\
	@@0$AT+QCCID\r$+QCCID\r\r\n$2$OK$ERROR$3$3000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};

const uint8_t ampm_AtGsmCmdStartSIM900[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$ATI\r$\r\n\
	@@D$AT&C1\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT+CNMI=2,1,0,0,0\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$1000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};



const uint8_t ampm_AtGsmCmdStartUbloxG100[] = {
	"@@0$AT\r$0$0$OK$NOT USE$3$1000$100\r\n\
	@@D$ATZ\r$\r\n\
	@@D$AT&K0\r$\r\n\
	@@D$AT+UPSV=2\r$\r\n\
	@@D$AT+CMGF=1\r$\r\n\
	@@D$AT+CNMI=2,1,0,0,0\r$\r\n\
	@@D$AT+CLIP=1\r$\r\n\
	@@0$AT+CREG?\r$0$0$+CREG: 0,1$NOT USE$20$3000$100\r\n\
	@@0$AT+CGSN\r$+CGSN\r\r\n$1$OK$ERROR$3$1000$100\r\n\
	@@0$AT+CCID\r$+CCID: $2$OK$ERROR$3$1000$100\r\n\
	@@0$AT+COPS=0,2\r$0$0$OK$NOT USE$20$3000$100\r\n\
	@@G$AT+CSQ\r$+CSQ:$4$OK$ERROR$1$2000$100\r\n\
	@@S"
};


extern uint8_t *ampm_AtGsmCmdStart_pt;
extern void PPP_Init(void);
extern void RESOLVER_Manage(void);
extern int8_t PPP_IsLinked(void);
extern uint8_t PPP_IsDead(void);
extern void RESOLVER_Reset(void);
extern void PPP_SetConnect(void);
extern uint32_t PPP_ManageLink(void);
extern void PPP_SetAuthentication(int8_t* usr, int8_t* pwd);
extern void Ampm_MainSmsRecvCallback(uint8_t *buf);
uint32_t Ampm_MainSwithToIdle(uint16_t cnt, uint8_t c);

enum PPPStatus
{
  PPP_CONNECTING,
  PPP_CONNECTED,
  PPP_DISCONNECTED,
};

#ifdef PPP_LWIP
char *pppUser;
char *pppPass;
int thisPPP = -1;
extern void tcpip_thread(void *arg);
#endif

#define AMPM_CHECK_SMS_INTERVAL 60000 //1min


uint8_t dataSendingTimeout = 0;

AMPM_GSM_MODE ampm_GSM_mode = AMPM_GSM_NONE;


extern uint16_t CMD_CfgParse(char *buff,uint8_t *smsSendBuff,uint32_t smsLenBuf,uint16_t *dataOutLen,uint8_t pwdCheck);

AMPM_GSM_MAIN_PHASE_TYPE ampmGSM_TaskPhase;

uint32_t smsCheckTime = 0;
uint8_t gsmMainTaskTryCnt;
Timeout_Type tRingTask;

uint8_t Ampm_GsmMainCallPhaseFinished(AMPM_CMD_PHASE_TYPE phase);
uint8_t Ampm_GsmMainATPhaseFinished(AMPM_CMD_PHASE_TYPE phase);

uint8_t  (*Ampm_TcpIpCallback)(void);
uint8_t  (*Ampm_TcpIpInit)(void);

const AMPM_GSM_AT_CMD_PACKET_TYPE ampmAtCmd_AT_CFUN_1 = {"AT+CFUN=1\r",NULL,NULL,NULL,"OK","ERROR"};//delay = 100,timeout = 1000,retry = 1
const AMPM_GSM_AT_CMD_PACKET_TYPE ampmAtCmd_AT_CFUN_9 = {"AT+CFUN=9\r",NULL,NULL,NULL,"OK","ERROR"};//delay = 100,timeout = 1000,retry = 1

const AMPM_CMD_PROCESS_TYPE ampmMainCmdProcess_CHLD	= {
		(void *)&ampmCmdProcess_AT,(void *)&ampmAtCmd_AT_CHLD	,Ampm_GsmSendCallback,Ampm_GsmRecvCallback,Ampm_GsmMainCallPhaseFinished,1,2000,500};

const AMPM_CMD_PROCESS_TYPE ampmMainCmdProcess_End	= {
NULL,(void *)&ampmAtCmd_AT,Ampm_GsmSendCallback,Ampm_GsmRecvCallback,NULL,1,2000,100};		
		
const AMPM_CMD_PROCESS_TYPE ampmMainCmdProcess_AT_CFUN_1	= {
(void *)&ampmMainCmdProcess_End,(void *)&ampmAtCmd_AT_CFUN_1,Ampm_GsmSendCallback,Ampm_GsmRecvCallback,NULL,1,3000,100};

const AMPM_CMD_PROCESS_TYPE ampmMainCmdProcess_AT_CFUN_9	= {
NULL,(void *)&ampmAtCmd_AT_CFUN_9,Ampm_GsmSendCallback,Ampm_GsmRecvCallback,NULL,1,3000,100};	

const AMPM_CMD_PROCESS_TYPE ampmMainCmdProcess_ATH	= {
(void *)&ampmMainCmdProcess_AT_CFUN_9,(void *)&ampmAtCmd_ATH,Ampm_GsmSendCallback,Ampm_GsmRecvCallback,NULL,1,3000,100};
		
const AMPM_CMD_PROCESS_TYPE ampmMainCmdProcess_AT	= {
(void *)&ampmMainCmdProcess_ATH,(void *)&ampmAtCmd_AT,Ampm_GsmSendCallback,Ampm_GsmRecvCallback,Ampm_GsmMainATPhaseFinished,1,3000,500};


__weak void Ampm_MainSmsRecvCallback(uint8_t *buf)
{
	
	
}

enum PPPStatus ppp_status = PPP_DISCONNECTED;

#ifdef PPP_LWIP
//Link Callback
void pppCallback(void *ctx,int errCode, void *arg)
{
  switch ( errCode )
  {
    //No error
    case PPPERR_NONE:
      {
        struct ppp_addrs* addrs = (struct ppp_addrs*) arg;
        //m_ip = IpAddr(&(addrs->our_ipaddr)); //Set IP
      }
      ppp_status = PPP_CONNECTED;
      break;
    default:
      //Disconnected
      AMPM_GSM_LIB_DBG("PPPNetIf: Callback errCode = %d.\n", errCode);
      ppp_status = PPP_DISCONNECTED;
    break;
  }
}

/* PPP status callback example */
static void status_cb(void *ctx, int err_code, void *arg) {
  LWIP_UNUSED_ARG(ctx);

  switch(err_code) {
    case PPPERR_NONE: {
			ppp_status = PPP_CONNECTED;
      printf("status_cb: Connected\n");
      break;
    }
    case PPPERR_PARAM: {
      printf("status_cb: Invalid parameter\n");
      break;
    }
    case PPPERR_OPEN: {
      printf("status_cb: Unable to open PPP session\n");
      break;
    }
    case PPPERR_DEVICE: {
      printf("status_cb: Invalid I/O device for PPP\n");
      break;
    }
    case PPPERR_ALLOC: {
			ppp_status = PPP_DISCONNECTED;
      printf("status_cb: Unable to allocate resources\n");
      break;
    }
    case PPPERR_USER: {
      printf("status_cb: User interrupt\n");
      break;
    }
    case PPPERR_CONNECT: {
			ppp_status = PPP_DISCONNECTED;
      printf("status_cb: Connection lost\n");
      break;
    }
    case PPPERR_AUTHFAIL: {
			ppp_status = PPP_DISCONNECTED;
      printf("status_cb: Failed authentication challenge\n");
      break;
    }
    case PPPERR_PROTOCOL: {
			ppp_status = PPP_DISCONNECTED;
      printf("status_cb: Failed to meet protocol\n");
      break;
    }
    default: {
      printf("status_cb: Unknown error code %d\n", err_code);
      break;
    }
  }
}

#endif

void Ampm_Gsm_Error(char *err)
{
	while(1)
	{
		SysTick_DelayMs(1000);
		AMPM_GSM_LIB_DBG("AmpmGsmError:%s\r\n",err);
	}
}


void Ampm_GsmSetMode(AMPM_GSM_MODE mode)
{
	ampm_GSM_mode = mode;
}


uint8_t Ampm_GsmMainATPhaseFinished(AMPM_CMD_PHASE_TYPE phase)
{
	if(ampmGSM_TaskPhase == AMPM_GSM_MAIN_GO_TO_SLEEP_PHASE)
	{
		Ampm_SendAtCmdNow(&ampmMainCmdProcess_ATH);
	}
	else//wake up
	{
		Ampm_SendAtCmdNow(&ampmMainCmdProcess_AT_CFUN_1);
	}
	return 1;
}

uint8_t Ampm_GsmMainCallPhaseFinished(AMPM_CMD_PHASE_TYPE phase)
{
		ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
		return 1;
}

uint8_t Ampm_GsmIsWorking(void)
{
	if(ampmGSM_TaskPhase == AMPM_GSM_MAIN_DATACALL_PHASE)
	{
		return 1;
	}	
	return 0;
}

uint8_t Ampm_Gsm_IsIdle(void)
{
	if(ampmGSM_TaskPhase == AMPM_GSM_MAIN_IDLE_PHASE
	&& Ampm_Ringing_GetPhase() != AMPM_GSM_RING_IDLE_PHASE
	&& Ampm_SmsCheckMessage_IsEmpty() 
	&& Ampm_VoiceCallCheckList_IsEmpty()
	&& ampm_NewSmsFlag == 0
	)
	{
		return 1;
	}	
	return 0;
}

uint8_t Ampm_GsmIsGood(void)
{
	if(ampmGSM_TaskPhase > AMPM_GSM_MAIN_STARTUP_PHASE)
	{
		return 1;
	}	
	return 0;
}

uint32_t Ampm_MainSwithToIdle(uint16_t cnt, uint8_t c)
{
	Ampm_GSM_DialUp_Reset();
	#ifdef PPP_UIP
	PPP_Init();
	#elif defined(PPP_LWIP)
	pppInit();
	#endif
	Ampm_TcpIpInit();
	ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
	return 0;
}

AMPM_GSM_MAIN_PHASE_TYPE Ampm_GsmGetPhase(void)
{
	return ampmGSM_TaskPhase;
}

uint8_t vTcpIpTaskInit(void)
{
	return 0;
}

uint8_t vTcpIpTask(void)
{	
    return 0;
}


void AMPM_GSM_Init(char *apn, char *usr,char *pwr,uint8_t (*tcpIpCallback)(void),uint8_t (*tcpIpInit)(void))
{
	Ampm_GsmSetApn((uint8_t *)apn);
	#ifdef PPP_UIP
	PPP_SetAuthentication((int8_t *)usr, (int8_t *)pwr);
	#elif defined(PPP_LWIP)
	tcpip_init(NULL,NULL);
	pppInit();
	pppUser = usr;
	pppPass = pwr;
	pppSetAuth(PPPAUTHTYPE_PAP, usr, pwr); //TODO: Allow CHAP as well
	#endif
	if(tcpIpCallback)
		Ampm_TcpIpCallback = tcpIpCallback;
	else
		Ampm_TcpIpCallback = vTcpIpTask;
	if(tcpIpInit)
		Ampm_TcpIpInit = tcpIpInit;
	else
		Ampm_TcpIpInit = vTcpIpTaskInit;
	ampmGSM_TaskPhase = AMPM_GSM_MAIN_INIT_PHASE;
	Ampm_SmsTask_Init(Ampm_MainSmsRecvCallback);
	AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_INIT_PHASE \r\n");
	#ifdef CMSIS_OS_RTX
	osThreadCreate (osThread(AMPM_GSM_MainTask), NULL);
	#endif
}

void AMPM_GSM_MainTask(void const * argument)
{
	#ifdef CMSIS_OS_RTX 
	for(;;)
	#endif
	{
		if(ampm_ModemResetFlag)
		{
			ampm_ModemResetFlag = 0;
			ampmGSM_TaskPhase = AMPM_GSM_MAIN_INIT_PHASE;
			AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_INIT_PHASE \r\n");
		}
		if(smsTaskFailCnt >= SMS_MAX_RETRY)
		{
			Ampm_Gsm_Error("Sms service error\r\n");
			smsTaskFailCnt = 0;
		}
		switch(ampmGSM_TaskPhase)
		{
			case AMPM_GSM_MAIN_INIT_PHASE:

				gotoDataModeFlag = 0;
				gotoCmdModeFlag = 0;
				Ampm_RingingReset();
				AMPM_GSM_Startup_Init();
				Ampm_GSM_DialUp_Reset();
				#ifdef PPP_UIP
				PPP_Init();
				#elif defined(PPP_LWIP)
				if(thisPPP>=0)
				{
					pppClose(thisPPP); //0 if ok, else should gen a WARN
					pppSigHUP(thisPPP);
					thisPPP = -1;
				}
				pppInit();
				ppp_status = PPP_DISCONNECTED;
				#endif
				Ampm_TcpIpInit();
				
				Ampm_CallTask_Init(NULL);
				list_init(ampm_GSM_CmdList);
				ampm_GSM_CmdPhase = AMPM_CMD_OK;
				ampmGSM_TaskPhase = AMPM_GSM_MAIN_STARTUP_PHASE;
				AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_STARTUP_PHASE \r\n");
			break;
			case AMPM_GSM_MAIN_STARTUP_PHASE:
				if(AMPM_GSM_Startup((const uint8_t *)ampm_AtGsmCmdStart)){
					//LedSetStatus(&led1Ctr,500,500,LED_TURN_ON,0xffffffff);
					if(Ampm_StartRecvSms())
					{
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_SMS_RECV_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_SMS_RECV_PHASE \r\n");
						break;
					}
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;  
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
				}
			break;
			case	AMPM_GSM_MAIN_SMS_RECV_PHASE:
				if(Ampm_RecvSms_IsFinished()){
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
				}
			break;

			case	AMPM_GSM_MAIN_SMS_SEND_PHASE:
				if(Ampm_SmsTask())
				{
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
				}
			break;
			case	AMPM_GSM_MAIN_VOICECALL_PHASE:
				if(Ampm_CallTask())
				{
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
				}
			break;
			case	AMPM_GSM_MAIN_DATACALL_PHASE:
				gotoDataModeFlag = 0;
				if(gotoCmdModeFlag || ampm_GSM_mode != AMPM_GSM_GPRS_ENABLE){
					//if(CheckTimeout(&tTcpDataIsBusy) == SYSTICK_TIMEOUT 
						//|| Ampm_Ringing_GetPhase() == AMPM_GSM_RING_IS_A_CALL)
					{
						gsmMainTaskTryCnt = 0;
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE \r\n");
					}
				}
				#ifdef PPP_UIP
				PPP_ManageLink();		// if ppp dead
				#endif
				
				#ifdef PPP_UIP
				if(PPP_IsDead())
				#elif defined(PPP_LWIP)
				
				int res = pppInputThread(thisPPP);
				if(res)
				{
					dataSendingTimeout = 3;
				}
				if((res < 0) || ppp_status == PPP_DISCONNECTED)
				#else
				if(1)
				#endif
				{
					Ampm_GSM_DialUp_Reset();
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE \r\n");
				}
				else if((ppp_status == PPP_CONNECTED) && Ampm_TcpIpCallback && Ampm_TcpIpInit)
				{
					Ampm_RingingEnable();
					#ifdef PPP_UIP
					RESOLVER_Manage();
					#elif defined(PPP_LWIP)
					//tcpip_thread(NULL);
					#endif
					if(Ampm_TcpIpCallback())
					{
						#ifdef PPP_UIP
						PPP_Init();
						#elif defined(PPP_LWIP)
						if(thisPPP>=0)
						{
							pppClose(thisPPP); //0 if ok, else should gen a WARN
							pppSigHUP(thisPPP);
							ppp_status = PPP_DISCONNECTED;
							//lwip_init();
							//thisPPP = -1;
						}
						#endif
						Ampm_TcpIpInit();
						Ampm_GSM_DialUp_Reset();
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE \r\n");
					}
				}
				else
				{
					#ifdef PPP_UIP
					RESOLVER_Reset();
					#endif
				}
			break;
			case AMPM_GSM_MAIN_DIAL_UP_PHASE:
				Ampm_GSM_DialUp();
				if(Ampm_GSM_DialUp_IsDone()){
					if(Ampm_GSM_DialUp_IsOk()){
						Ampm_RingingDisable();
						gotoCmdModeFlag = 0;
						#ifdef PPP_UIP
						PPP_SetConnect();
						#elif defined(PPP_LWIP)
						if(thisPPP >=0)
						{
							pppClose(thisPPP); //0 if ok, else should gen a WARN
							pppSigHUP(thisPPP);
						}
						pppSetAuth(PPPAUTHTYPE_PAP, pppUser, pppPass); //TODO: Allow CHAP as well
						thisPPP = pppOverSerialOpen((void*)NULL, status_cb, NULL);
						ppp_status = PPP_CONNECTING;
						#endif
						if(Ampm_TcpIpInit) Ampm_TcpIpInit();
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_DATACALL_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_DATACALL_PHASE \r\n");
					}else{
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
					}
				}
			break;
			case AMPM_GSM_MAIN_GOTO_DATA_MODE_PHASE:
				if(Ampm_GSM_DialUp_IsOk() && ppp_status == PPP_CONNECTED)	{
						if(Ampm_CmdTask_SendCmd(Ampm_MainSwithToIdle,"NO CARRIER",1000, "CONNECT", modemError, 3000, 3, "ATO\r")  == AMPM_GSM_RES_OK){
							ampmGSM_TaskPhase = AMPM_GSM_MAIN_WAIT_GOTO_DATA_MODE_PHASE;
							AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_WAIT_GOTO_DATA_MODE_PHASE \r\n");
						}
				}else{
					Ampm_GSM_DialUp_Reset();
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_DIAL_UP_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_DIAL_UP_PHASE \r\n");
					gotoCmdModeFlag = 0;
					#ifdef PPP_UIP
					PPP_Init();
					#endif
					Ampm_TcpIpInit();
				}
			break;
			case AMPM_GSM_MAIN_WAIT_GOTO_DATA_MODE_PHASE:
				if(Ampm_CmdTask_IsIdle(ampm_GSM_CmdPhase)){
					if(ampm_GSM_CmdPhase == AMPM_CMD_OK){
						gsmMainTaskTryCnt = 0;
						gotoCmdModeFlag = 0;
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_DATACALL_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_DATACALL_PHASE \r\n");
					}else{
						Ampm_GSM_DialUp_Reset();
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE \r\n");
					}
				}
			break;
			case AMPM_GSM_MAIN_GOTO_CMD_MODE_PHASE:
				gsmMainTaskTryCnt = 0;
				Ampm_RingingEnable();
				ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_CMD_MODE_CHECK_PHASE;
				AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_CMD_MODE_CHECK_PHASE \r\n");
				break;
			case AMPM_GSM_MAIN_GOTO_CMD_MODE_CHECK_PHASE:
				if(gsmMainTaskTryCnt && ampm_GSM_CmdPhase == AMPM_CMD_OK)
				{
					gsmMainTaskTryCnt = 0;
					gotoCmdModeFlag = 0;
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
				}
				else if(Ampm_CmdTask_SendCmd(NULL,NULL,500, modemOk, "NO CARRIER", 2000, 0 ,"+++")  == AMPM_GSM_RES_OK){
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_WAIT_GOTO_CMD_MODE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_WAIT_GOTO_CMD_MODE_PHASE \r\n");
				}
			case AMPM_GSM_MAIN_WAIT_GOTO_CMD_MODE_PHASE:
				if(Ampm_CmdTask_IsIdle(ampm_GSM_CmdPhase)){
					if(ampm_GSM_CmdPhase == AMPM_CMD_OK){
						gotoCmdModeFlag = 0;
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_IDLE_PHASE \r\n");
					}else{
						Ampm_CmdTask_SendCmd(NULL,NULL,500, modemOk, modemError, 1000, 1, "AT\r");
						if(gsmMainTaskTryCnt++ < 3){
							ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_CMD_MODE_CHECK_PHASE;
							AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_CMD_MODE_CHECK_PHASE \r\n");
						}else{
							ampmGSM_TaskPhase = AMPM_GSM_MAIN_INIT_PHASE;
							AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_INIT_PHASE \r\n");
						}
					}
				}
			break;
			case	AMPM_GSM_MAIN_IDLE_PHASE:
				if(Ampm_Ringing_GetPhase() == AMPM_GSM_RING_IS_A_CALL)//if have incomming call
				{
					Ampm_VoiceCallStartRecvCall();
					Ampm_RingingReset();
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_VOICECALL_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_VOICECALL_PHASE \r\n");
				}
				else if(!Ampm_VoiceCallCheckList_IsEmpty())
				{
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_VOICECALL_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_VOICE_CALL_OUT_PHASE \r\n");
				}
				else if(ampm_NewSmsFlag || SysTick_Get() - smsCheckTime > AMPM_CHECK_SMS_INTERVAL)
				{
					smsCheckTime = SysTick_Get();
					if(Ampm_StartRecvSms())
					{
						ampm_NewSmsFlag = 0;
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_SMS_RECV_PHASE;
						AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_SMS_RECV_PHASE \r\n");
					}
				}
				else if(!Ampm_SmsCheckMessage_IsEmpty())
				{
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_SMS_SEND_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_SMS_SEND_PHASE \r\n");
				}
				else if(Ampm_Ringing_GetPhase() != AMPM_GSM_RING_IDLE_PHASE)
				{
					break;
				}
				else if(ampm_GSM_mode == AMPM_GSM_GPRS_ENABLE)
				{
					gotoDataModeFlag = 1;
				}
				else if(ampm_GSM_mode == AMPM_GSM_SLEEP_MODE)
				{
					if(Ampm_SendAtCmd(&ampmMainCmdProcess_AT))
					{
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_GO_TO_SLEEP_PHASE;
						break;
					}
				}
				if(gotoDataModeFlag)
				{
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_GOTO_DATA_MODE_PHASE;
					AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_MAIN:AMPM_GSM_MAIN_GOTO_DATA_MODE_PHASE \r\n");
				}
			break;
			case AMPM_GSM_MAIN_GO_TO_SLEEP_PHASE:
				if(Ampm_SendAtCheck_IsEmpty() && Ampm_CmdTask_IsIdle(ampm_GSM_CmdPhase)){
					if(ampm_GSM_CmdPhase == AMPM_CMD_OK){
						#ifdef PPP_UIP
						PPP_Init();
						#endif
						Ampm_TcpIpInit();
						Ampm_GSM_DialUp_Reset();
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_SLEEP_PHASE;
					}else{
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_INIT_PHASE;
					}
				}
			break;
			case AMPM_GSM_MAIN_SLEEP_PHASE:
				if(ampm_GSM_mode != AMPM_GSM_SLEEP_MODE)
				{
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
					MODEM_Wakeup();
					Ampm_SendAtCmdNow(&ampmMainCmdProcess_AT);
					ampmGSM_TaskPhase = AMPM_GSM_MAIN_WAKEUP_PHASE;
				}
			break;
			case AMPM_GSM_MAIN_WAKEUP_PHASE:
				if(Ampm_SendAtCheck_IsEmpty() && Ampm_CmdTask_IsIdle(ampm_GSM_CmdPhase)){
					if(ampm_GSM_CmdPhase == AMPM_CMD_OK){
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_IDLE_PHASE;
					}else{
						ampmGSM_TaskPhase = AMPM_GSM_MAIN_INIT_PHASE;
					}
				}
			break;
			default:
			ampmGSM_TaskPhase = AMPM_GSM_MAIN_INIT_PHASE;
			break;
		}
		
		if(
			(!Ampm_SmsCheckMessage_IsEmpty() 
				|| !Ampm_VoiceCallCheckList_IsEmpty()
				|| Ampm_Ringing_GetPhase() != AMPM_GSM_RING_IDLE_PHASE
				|| ampm_NewSmsFlag
				|| SysTick_Get() - smsCheckTime > AMPM_CHECK_SMS_INTERVAL
			)
			&& (dataSendingTimeout == 0)
		)
		{
			Ampm_GsmGotoCmdMode();
		}

		if(ampmGSM_TaskPhase != AMPM_GSM_MAIN_DATACALL_PHASE)
		{
			ampm_AtCommandParserEnable = 1;
			Ampm_Cmd_Task(&ampm_GSM_CmdPhase,&ampmGSM_CmdSend,ampm_GSM_CmdList,&ampm_GSM_TaskTimeout);
		}

		if(ampmGSM_TaskPhase > AMPM_GSM_MAIN_STARTUP_PHASE){
			Ampm_RingingProcess();
		}

		if(CheckTimeout(&tRingTask) == SYSTICK_TIMEOUT)
		{
			if(dataSendingTimeout) dataSendingTimeout--;
			InitTimeout(&tRingTask,SYSTICK_TIME_SEC(1));
			Ampm_RingingTimer();
			Ampm_SmsTaskPeriodic_1Sec();
			Ampm_CallTaskPeriodic_1Sec();
		}
	}
}




extern const uint8_t ampm_AtGsmCmdStartBG2_E[];
extern const uint8_t ampm_AtGsmCmdStartBGS2_E[];
extern const uint8_t ampm_AtGsmCmdStartM95[];
extern const uint8_t ampm_AtGsmCmdStartM26[];

AMPM_GSM_MODULE_TYPE ampmGsmModuleType = THIS_MODULE_NOT_SUPPORT;

COMPARE_TYPE cmpBGS2_W;
COMPARE_TYPE cmpBGS2_E;
COMPARE_TYPE cmpBG2_E;
COMPARE_TYPE cmpM95;
COMPARE_TYPE cmpM26;
COMPARE_TYPE cmpUbloxG100;
COMPARE_TYPE cmp;
COMPARE_TYPE cmpSIM900;

uint32_t Ampm_GSM_GetATI(uint16_t cnt,uint8_t c)
{
	

	if(cnt == 0)
	{
		InitFindData(&cmp,"\r\nOK");
		InitFindData(&cmpBGS2_W,"BGS2-W");
		InitFindData(&cmpBGS2_E,"BGS2-E");
		InitFindData(&cmpBG2_E,"BG2-E");
		InitFindData(&cmpM95,"M95");
		InitFindData(&cmpM26,"M26");
		InitFindData(&cmpSIM900,"SIM900");
		InitFindData(&cmpUbloxG100,"G100");
	}
	if(FindData(&cmp,c) == 0 || cnt >= 45)
	{
		AMPM_GSM_LIB_DBG("\r\n AMPM_GSM_INIT:Got ATI \r\n");
		if(ampmGsmModuleType == THIS_MODULE_NOT_SUPPORT)
		{
			#ifdef PPP_UIP
			PPP_SetAuthenticationLogin(1);
			#endif
			AMPM_GSM_LIB_DBG("\r\n Sorry we do not support your module \r\n");
			AMPM_GSM_LIB_DBG("\r\n Pls contact thienhaiblue@gmail.com to have a good support \r\n");
			AMPM_GSM_LIB_DBG("\r\n Thanks! \r\n");
		}
		return 0;
	}
	if(FindData(&cmpBGS2_W,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(1);
		#endif
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpBGS2_W.buff);
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartBGS2_W;
		ampmGsmModuleType = BGS2_W;
		return 0;
	}
	if(FindData(&cmpBGS2_E,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(1);
		#endif
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpBGS2_E.buff);
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartBGS2_E;
		ampmGsmModuleType = BGS2_E;
		return 0;
	}
	if(FindData(&cmpBG2_E,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(1);
		#endif
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartBG2_E;
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpBG2_E.buff);
		ampmGsmModuleType = BG2_E;
		return 0;
	}
	if(FindData(&cmpM95,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(1);
		#endif
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartM95;
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpM95.buff);
		ampmGsmModuleType = M95;
		return 0;
	}
	if(FindData(&cmpM26,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(1);
		#endif
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartM26;
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpM26.buff);
		ampmGsmModuleType = M26;
		return 0;
	}
	if(FindData(&cmpSIM900,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(1);
		#endif
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartSIM900;
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpSIM900.buff);
		ampmGsmModuleType = SIM900;
		return 0;
	}
	if(FindData(&cmpUbloxG100,c) == 0)
	{
		#ifdef PPP_UIP
		PPP_SetAuthenticationLogin(0);
		#endif
		ampm_AtGsmCmdStart_pt = (uint8_t *)ampm_AtGsmCmdStartUbloxG100;
		AMPM_GSM_LIB_DBG("\r\n YOUR MODULE IS:Got ATI:%s \r\n",cmpM95.buff);
		ampmGsmModuleType = UBLOX_G100;
		return 0;
	}
	return 0xff;
}

