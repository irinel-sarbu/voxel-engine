#ifndef __RAWMODEL_H__
#define __RAWMODEL_H__

class RawModel {
private:
  unsigned int vaoID;
  unsigned int vertexCount;

public:
  RawModel(unsigned int vaoID, unsigned int vertexCount) : vaoID(vaoID), vertexCount(vertexCount){};

  unsigned int getVaoID() {
    return vaoID;
  }

  unsigned int getVertexCount() {
    return vertexCount;
  }
};

#endif // __RAWMODEL_H__