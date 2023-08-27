#include "SEGGER_RTT.h"

#include "log.h"


extern void printLog(const char * sFormat, ...)
{
    SEGGER_RTT_printf(0, sFormat);
}
