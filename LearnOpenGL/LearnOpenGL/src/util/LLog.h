//
//  LLog.h
//  LearnOpenGL
//
//  Created by zuer on 2021/1/13.
//

#ifndef LLog_h
#define LLog_h

#include <stdio.h>

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

#endif /* LLog_h */
