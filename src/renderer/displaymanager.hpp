#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <mutex>

class DisplayManager {
private:
  DisplayManager();
  DisplayManager(const DisplayManager &) = delete;
  DisplayManager &operator=(const DisplayManager &) = delete;

  GLFWwindow *window;

  static std::mutex mutex;

public:
  static DisplayManager &instance();

  bool isCloseRequested();
  void update();
  void close();
};
#endif // __DISPLAYMANAGER_H__