//
//  LGLRenderTexture.h
//  LearnOpenGL
//
//  Created by zuer on 2021/1/13.
//

#ifndef LGLRenderTexture_h
#define LGLRenderTexture_h

#include <stdio.h>
#include <string.h>
#include "LGLProgram.h"

struct LGLRenderTextureObject{
    GLuint VBO;
    GLuint VAO;
    GLuint lightVAO;
    GLuint texture;
};

LGLViewProtocol lgl_texture_protocol(void);

#endif /* LGLRenderTexture_h */
