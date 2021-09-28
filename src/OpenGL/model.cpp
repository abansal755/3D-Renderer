#include "model.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "lib/glm/gtc/type_ptr.hpp"

void Model::renderModel(Camera *camera){
    shader->useShader();
    GLuint uniformModel=shader->getModelLocation();
    GLuint uniformProjection=shader->getProjectionLocation();
    GLuint uniformView=shader->getViewLocation();
    GLuint uniformModelColor=shader->getModelColorLocation();
    gl()->glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    gl()->glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(camera->calculateProjectionMatrix()));
    gl()->glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
    gl()->glUniform4f(uniformModelColor,color.redF(),color.greenF(),color.blueF(),color.alphaF());
    mesh->renderMesh();
    Shader::unUseShader();
}
