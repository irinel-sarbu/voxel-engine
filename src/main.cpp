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

  std::vector<float> positions{-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};

  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);

  printf("Info:\n");
  printf("\tOpenGL version: %s\n", glGetString(GL_VERSION));
  printf("\tGPU vendor: %s\n", glGetString(GL_VENDOR));
  printf("\tRenderer: %s\n", glGetString(GL_RENDERER));

  Shader shader("res/shaders/main.vert", "res/shaders/main.frag");
  shader.use();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, positions.size() / 2);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  printf("Closing window...\n");

  return 0;
}