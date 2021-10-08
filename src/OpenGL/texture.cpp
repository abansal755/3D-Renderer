#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"
#include "lib/stb_image.h"

#include <QDebug>

Texture::Texture(){
    initializeOpenGLFunctions();
}

Texture::Texture(QString& fileLoc) {
    loadTexture(fileLoc);
}

Texture::~Texture() {
    if (textureId) glDeleteTextures(1, &textureId);
}

void Texture::loadTexture(QString& fileLoc) {
    clearTexture();
    std::string stdFileLoc=fileLoc.toStdString();

    unsigned char* texData = stbi_load(&stdFileLoc[0], &width, &height, &bitDepth, 0);
    if (!texData) {
        qDebug() << "Unable to load from "+fileLoc;
        return;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texData);
}

void Texture::clearTexture() {
    if (textureId) {
        glDeleteTextures(1, &textureId);
        textureId = 0;
    }
    width = 0;
    height = 0;
    bitDepth = 0;
}

void Texture::useTexture() {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unUseTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
