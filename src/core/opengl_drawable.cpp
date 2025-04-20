#include <glad/glad.h>

#include "opengl_drawable.hpp"
#include "plane_framework.hpp"
#include "spdlog/spdlog.h"

void Drawable::Init(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (vertexes.size()), vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (vertexes.size()), vertexes.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Drawable::Draw(){
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexes.size() / 6);
    glBindVertexArray(0);
}

void Drawable::Free(){
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO);
}
