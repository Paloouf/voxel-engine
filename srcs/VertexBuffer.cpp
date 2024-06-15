#include "../include/VertexBuffer.hpp"

VertexBuffer::VertexBuffer(const float* data, unsigned int size) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &vbo);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}