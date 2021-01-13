//
//  LFile.c
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#include "LFile.h"
#include <stdlib.h>
#include <stdarg.h>

int lglstring_alloc_from_file(const char *fp, char **buf, long *size)
{
    FILE *f = fopen(fp, "r");
    if (!f) {
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long s = ftell(f);
    rewind(f);
    *buf = (char *)malloc(s);
    fread(*buf, s, 1, f);
    fclose(f);
    if (size)
        *size = s;
    return 0;
}

void lgl_free_p(void **s)
{
    if (s && *s) {
        free(*s);
        *s = NULL;
    }
}

