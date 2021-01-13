//
//  LLog.c
//  LearnOpenGL
//
//  Created by zuer on 2021/1/13.
//

#include "LLog.h"
#include <stdlib.h>
#include <stdarg.h>

void lgl_log(int level, const char *tag, const char *fmt, ...)
{
    if (!(lgl_level & level)) {
        return;
    }
    char message[1024];
    va_list arg;
    va_start(arg, fmt);
    vsprintf(message, fmt, arg);
    va_end(arg);
    printf("L: [%s] %s \n", tag, message);
}
