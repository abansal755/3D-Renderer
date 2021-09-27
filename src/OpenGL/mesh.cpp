#include "mesh.h"

Mesh::Mesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices){
    createMesh(vertices, indices);
}

Mesh::~Mesh() {
    clearMesh();
}

void Mesh::createMesh(std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices) {
    clearMesh();
    numVertices = vertices.size();
    numIndices = indices.size();
    gl()->glGenVertexArrays(1, &VAO);
    gl()->glBindVertexArray(VAO);
        gl()->glGenBuffers(1, &VBO);
        gl()->glBindBuffer(GL_ARRAY_BUFFER, VBO);
            gl()->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numVertices, &vertices[0], GL_STATIC_DRAW);

            gl()->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
            gl()->glEnableVertexAttribArray(0);

            gl()->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
            gl()->glEnableVertexAttribArray(1);
        gl()->glBindBuffer(GL_ARRAY_BUFFER, 0);

        gl()->glGenBuffers(1, &IBO);
        gl()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            gl()->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numIndices, &indices[0], GL_STATIC_DRAW);
        gl()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl()->glBindVertexArray(0);
}

void Mesh::clearMesh() {
    if (IBO != 0) {
        gl()->glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if (VBO != 0) {
        gl()->glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (VAO != 0) {
        gl()->glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    numIndices = 0;
    numVertices = 0;
}

void Mesh::renderMesh() {
    gl()->glBindVertexArray(VAO);
        gl()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            gl()->glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
        gl()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl()->glBindVertexArray(0);
}
