//
//  LGLTexture.h
//  LearnOpenGL
//
//  Created by zuer on 2021/1/13.
//

#ifndef LGLTexture_h
#define LGLTexture_h

#include <stdio.h>
#include "LGLProgram.h"

int lgl_alloc_texture(const char *name, GLuint *tid);

int lgl_free_texture(GLuint *tid);

#endif /* LGLTexture_h */
