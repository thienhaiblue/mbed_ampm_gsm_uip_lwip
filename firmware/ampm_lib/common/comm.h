
#ifndef __COMM_H__
#define __COMM_H__
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lib/ringbuf.h"
#define AMPM_GSM_OS_RTX
#ifdef __cplusplus
 extern "C" {
#endif
	 

//extern int  printf(const uint8_t *format, ...);

#define PPP_Info(...)		printf(__VA_ARGS__)

#define PPP_Debug(...)	printf(__VA_ARGS__)
#define AT_CMD_Debug(...)	printf(__VA_ARGS__)
#define UIP_PPP_Info(...) printf(__VA_ARGS__)
#define AMPM_GSM_LIB_DBG(...) printf(__VA_ARGS__)
#define MODEM_Info(...)		printf(__VA_ARGS__)


extern  void COMM_Putc(uint8_t c);
extern  int32_t COMM_Getc(uint8_t *c);
extern  void COMM_ClearTx(void);
extern  void COMM_Puts(uint8_t *s);
extern  uint8_t COMM_CarrierDetected(void);
extern  void MODEM_RTS_Set(void);
extern  void MODEM_RTS_Clr(void);
extern  void MODEM_DTR_Set(void);
extern  void MODEM_DTR_Clr(void);
extern  void MODEM_MOSFET_On(void);
extern  void MODEM_MOSFET_Off(void);
extern  void MODEM_POWER_Set(void);
extern  void MODEM_POWER_Clr(void);
extern  void MODEM_RESET_Set(void);
extern  void MODEM_RESET_Clr(void);
extern  void MODEM_Wakeup(void);
extern  void MODEM_UartInit(uint32_t baudrate);
#ifdef __cplusplus
}
#endif

#endif
