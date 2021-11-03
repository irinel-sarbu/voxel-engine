#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if defined(__APPLE__)
#include <Opengl/gl.h>
#define GL_SILENCE_DEPRECATION
#else
#include <GL/gl.h>
#endif

#include "src/graphics/shader.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "src/renderer/displaymanager.hpp"
#include "src/renderer/loader.hpp"
#include "src/renderer/renderer.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
  DisplayManager &window = DisplayManager::instance();

  std::vector<float> vertices{
      -0.5f, 0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,

      0.5f, 0.5f, 0.0f};

  std::vector<unsigned int> indices{
      0, 1, 3,
      3, 1, 2};

  Loader loader;
  Renderer renderer;

  RawModel model = loader.loadToVAO(vertices, indices);

  Shader shader("res/shaders/main.vert", "res/shaders/main.frag");
  shader.use();

  /* Loop until the user closes the window */
  while (!window.isCloseRequested()) {
    /* Render prepare */
    renderer.prepare();

    /* Render here */
    renderer.render(model);

    /* Update window */
    window.update();
  }

  window.close();

  return 0;
}