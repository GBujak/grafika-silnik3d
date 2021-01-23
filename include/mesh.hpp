#pragma once

#include <GL/glew.h>

class Mesh {
    unsigned m_VBO;
    unsigned m_VAO;
    size_t m_float_count;
    
    public:
    Mesh(float* vertices, size_t float_count) {
        m_float_count = float_count;

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, float_count * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
        glEnableVertexAttribArray(0);
    }

    void use() {
        glBindVertexArray(m_VAO);
    }

    void draw() {
        glDrawArrays(GL_TRIANGLES, 0, m_float_count);
    }
};
