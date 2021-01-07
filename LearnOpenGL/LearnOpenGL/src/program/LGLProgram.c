//
//  LGLProgram.c
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#include "LGLProgram.h"

LGLProgram lglprogram_make(void)
{
    LGLProgram p = {0};
    return p;
}

int lglprogram_create_shader(const GLchar *shader_code, GLint shader_len, GLenum shader_type, GLuint *shader_handle)
{
    if (!shader_handle) {
        return -1;
    }
    *shader_handle = glCreateShader(shader_type);
    glShaderSource(*shader_handle, 1, &shader_code, &shader_len);
    glCompileShader(*shader_handle);
    GLint state;
    glGetShaderiv(*shader_handle, GL_COMPILE_STATUS, &state);
    if (state == GL_FALSE) {
        char messages[256];
        glGetShaderInfoLog(*shader_handle, sizeof(messages), 0, &messages[0]);
        LGL_LOGD("glCompileShader error: %s", messages);
        return -2;
    }
    return 0;
}

void lglprogram_delete_shader(GLuint *shader)
{
    if (shader && *shader) {
        glDeleteShader(*shader);
    }
}

int lglprogram_create_program(GLuint *program_handle, GLuint vsh, GLuint fsh)
{
    if (!program_handle) {
        return -1;
    }
    *program_handle = glCreateProgram();
    glAttachShader(*program_handle, vsh);
    glAttachShader(*program_handle, fsh);
    glLinkProgram(*program_handle);
    GLint state;
    glGetProgramiv(*program_handle, GL_LINK_STATUS, &state);
    if (state == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(*program_handle, sizeof(messages), 0, &messages[0]);
        LGL_LOGD("glLinkProgram error: %s", messages);
        return -2;
    }
    return 0;
}

void lglprogram_delete_program(GLuint *program)
{
    if (program && *program) {
        glDeleteProgram(*program);
    }
}

int lglprogram_init(LGLProgram *prog, const char *vsh, const char *fsh)
{
    if (!prog) {
        return -1;
    }
    long vlen;
    char *vsh_code = lglstring_alloc_from_file(lgl_filepath(vsh), &vlen);
    int ret = lglprogram_create_shader((const GLchar *)vsh_code, (GLint)vlen, GL_VERTEX_SHADER, &prog->v_shader_handle);
    if (ret != 0){
        LGL_LOGD("GL_VERTEX_SHADER create fail %d", ret);
        goto fail;
    }
    lglstring_free((void**)&vsh_code);
    
    long flen;
    char *fsh_code = lglstring_alloc_from_file(lgl_filepath(fsh), &flen);
    ret = lglprogram_create_shader((const GLchar *)fsh_code, (GLint)flen, GL_FRAGMENT_SHADER, &prog->f_shader_handle);
    if (ret != 0){
        LGL_LOGD("GL_FRAGMENT_SHADER create fail %d", ret);
        goto fail;
    }
    lglstring_free((void**)&fsh_code);
    
    ret = lglprogram_create_program(&prog->handle, prog->v_shader_handle, prog->f_shader_handle);
    if (ret != 0){
        goto fail;
    }
    lglprogram_delete_shader(&prog->f_shader_handle);
    lglprogram_delete_shader(&prog->v_shader_handle);
    return 0;
    
fail:
    lglstring_free((void**)&vsh_code);
    lglstring_free((void**)&fsh_code);
    lglprogram_deinit(prog);
    return -2;
}

void lglprogram_deinit(LGLProgram *prog)
{
    lglprogram_delete_shader(&prog->f_shader_handle);
    lglprogram_delete_shader(&prog->v_shader_handle);
    lglprogram_delete_program(&prog->handle);
}

void lglprogram_use(LGLProgram *prog)
{
    if (prog) {
        glUseProgram(prog->handle);
    }
}

void lglprogram_set_vec3(LGLProgram *prog, const GLchar *name, GLfloat x, GLfloat y, GLfloat z)
{
    if (prog) {
        glUniform3f(glGetUniformLocation(prog->handle, name), x, y, z);
    }
}

void lglprogram_set_vec4(LGLProgram *prog, const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    if (prog) {
        glUniform4f(glGetUniformLocation(prog->handle, name), x, y, z, w);
    }
}

void lglprogram_set_float(LGLProgram *prog, const GLchar *name, GLfloat v)
{
    if (prog) {
        glUniform1f(glGetUniformLocation(prog->handle, name), v);
    }
}
