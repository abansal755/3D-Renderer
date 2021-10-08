#include "../light.h"

class DirectionalLight : public Light{
    glm::vec3 direction;
    GLfloat diffuseIntensity;
public:
    DirectionalLight(glm::vec3 direction=glm::vec3(0,-1,0),
                     QColor color=QColor(Qt::white),
                     GLfloat diffuseIntensity=1,
                     GLfloat ambientIntensity=0.5);

    void setDirection(glm::vec3 direction){this->direction=-direction;}
    glm::vec3 getDirection(){return direction;}
    void setDiffuseIntensity(GLfloat diffuseIntensity){this->diffuseIntensity=diffuseIntensity;}
    GLfloat getDiffuseIntensity(){return diffuseIntensity;}
};
