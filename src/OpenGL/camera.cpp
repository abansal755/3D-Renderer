#include "camera.h"
#include "src/GUI/glwidget.h"

Camera::Camera(glm::vec3 startPos, glm::vec3 startWorldUp,
               GLfloat startYaw, GLfloat startPitch,
               GLfloat startMoveSpeed, GLfloat startTurnSpeed,
               GLfloat fov, GLfloat aspect, GLfloat zNear, GLfloat zFar)
    :pos(startPos), worldUp(startWorldUp), yaw(startYaw), pitch(startPitch), moveSpeed(startMoveSpeed), turnSpeed(startTurnSpeed),
    fov(fov), aspect(aspect), zNear(zNear), zFar(zFar)
{
    update();
}

void Camera::update() {
    front.x = cos(pitch) * cos(yaw);
    front.y = sin(pitch);
    front.z = cos(pitch) * sin(yaw);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::keyControl(GLWidget *glwidget, GLfloat deltaTime){
    if (glwidget->isWPressed()) pos += front * moveSpeed * deltaTime;
    if (glwidget->isAPressed()) pos -= right * moveSpeed * deltaTime;
    if (glwidget->isSPressed()) pos -= front * moveSpeed * deltaTime;
    if (glwidget->isDPressed()) pos += right * moveSpeed * deltaTime;
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    yaw += xChange * turnSpeed;
    pitch += yChange * turnSpeed;

    pitch = glm::degrees(pitch);
    if (pitch >= 89) pitch = 89;
    else if (pitch <= -89) pitch = -89;
    pitch = glm::radians(pitch);

    update();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::calculateProjectionMatrix() {
    return glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::setWorldUp(glm::vec3 worldUp) {
    this->worldUp = worldUp;
    update();
}

void Camera::setYaw(GLfloat yaw) {
    this->yaw = yaw;
    update();
}

void Camera::setPitch(GLfloat pitch) {
    this->pitch = pitch;
    update();
}
