#ifndef _FCS_H_
#define _FCS_H_
#include <stdint.h>


#ifdef __cplusplus
 extern "C" {
#endif


uint16_t FCS_Get(uint8_t *cp, uint32_t len);
uint16_t FCS_Calculate(uint8_t val, uint16_t fcs);
#ifdef __cplusplus
}
#endif
#endif
