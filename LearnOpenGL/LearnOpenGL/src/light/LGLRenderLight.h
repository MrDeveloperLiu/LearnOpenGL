//
//  LGLRenderLight.h
//  LearnOpenGL
//
//  Created by zuer on 2021/1/4.
//

#ifndef LGLRenderLight_h
#define LGLRenderLight_h

#include <stdio.h>
#include <string.h>
#include "LGLProgram.h"

struct LGLRenderLightObject{
    GLuint VBO;
    GLuint VAO;
    GLuint lightVAO;
};

LGLViewProtocol lgl_light_protocol(void);

#endif /* LGLRenderLight_h */
