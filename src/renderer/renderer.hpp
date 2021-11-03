#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "rawModel.hpp"

class Renderer {
public:
  void prepare();
  void render(RawModel model);

private:
};

#endif // __RENDERER_H__