#include "light.h"
#include "Shaders/lightshader.h"
#include <QDebug>

Light::Light(glm::vec3 direction, QColor color,
      GLfloat diffuseIntensity, GLfloat ambientIntensity)
    :color(color),diffuseIntensity(diffuseIntensity),ambientIntensity(ambientIntensity)
{
    this->direction=-direction;
}

void Light::useLight(LightShader*shader){
    shader->useShader();
    GLuint lightColorLocation=shader->getLightColorLocation();
    GLuint ambientIntensityLocation=shader->getAmbientIntensityLocation();
    GLuint directionLocation=shader->getDirectionLocation();
    GLuint diffuseIntensityLocation=shader->getDiffuseIntensityLocation();

    gl()->glUniform3f(lightColorLocation,color.redF(),color.greenF(),color.blueF());
    gl()->glUniform1f(ambientIntensityLocation,ambientIntensity);

    gl()->glUniform3f(directionLocation,direction.x,direction.y,direction.z);
    gl()->glUniform1f(diffuseIntensityLocation,diffuseIntensity);
    Shader::unUseShader();
}
