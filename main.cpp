#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if defined(__APPLE__)
#include <Opengl/gl.h>
#define GL_SILENCE_DEPRECATION
#else
#include <GL/gl.h>
#endif

#include "src/graphics/shader.hpp"

#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "src/renderer/displaymanager.hpp"
#include "src/renderer/loader.hpp"
#include "src/renderer/renderer.hpp"

#include "src/math/mat4.hpp"
#include "src/math/quaternion.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
  DisplayManager &window = DisplayManager::instance();

  std::vector<float> vertices{
      -100.0f, 100.0f, 0.0f,
      -100.0f, -100.0f, 0.0f,
      100.0f, -100.0f, 0.0f,
      100.0f, 100.0f, 0.0f};

  std::vector<unsigned int> indices{
      0, 1, 3,
      3, 1, 2};

  Loader loader;
  Renderer renderer;

  RawModel model = loader.loadToVAO(vertices, indices);

  Mat4 Projection = Mat4::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
  Mat4 View = Mat4::translate({-200.0f, 0.0f, 0.0f});
  Mat4 Model = Mat4::translate({200.0f, 200.0f, 0.0f}) * Mat4::rotate(Quaternion::angle_axis(45.0f, {0.0f, 0.0f, 1.0f}));
  Mat4 MVP = Projection * View * Model;

  Shader shader("res/shaders/main.vert", "res/shaders/main.frag");
  shader.use();
  shader.setUniformMat4("MVP", MVP);

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