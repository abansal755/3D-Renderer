#include "model.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include <glm/gtc/type_ptr.hpp>

Model::Model(Mesh*mesh,glm::mat4 model,Shader*shader)
    :mesh(mesh),model(model),shader(shader)
{
    initializeOpenGLFunctions();
}

void Model::renderModel(Camera *camera){
    shader->useShader();
    GLuint uniformModel=shader->getModelLocation();
    GLuint uniformProjection=shader->getProjectionLocation();
    GLuint uniformView=shader->getViewLocation();
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(camera->calculateProjectionMatrix()));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->calculateViewMatrix()));
    populateUniforms();
    mesh->renderMesh();
    shader->unUseShader();
}
