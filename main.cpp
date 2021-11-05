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

  // Mat4 Projection = Mat4::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
  // Mat4 View = Mat4::translate({-200.0f, 0.0f, 0.0f});

  // Mat4 ModelTranslation = Mat4::translate({500.0f, 200.0f, 0.0f});
  // Mat4 ModelRotation = Mat4::rotate({0.0f, {0.0f, 0.0f, 1.0f}});
  // Mat4 ModelScale = Mat4::scale({1.0f, 1.0f, 1.0f});

  // Mat4 Model = ModelTranslation * ModelRotation * ModelScale;
  // Mat4 MVP = Projection * View * Model;

  Shader shader("res/shaders/main.vert", "res/shaders/main.frag");
  shader.use();
  // shader.setUniformMat4("MVP", MVP);

  //float angle = 0.0f;

  float lastTime = glfwGetTime();
  int nbFrames = 0;
  /* Loop until the user closes the window */
  while (!window.isCloseRequested()) {
    /* Render prepare */
    renderer.prepare();

    /* Render here */
    // ModelRotation = Mat4::rotate(Quaternion::angle_axis(angle, {0.0f, 0.0f, 1.0f}));
    // Model = ModelTranslation * ModelRotation * ModelScale;
    // MVP = Projection * View * Model;
    // shader.setUniformMat4("MVP", MVP);

    renderer.render(model);

    /* Update window */
    window.update();
    //angle += 0.2f;

    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
      // printf and reset timer
      printf("FPS: %d - %f ms/frame\n", nbFrames / 60, 1000.0 / double(nbFrames));
      nbFrames = 0;
      lastTime += 1.0;
    }
  }

  window.close();

  return 0;
}