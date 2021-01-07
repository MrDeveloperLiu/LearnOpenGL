//
//  LGLRenderRect.c
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#include "LGLRenderRect.h"

#define kElementsDraw 0
#define kEnableMVP 1

void start_r(struct LGLViewProtocol *protocol)
{
    glEnable(GL_DEPTH_TEST);
}

void stop_r(struct LGLViewProtocol *protocol)
{
    glFinish();
}

void create_program_r(struct LGLViewProtocol *protocol)
{
    protocol->program = lglprogram_make();
    if (lglprogram_init(&protocol->program, "Vertex-Rect.glsl", "Fragment-Rect.glsl") != 0) {
        return;
    }
    lglprogram_use(&protocol->program);
        
#if kElementsDraw
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };
    struct LGLRenderRectObject *rect = (struct LGLRenderRectObject *)protocol->ctx;
    glGenBuffers(1, &rect->triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rect->triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint index[] = {
        0, 1, 2,
        3, 0, 2
    };
    glGenBuffers(1, &rect->triangleEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect->triangleEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
#else
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,            
    };
    struct LGLRenderRectObject *rect = (struct LGLRenderRectObject *)protocol->ctx;
    glGenBuffers(1, &rect->triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rect->triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
#endif
}

void delete_program_r(struct LGLViewProtocol *protocol)
{
    struct LGLRenderRectObject *rect = (struct LGLRenderRectObject *)protocol->ctx;
    if (rect->triangleVBO) {
        glDeleteBuffers(1, &rect->triangleVBO);
    }
#if kElementsDraw
    if (rect->triangleEBO) {
        glDeleteBuffers(1, &rect->triangleEBO);
    }
#endif
    lglprogram_deinit(&protocol->program);
}

void render_r(struct LGLViewProtocol *protocol)
{
    protocol->viewport_bridge(protocol);
    
    GLuint pid = glGetAttribLocation(protocol->program.handle, "aPos");
    glVertexAttribPointer(pid, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(pid);

    GLfloat color[] = {
        1.0, 1.0, 0.0, 1.0
    };
    GLuint cid = glGetAttribLocation(protocol->program.handle, "aColor");
    glVertexAttrib4fv(cid, color);
    
#if kEnableMVP
    protocol->mvp_bridge(protocol, protocol->program.handle);
#endif
    
#if kElementsDraw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#else
    glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
}

void clear_r(struct LGLViewProtocol *protocol)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


LGLViewProtocol lgl_rect_protocol(void)
{
    struct LGLRenderRectObject obj = {0};
    LGLViewProtocol p = {0};    
    p.ctx = &obj;
    p.start = start_r;
    p.stop = stop_r;
    p.create_program = create_program_r;
    p.delete_program = delete_program_r;
    p.render = render_r;
    p.clear = clear_r;
    return p;
}
