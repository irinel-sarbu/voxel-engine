#include "shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>

std::string Shader::parseFile(const std::string &filepath) {
  std::ifstream file;
  std::stringstream buffer;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    file.open(filepath);
    buffer << file.rdbuf();
  } catch (std::ifstream::failure e) {
    std::printf("ERROR: %s\n", e.what());
    exit(-1);
  }

  return buffer.str();
}

Shader::Shader(const std::string &vertShaderPath, const std::string &fragShaderPath) {

  std::string vertShaderCode = parseFile(vertShaderPath);
  const char *vShaderCode = vertShaderCode.c_str();

  std::string fragShaderCode = parseFile(fragShaderPath);
  const char *fShaderCode = fragShaderCode.c_str();

  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // vertex Shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::printf("ERROR Shader vertex compilation failed\n%s\n", infoLog);
    exit(-1);
  };

  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::printf("ERROR Shader fragment compilation failed\n%s\n", infoLog);
    exit(-1);
  };

  // shader Program
  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);

  // print linking errors if any
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    std::printf("ERROR Shader program linking failed\n%s\n", infoLog);
    exit(-1);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use() {
  glUseProgram(id);
}

void Shader::setUniformMat4(const std::string &name, const Mat4 &mat) {
  unsigned int mID = glGetUniformLocation(id, name.c_str());
  glUniformMatrix4fv(mID, 1, GL_TRUE, &mat(0, 0));
}
