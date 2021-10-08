#include "mesh.h"

Mesh::Mesh(){
    initializeOpenGLFunctions();
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices,
           GLenum usageMode, GLenum drawMode)
    :usageMode(usageMode), drawMode(drawMode)
{
    initializeOpenGLFunctions();
    createMesh(vertices, indices);
}

Mesh::~Mesh() {
    clearMesh();
}

void Mesh::createMesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    clearMesh();
    numVertices = vertices.size();
    numIndices = indices.size();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numVertices, &vertices[0], usageMode);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
            glEnableVertexAttribArray(1);

            glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(2*sizeof(glm::vec3)));
            glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numIndices, &indices[0], usageMode);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::clearMesh() {
    if (IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    numIndices = 0;
    numVertices = 0;
}

void Mesh::renderMesh() {
    glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glDrawElements(drawMode, numIndices, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::updateVertexBuffer(std::vector<Vertex> &vertices, GLintptr offset){
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,offset,sizeof(vertices[0])*vertices.size(),&vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Mesh::updateIndexBuffer(std::vector<unsigned int> &indices, GLintptr offset){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,offset,sizeof(indices[0])*numIndices,&indices[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
