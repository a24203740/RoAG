#include "cube.hpp"

Cube::Cube() : Drawable() {
  this->position = glm::vec3(0, 0, 0);
  this->size = glm::vec3(1, 1, 1);
  this->color = glm::vec3(0xFF / 255.0, 0xFF / 255.0, 0xFF / 255.0);
  generateVertices();
}

Cube::Cube(glm::vec3 position, glm::vec3 size, glm::vec3 color) : Drawable() {
  this->position = position;
  this->size = size;
  this->color = color;
  generateVertices();
}

void Cube::generateVertices() {
  float x = size.x, y = size.y, z = size.z;
  glm::vec3 verticesRaw[] = {// 0: Left-Bottom-Near
                          glm::vec3(0.0f, 0.0f, 0.0f),
                          // 1: Right-Bottom-Near
                          glm::vec3(x, 0.0f, 0.0f),
                          // 2: Right-Top-Near
                          glm::vec3(x, y, 0.0f),
                          // 3: Left-Top-Near
                          glm::vec3(0.0f, y, 0.0f),
                          // 4: Left-Bottom-Far
                          glm::vec3(0.0f, 0.0f, z),
                          // 5: Right-Bottom-Far
                          glm::vec3(x, 0.0f, z),
                          // 6: Right-Top-Far
                          glm::vec3(x, y, z),
                          // 7: Left-Top-Far
                          glm::vec3(0.0f, y, z)};

  std::vector<float> vertexBuffer;
  for (int i = 0; i < 8; i++) {
    vertexBuffer.push_back(verticesRaw[i].x + position.x);
    vertexBuffer.push_back(verticesRaw[i].y + position.y);
    vertexBuffer.push_back(verticesRaw[i].z + position.z);
    vertexBuffer.push_back(color.x);
    vertexBuffer.push_back(color.y);
    vertexBuffer.push_back(color.z);
  }

  std::vector<unsigned int> indicesBuffer{// Front face (z = 0)
                            0, 1, 2, 2, 3, 0,

                            // Back face (z = z)
                            5, 4, 7, 7, 6, 5,

                            // Left face (x = 0)
                            4, 0, 3, 3, 7, 4,

                            // Right face (x = x)
                            1, 5, 6, 6, 2, 1,

                            // Top face (y = y)
                            3, 2, 6, 6, 7, 3,

                            // Bottom face (y = 0)
                            4, 5, 1, 1, 0, 4};

  this->SetVertexes(vertexBuffer);
  this->SetIndices(indicesBuffer);
  this->SetAttributesLength({3, 3});
}
