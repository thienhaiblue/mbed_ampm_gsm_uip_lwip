
#ifndef __AMPM_SPRINTF___
#define __AMPM_SPRINTF___
#include "stdint.h"
#include "stdarg.h"

#ifdef __cplusplus
 extern "C" {
#endif
int ampm_vsprintf (char *fp,
	const char* format,	/* Pointer to the format string */
	va_list arg					/* Optional arguments... */
);

int  ampm_sprintf(char *fp,const char *format, ...);
#ifdef __cplusplus
}
#endif
#endif
