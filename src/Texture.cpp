#include "Texture.h"

Texture::Texture(uint16_t size, bool init) {
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);;
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    if (init)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size/2, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(GLuint textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
