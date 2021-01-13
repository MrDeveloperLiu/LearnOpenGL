//
//  LGLTexture.c
//  LearnOpenGL
//
//  Created by zuer on 2021/1/13.
//

#include "LGLTexture.h"

int lgl_alloc_texture(const char *name, GLuint *tid)
{
    if (!tid) {
        return -1;
    }
    GLsizei width = 0;
    GLsizei height = 0;
    uint8_t *data = NULL;
    size_t data_size = 0;
    lgl_read_jpg(name, &width, &height, &data, &data_size);
    
    glGenTextures(1, tid);
    glBindTexture(GL_TEXTURE_2D, *tid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    lgl_free_p((void **)&data);
    return 0;
}

int lgl_free_texture(GLuint *tid)
{
    if (!tid) {
        return -1;
    }
    glDeleteTextures(1, tid);
    return 0;
}
