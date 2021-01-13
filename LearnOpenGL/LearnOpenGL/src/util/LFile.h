//
//  LFile.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#ifndef LFile_h
#define LFile_h

#include <stdio.h>
#include "LLog.h"

int lglstring_alloc_from_file(const char *fp, char **buf, long *size);

void lgl_free_p(void **s);


#endif /* LFile_h */
