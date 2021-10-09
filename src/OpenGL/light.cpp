#include "light.h"
#include "Shaders/lightshader.h"
#include <QDebug>

Light::Light(glm::vec3 direction, QColor color,
      GLfloat diffuseIntensity, GLfloat ambientIntensity)
    :color(color),diffuseIntensity(diffuseIntensity),ambientIntensity(ambientIntensity)
{
    initializeOpenGLFunctions();
    this->direction=-direction;
}

void Light::useLight(LightShader*shader){
    shader->useShader();
    GLuint lightColorLocation=shader->getLightColorLocation();
    GLuint ambientIntensityLocation=shader->getAmbientIntensityLocation();
    GLuint directionLocation=shader->getDirectionLocation();
    GLuint diffuseIntensityLocation=shader->getDiffuseIntensityLocation();

    glUniform3f(lightColorLocation,color.redF(),color.greenF(),color.blueF());
    glUniform1f(ambientIntensityLocation,ambientIntensity);

    glUniform3f(directionLocation,direction.x,direction.y,direction.z);
    glUniform1f(diffuseIntensityLocation,diffuseIntensity);
    shader->unUseShader();
}
