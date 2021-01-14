#include "Mesh.h"

#include "../lib/opengl.h"

Mesh::Mesh() {
    init();
}

Mesh::~Mesh() {
    deInit();
}

Mesh::Mesh(Mesh &&other) {
    steal(other);
}
Mesh &Mesh::operator=(Mesh &&other) {
    deInit();
    steal(other);
    return *this;
}

void Mesh::steal(Mesh &other) {
    array = other.array;
    vertices = other.vertices;
    indices = other.indices;
    countIndices = other.countIndices;
    other.array = 0;
    other.vertices = 0;
    other.indices = 0;
    other.countIndices = 0;
}

void Mesh::init() {
    glGenVertexArrays(1, &array);
    glGenBuffers(1, &vertices);
    glGenBuffers(1, &indices);
    countIndices = 0;
}

void Mesh::deInit() {
    if (array != 0) {
        glDeleteVertexArrays(1, &array);
        glDeleteBuffers(1, &vertices);
        glDeleteBuffers(1, &indices);
    }
    countIndices = 0;
}

void Mesh::bind() const {
    glBindVertexArray(array);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
}

void Mesh::unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::setVertices(int count, const float *data) {
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::setIndices(int count, const unsigned int *data) {
    countIndices = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::setParam(unsigned int index, int size, int stride, int offset) {
    bind();
    // Load the settings
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    // Apply the settings
    glEnableVertexAttribArray(index);
    unbind();
}

void Mesh::render() const {
    bind();
    // Draw the vertices in the array buffer according to the
    // indices in the element buffer
    glDrawElements(GL_TRIANGLES, countIndices, GL_UNSIGNED_INT, 0);
    unbind();
}
