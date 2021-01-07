//
//  LGLRenderRect.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#ifndef LGLRenderRect_h
#define LGLRenderRect_h

#include <stdio.h>
#include <string.h>
#include "LGLProgram.h"

struct LGLRenderRectObject{
    GLuint triangleVBO;
    GLuint triangleEBO;
};


LGLViewProtocol lgl_rect_protocol(void);

#endif /* LGLRenderRect_h */
