#ifndef __LOADER_H__
#define __LOADER_H__

#include <vector>

#include "rawModel.hpp"

class Loader {
private:
  std::vector<unsigned> vaos;
  std::vector<unsigned> vbos;

public:
  RawModel loadToVAO(std::vector<float> positions, std::vector<unsigned int> indices);
  void cleanUp();

private:
  unsigned int createVAO();
  void storeDataInAttributeList(int attributeNumber, std::vector<float> data);
  void unbindVAO();
  void bindIBO(std::vector<unsigned int> indices);
};

#endif // __LOADER_H__