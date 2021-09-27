#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"
#include "lib/stb_image.h"

#include <QDebug>

Texture::Texture(std::string& fileLoc) {
    loadTexture(fileLoc);
}

Texture::~Texture() {
    if (textureId) gl()->glDeleteTextures(1, &textureId);
}

void Texture::loadTexture(std::string& fileLoc) {
    clearTexture();

    unsigned char* texData = stbi_load(&fileLoc[0], &width, &height, &bitDepth, 0);
    if (!texData) {
        qDebug() << "Unable to load from "+QString::fromStdString(fileLoc);
        return;
    }

    gl()->glGenTextures(1, &textureId);
    gl()->glBindTexture(GL_TEXTURE_2D, textureId);
    gl()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gl()->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    gl()->glGenerateMipmap(GL_TEXTURE_2D);
    gl()->glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);
}

void Texture::clearTexture() {
    if (textureId) {
        gl()->glDeleteTextures(1, &textureId);
        textureId = 0;
    }
    width = 0;
    height = 0;
    bitDepth = 0;
}

void Texture::useTexture() {
    gl()->glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unUseTexture() {
    gl()->glBindTexture(GL_TEXTURE_2D, 0);
}
