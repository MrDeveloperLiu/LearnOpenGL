//
//  LFile.c
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#include "LFile.h"
#include <stdlib.h>
#include <stdarg.h>

char *lglstring_alloc_from_file(const char *fp, long *size)
{
    FILE *f = fopen(fp, "r");
    if (!f) {
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    long s = ftell(f);
    rewind(f);
    char *code = (char *)malloc(s);
    fread(code, s, 1, f);
    fclose(f);
    if (size)
        *size = s;
    return code;
}

void lglstring_free(void **s)
{
    if (s && *s) {
        free(*s);
        *s = NULL;
    }
}

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
