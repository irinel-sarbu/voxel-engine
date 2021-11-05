#include "renderer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Renderer::prepare() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(RawModel model) {
  glBindVertexArray(model.getVaoID());
  glEnableVertexAttribArray(0);
  glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
}
