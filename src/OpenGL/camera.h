#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "version.h"

const float PI = 3.1415926535;

class GLWidget;

class Camera{
    glm::vec3 pos,front,up,right,worldUp;
    GLfloat yaw,pitch;
    GLfloat moveSpeed,turnSpeed;
    GLfloat fov,aspect,zNear,zFar;

    void update();
public:
    Camera(glm::vec3 startPos=glm::vec3(0, 0, 0), glm::vec3 startWorldUp=glm::vec3(0, 1, 0),
           GLfloat startYaw=0, GLfloat startPitch=0,
           GLfloat startMoveSpeed=10, GLfloat startTurnSpeed=0.005,
           GLfloat fov=PI/4, GLfloat aspect=1, GLfloat zNear=0.01, GLfloat zFar=100);

    void keyControl(GLWidget* glwidget, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);

    glm::mat4 calculateViewMatrix();
    glm::mat4 calculateProjectionMatrix();

    void setPos(glm::vec3 pos) { this->pos = pos; }
    glm::vec3 getPos() { return pos; }
    glm::vec3 getFront(){return front;}

    void setWorldUp(glm::vec3 worldUp);
    glm::vec3 getWorldUp() { return worldUp; }

    void setYaw(GLfloat yaw);
    GLfloat getYaw() { return yaw; }
    void setPitch(GLfloat pitch);
    GLfloat getPitch() { return pitch; }

    void setMoveSpeed(GLfloat moveSpeed) { this->moveSpeed = moveSpeed; }
    GLfloat getMoveSpeed() { return moveSpeed; }
    void setTurnSpeed(GLfloat turnSpeed) { this->turnSpeed = turnSpeed; }
    GLfloat getTurnSpeed() { return turnSpeed; }

    void setFov(GLfloat fov) { this->fov = fov; }
    GLfloat getFov() { return fov; }
    void setAspect(GLfloat aspect) { this->aspect = aspect; }
    GLfloat getAspect() { return aspect; }
    void setZNear(GLfloat zNear) { this->zNear = zNear; }
    GLfloat getZNear() { return zNear; }
    void setZFar(GLfloat zFar) { this->zFar = zFar; }
    GLfloat getZFar() { return zFar; }
};
