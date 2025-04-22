#include <glad/glad.h>

#include "opengl_drawable.hpp"
#include "plane_framework.hpp"
#include "spdlog/spdlog.h"

unsigned int Drawable::lengthOfSingleVertex() {
  unsigned int length = 0;
  for (int i = 0; i < attributesLength.size(); i++) {
    length += attributesLength[i];
  }
  return length;
}

bool Drawable::checkDataIsValid() {
  if (vertexes.size() == 0) {
    spdlog::error("Vertexes is empty");
    return false;
  }
  if (indices.size() == 0) {
    spdlog::error("Indices is empty");
    return false;
  }
  if (attributesLength.size() == 0) {
    spdlog::error("AttributesLength is empty");
    return false;
  }
  if (indices.size() % 3 != 0) {
    spdlog::error("Indices size is not multiple of 3");
    return false;
  }
  unsigned int lengthUnit = lengthOfSingleVertex();
  if (vertexes.size() % lengthUnit != 0) {
    spdlog::error("Vertexes size is not multiple of attributesLength");
    return false;
  }

  return true;
}

void Drawable::InitVAO() {
  if (!checkDataIsValid()) {
    spdlog::error("Data is not valid");
    return;
  }
  unsigned int VBO;
  unsigned int EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (vertexes.size()),
               vertexes.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (indices.size()),
               indices.data(), GL_STATIC_DRAW);

  unsigned int lengthUnit = lengthOfSingleVertex();
  unsigned int offset = 0;
  for (int i = 0; i < attributesLength.size(); i++) {
    glVertexAttribPointer(i, attributesLength[i], GL_FLOAT, GL_FALSE,
                          sizeof(float) * lengthUnit,
                          (void *)(offset * sizeof(float)));
    glEnableVertexAttribArray(i);
    offset += attributesLength[i];
  }
  // must unbind VAO first
  glBindVertexArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  init = true;
}

void Drawable::Draw() {
  if (!init) {
    spdlog::error("VAO is not initialized");
    return;
  }
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Drawable::Free() {
  if (init) {
    glDeleteVertexArrays(1, &VAO);
  }
}
