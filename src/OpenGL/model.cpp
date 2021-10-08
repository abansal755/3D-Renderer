#include "model.h"
#include "lib/glm/gtc/type_ptr.hpp"

Model::Model(Mesh *mesh, Material *mat, glm::mat4 modelMatrix)
    :mesh(mesh),mat(mat),modelMatrix(modelMatrix)
{
    initializeOpenGLFunctions();
}

void Model::renderModel(){
    //bind shader
    LightShader* shader=mat->getShader();
    shader->useShader();

    //set uniform values
    GLuint modelLocation=shader->getModelLocation();
    glUniformMatrix4fv(modelLocation,1,GL_FALSE,glm::value_ptr(modelMatrix));
        //set camera values
        //set light values
        //set texture and color

    //render mesh
    mesh->renderMesh();

    //unbind shader
    shader->unUseShader();
}
