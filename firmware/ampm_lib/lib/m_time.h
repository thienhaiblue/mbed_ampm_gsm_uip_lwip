#ifndef __M_TIME_H__
#define __M_TIME_H__
#include <time.h>

#ifdef __cplusplus
 extern "C" {
#endif

struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf);
time_t mktime(struct tm *tmbuf);
#ifdef __cplusplus
}
#endif
#endif

