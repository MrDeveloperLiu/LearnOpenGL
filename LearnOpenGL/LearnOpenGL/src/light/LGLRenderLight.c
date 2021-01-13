//
//  LGLRenderLight.c
//  LearnOpenGL
//
//  Created by zuer on 2021/1/4.
//

#include "LGLRenderLight.h"
#include <sys/time.h>
#include <math.h>
#include <stdlib.h>

void start_l(struct LGLViewProtocol *protocol)
{
    protocol->ctx = calloc(1, sizeof(struct LGLRenderLightObject));
    glEnable(GL_DEPTH_TEST);
}

void stop_l(struct LGLViewProtocol *protocol)
{
    if (protocol->ctx) {
        free(protocol->ctx);
    }
    glFinish();
}

void create_program_l(struct LGLViewProtocol *protocol)
{
    struct LGLRenderLightObject *ctx = (struct LGLRenderLightObject *)protocol->ctx;

    protocol->program = lglprogram_make();
    if (lglprogram_init(&protocol->program, "Vertex-Light.glsl", "Fragment-Light.glsl") != 0) {
        return;
    }
    strcpy(protocol->m_name, "model");
    strcpy(protocol->v_name, "view");
    strcpy(protocol->p_name, "projection");
        
    GLfloat vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
    
    glGenVertexArrays(1, &ctx->VAO);
    glBindVertexArray(ctx->VAO);
    glGenBuffers(1, &ctx->VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, ctx->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //顶点
    GLuint pidx = glGetAttribLocation(protocol->program.handle, "aPos");
    glVertexAttribPointer(pidx, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(pidx);
    //法线    
    GLuint nidx = glGetAttribLocation(protocol->program.handle, "aNormal");
    glVertexAttribPointer(nidx, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(nidx);
    
    protocol->light_program = lglprogram_make();
    if (lglprogram_init(&protocol->light_program, "Vertex-LightCube.glsl", "Fragment-LightCube.glsl") != 0) {
        return;
    }
    glGenVertexArrays(1, &ctx->lightVAO);
    glBindVertexArray(ctx->lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, ctx->VBO);
    
    GLuint lpidx = glGetAttribLocation(protocol->light_program.handle, "aPos");
    glVertexAttribPointer(lpidx, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(lpidx);
}

void delete_program_l(struct LGLViewProtocol *protocol)
{
    struct LGLRenderLightObject *ctx = (struct LGLRenderLightObject *)protocol->ctx;
    if (ctx->VBO) {
        glDeleteBuffers(1, &ctx->VBO);
    }
    if (ctx->VAO) {
        glDeleteVertexArrays(1, &ctx->VAO);
    }
    if (ctx->lightVAO) {
        glDeleteVertexArrays(1, &ctx->lightVAO);
    }
    lglprogram_deinit(&protocol->program);
    lglprogram_deinit(&protocol->light_program);
}

void render_l(struct LGLViewProtocol *protocol)
{
    struct LGLRenderLightObject *ctx = (struct LGLRenderLightObject *)protocol->ctx;

    protocol->viewport_bridge(protocol);
    
    GLfloat lightPos[3] = {1.2, 1.0, 2.0};
    GLfloat cameraEyes[3] = {0};
    protocol->camera_eye(protocol, cameraEyes, NULL);
    
    lglprogram_use(&protocol->program);
    lglprogram_set_vec3(&protocol->program, "viewPos", cameraEyes[0], cameraEyes[1], cameraEyes[2]);
    lglprogram_set_vec3(&protocol->program, "light.position", lightPos[0], lightPos[1], lightPos[2]);
    
    lglprogram_set_vec3(&protocol->program, "light.ambient", 0.1, 0.1, 0.1);
    lglprogram_set_vec3(&protocol->program, "light.diffuse", 0.5, 0.5, 0.5);
    lglprogram_set_vec3(&protocol->program, "light.specular", 1.0, 1.0, 1.0);
    
    lglprogram_set_vec3(&protocol->program, "material.ambient", 1.0, 0.5, 0.31);
    lglprogram_set_vec3(&protocol->program, "material.diffuse", 1.0, 0.5, 0.31);
    lglprogram_set_vec3(&protocol->program, "material.specular", 0.5, 0.5, 0.5);
    lglprogram_set_float(&protocol->program, "material.shininess", 32.0);
    protocol->mvp_bridge(protocol, protocol->program.handle);
    glBindVertexArray(ctx->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    lglprogram_use(&protocol->light_program);
    
    protocol->mvp_light_bridge(protocol, protocol->light_program.handle, lightPos);
    glBindVertexArray(ctx->lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void clear_l(struct LGLViewProtocol *protocol)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


LGLViewProtocol lgl_light_protocol(void)
{
    LGLViewProtocol p = {0};
    p.start = start_l;
    p.stop = stop_l;
    p.create_program = create_program_l;
    p.delete_program = delete_program_l;
    p.render = render_l;
    p.clear = clear_l;
    return p;
}
