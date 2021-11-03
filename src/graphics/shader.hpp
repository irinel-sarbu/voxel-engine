#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
private:
  unsigned int id;

public:
  Shader(const std::string &fragShaderPath, const std::string &vertShaderPath);
  void use();

private:
  std::string parseFile(const std::string &filepath);
};

#endif