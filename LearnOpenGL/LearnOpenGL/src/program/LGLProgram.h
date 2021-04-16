//
//  LGLProgram.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#ifndef LGLProgram_h
#define LGLProgram_h

#include <stdio.h>

#import <OpenGLES/gltypes.h>
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>

#include "LFile.h"
#include "LGLBridgeOC.h"

struct LGLProgram {
    GLuint handle;    //程序句柄
    GLuint v_shader_handle;    //顶点着色器
    GLuint f_shader_handle;    //片段着色器
};
typedef struct LGLProgram LGLProgram;

LGLProgram lglprogram_make(void);
int lglprogram_init(LGLProgram *prog, const char *vsh, const char *fsh);
void lglprogram_deinit(LGLProgram *prog);
void lglprogram_use(LGLProgram *prog);

void lglprogram_set_vec3(LGLProgram *prog, const GLchar *name, GLfloat x, GLfloat y, GLfloat z);
void lglprogram_set_vec4(LGLProgram *prog, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void lglprogram_set_float(LGLProgram *prog, const GLchar *name, GLfloat v);
void lglprogram_set_int(LGLProgram *prog, const GLchar *name, GLint v);

#define kMVPNameSize 64

struct LGLViewProtocol {
    LGLProgram program;
    LGLProgram light_program;

    void       *ctx;
    
    GLchar     m_name[kMVPNameSize];
    GLchar     v_name[kMVPNameSize];
    GLchar     p_name[kMVPNameSize];
    
    void (*start)(struct LGLViewProtocol *protocol);
    void (*stop)(struct LGLViewProtocol *protocol);
    void (*create_program)(struct LGLViewProtocol *protocol);
    void (*delete_program)(struct LGLViewProtocol *protocol);
    void (*render)(struct LGLViewProtocol *protocol);
    void (*clear)(struct LGLViewProtocol *protocol);
    
    void       *bridge_ctx;
    void (*mvp_bridge)(struct LGLViewProtocol *protocol, GLuint program);
    void (*mvp_light_bridge)(struct LGLViewProtocol *protocol, GLuint program, GLfloat p[3]);
    void (*viewport_bridge)(struct LGLViewProtocol *protocol);
    
    void (*camera_eye)(struct LGLViewProtocol *protocol, GLfloat *pos, GLfloat *front);
    
    void       *info;
};
typedef struct LGLViewProtocol LGLViewProtocol;



#endif /* LGLProgram_h */


