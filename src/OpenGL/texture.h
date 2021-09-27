#include "version.h"

class Texture{
    GLuint textureId = 0;
    int width = 0, height = 0, bitDepth = 0;

    Texture(const Texture& texture);
    Texture operator=(const Texture& texture);
public:
    Texture() {};
    Texture(std::string& fileLoc);
    ~Texture();

    void loadTexture(std::string& fileLoc);
    void clearTexture();

    void useTexture();
    static void unUseTexture();

    bool empty() { return (textureId == 0); }
};
