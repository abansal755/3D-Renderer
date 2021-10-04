#include <QOpenGLFunctions_3_3_Core>

class Texture: protected QOpenGLFunctions_3_3_Core{
    GLuint textureId = 0;
    int width = 0, height = 0, bitDepth = 0;

    Texture(const Texture& texture);
    Texture operator=(const Texture& texture);
public:
    Texture();
    Texture(std::string& fileLoc);
    ~Texture();

    void loadTexture(std::string& fileLoc);
    void clearTexture();

    void useTexture();
    void unUseTexture();

    bool empty() { return (textureId == 0); }
};
