#include "directionallight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction,
                                   QColor color,
                                   GLfloat diffuseIntensity,
                                   GLfloat ambientIntensity)
    :Light(color,ambientIntensity),diffuseIntensity(diffuseIntensity)
{
    this->direction=-direction;
}
