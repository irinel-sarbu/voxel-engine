#include <GL/glew.h>
#include <GLFW/glfw3.h>

#if defined(__APPLE__)
#include <Opengl/gl.h>
#define GL_SILENCE_DEPRECATION
#else
#include <GL/gl.h>
#endif

#include "graphics/shader.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "renderer/loader.hpp"
#include "renderer/renderer.hpp"

using namespace std;

int main(int argc, const char *argv[]) {
  GLFWwindow *window;

  printf("Initializing...\n");

  /* Initialize the library */
  if (!glfwInit()) {
    printf("Unable to init GLFW!\n");
    return -1;
  }

#ifdef __APPLE__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Test window", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    printf("Unable to create window!\n");
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    printf("Unable to init GLEW!\n");
  }

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
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    renderer.prepare();

    renderer.render(model);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Closing window...\n");

  return 0;
}