#include "displaymanager.hpp"

#include <iostream>

std::mutex DisplayManager::mutex;

DisplayManager &DisplayManager::instance() {
  std::lock_guard<std::mutex> lock(mutex);
  static DisplayManager instance;
  return instance;
}

bool DisplayManager::isCloseRequested() {
  return glfwWindowShouldClose(window);
}

void DisplayManager::update() {
  /* Swap front and back buffers */
  glfwSwapBuffers(window);

  /* Poll for and process events */
  glfwPollEvents();
}

void DisplayManager::close() {
  glfwTerminate();
  printf("Closing window...\n");
}

DisplayManager::DisplayManager() {
  /* Initialize the library */
  if (!glfwInit()) {
    std::printf("Unable to init GLFW!\n");
    exit(-1);
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
    exit(-1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    printf("Unable to init GLEW!\n");
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
