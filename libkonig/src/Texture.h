#ifndef KONIG_TEXTURE_H
#define KONIG_TEXTURE_H

#include <stdint.h>

#include "gl.h"

class Texture {
public:
    Texture(uint16_t size, bool init);
    ~Texture();

    uint16_t size;
    GLuint id;

    void bind(GLuint textureUnit);
    void unbind();
};

#endif
