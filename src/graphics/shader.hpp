#ifndef __SHADER_H__
#define __SHADER_H__

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

#endif // __SHADER_H__