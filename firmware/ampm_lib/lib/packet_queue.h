#ifndef _PACKET_QUEUE_H_
#define _PACKET_QUEUE_H_

#include "ringbuf.h"

#ifdef __cplusplus
 extern "C" {
#endif

int16_t PQUEUE_Put(RINGBUF *r, uint8_t *packet);
int16_t PQUEUE_Get(RINGBUF *r, uint8_t *buf, int16_t bufSize);

int16_t APQUEUE_Put(RINGBUF *r, uint8_t *packet);
int16_t APQUEUE_Get(RINGBUF *r, uint8_t *buf, int16_t bufSize);
#ifdef __cplusplus
}
#endif
#endif
