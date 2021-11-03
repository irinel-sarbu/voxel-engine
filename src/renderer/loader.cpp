#include "loader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<unsigned int> indices) {
  unsigned int vaoID = createVAO();
  bindIBO(indices);
  storeDataInAttributeList(0, positions);
  unbindVAO();

  return RawModel(vaoID, indices.size());
}

void Loader::cleanUp() {
  for (auto vao : vaos) {
    glDeleteVertexArrays(1, &vao);
  }

  for (auto vbo : vbos) {
    glDeleteBuffers(1, &vbo);
  }
}

unsigned int Loader::createVAO() {
  unsigned int vaoID;
  glGenVertexArrays(1, &vaoID);
  vaos.push_back(vaoID);
  glBindVertexArray(vaoID);
  return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, std::vector<float> data) {
  unsigned int vboID;
  glGenBuffers(1, &vboID);
  vbos.push_back(vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(attributeNumber);
  glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
  glBindVertexArray(0);
}

void Loader::bindIBO(std::vector<unsigned int> indices) {
  unsigned int vboID;
  glGenBuffers(1, &vboID);
  vbos.push_back(vboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}
