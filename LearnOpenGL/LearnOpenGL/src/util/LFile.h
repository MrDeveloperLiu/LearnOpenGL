//
//  LFile.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#ifndef LFile_h
#define LFile_h

#include <stdio.h>

char *lglstring_alloc_from_file(const char *fp, long *size);

void lglstring_free(void **s);


//日志系统

enum LglLogLevel{
    LglLogLevelDebug = (1 << 0),
    LglLogLevelRelease = (1 << 1),
};
#ifdef DEBUG
static int lgl_level = LglLogLevelDebug | LglLogLevelRelease;
#else
static int lgl_level = LglLogLevelRelease;
#endif

void lgl_log(int level, const char *tag, const char *fmt, ...);

#define LGL_LOGD(fmt, ...) lgl_log(LglLogLevelDebug, "DEBUG", fmt, __VA_ARGS__)

#define LGL_LOGR(fmt, ...) lgl_log(LglLogLevelRelease, "RELEASE", fmt, __VA_ARGS__)

#endif /* LFile_h */
