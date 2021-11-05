#include "mat4.hpp"
#include "vec3.hpp"
#include <cmath>
Mat4::Mat4() {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      data[y][x] = 0;
}

Mat4::Mat4(const Mat4 &m) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      data[y][x] = m.data[y][x];
}

Mat4::Mat4(float n) {
  data[0][0] = n;
  data[0][1] = 0;
  data[0][2] = 0;
  data[0][3] = 0;

  data[1][0] = 0;
  data[1][1] = n;
  data[1][2] = 0;
  data[1][3] = 0;

  data[2][0] = 0;
  data[2][1] = 0;
  data[2][2] = n;
  data[2][3] = 0;

  data[3][0] = 0;
  data[3][1] = 0;
  data[3][2] = 0;
  data[3][3] = n;
}

Mat4::Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33) {
  Mat4 m;
  m.data[0][0] = m00;
  m.data[0][1] = m01;
  m.data[0][2] = m02;
  m.data[0][3] = m03;

  m.data[1][0] = m10;
  m.data[1][1] = m11;
  m.data[1][2] = m12;
  m.data[1][3] = m13;

  m.data[2][0] = m20;
  m.data[2][1] = m21;
  m.data[2][2] = m22;
  m.data[2][3] = m23;

  m.data[3][0] = m30;
  m.data[3][1] = m31;
  m.data[3][2] = m32;
  m.data[3][3] = m33;

  *this = m;
}

Mat4 Mat4::rotate(Quaternion rotation) {
  float w = rotation.w;
  float x = rotation.x;
  float y = rotation.y;
  float z = rotation.z;

  Mat4 m;
  m.data[0][0] = 1 - 2 * sqr(y) - 2 * sqr(z);
  m.data[0][1] = 2 * (x * y - w * z);
  m.data[0][2] = 2 * (x * z + w * y);
  m.data[0][3] = 0;

  m.data[1][0] = 2 * (x * y + w * z);
  m.data[1][1] = 1 - 2 * sqr(x) - 2 * sqr(z);
  m.data[1][2] = 2 * (y * z - w * x);
  m.data[1][3] = 0;

  m.data[2][0] = 2 * (x * z - w * y);
  m.data[2][1] = 2 * (y * z + w * x);
  m.data[2][2] = 1 - 2 * sqr(x) - 2 * sqr(y);
  m.data[2][3] = 0;

  m.data[3][0] = 0;
  m.data[3][1] = 0;
  m.data[3][2] = 0;
  m.data[3][3] = 1;

  return m;
}

Mat4 Mat4::scale(Vec3 v) {
  Mat4 m;

  m.data[0][0] = v.x;
  m.data[0][1] = 0;
  m.data[0][2] = 0;
  m.data[0][3] = 0;

  m.data[1][0] = 0;
  m.data[1][1] = v.y;
  m.data[1][2] = 0;
  m.data[1][3] = 0;

  m.data[2][0] = 0;
  m.data[2][1] = 0;
  m.data[2][2] = v.z;
  m.data[2][3] = 0;

  m.data[3][0] = 0;
  m.data[3][1] = 0;
  m.data[3][2] = 0;
  m.data[3][3] = 1.0f;

  return m;
}

Mat4 Mat4::translate(Vec3 v) {
  Mat4 m;
  m.data[0][0] = 1;
  m.data[0][3] = v.x;
  m.data[1][1] = 1;
  m.data[1][3] = v.y;
  m.data[2][2] = 1;
  m.data[2][3] = v.z;
  m.data[3][3] = 1;

  return m;
}

Mat4 Mat4::lookAt(const Vec3 &from, const Vec3 &to, const Vec3 &tmp) {
  Vec3 forward = (from - to).normalized();
  Vec3 right = cross(tmp, forward);
  Vec3 up = cross(forward, right);

  Mat4 camToWorld;

  camToWorld.data[0][0] = right.x;
  camToWorld.data[0][1] = right.y;
  camToWorld.data[0][2] = right.z;
  camToWorld.data[0][3] = 0;

  camToWorld.data[1][0] = up.x;
  camToWorld.data[1][1] = up.y;
  camToWorld.data[1][2] = up.z;
  camToWorld.data[1][3] = 0;

  camToWorld.data[2][0] = forward.x;
  camToWorld.data[2][1] = forward.y;
  camToWorld.data[2][2] = forward.z;
  camToWorld.data[2][3] = 0;

  camToWorld.data[3][0] = from.x;
  camToWorld.data[3][1] = from.y;
  camToWorld.data[3][2] = from.z;
  camToWorld.data[3][3] = 0;

  return camToWorld;
}

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float near, float far) {

  Mat4 m;
  m.data[0][0] = 2.0f / (right - left);
  m.data[0][3] = -(right + left) / (right - left);

  m.data[1][1] = 2.0f / (top - bottom);
  m.data[1][3] = -(top + bottom) / (top - bottom);

  m.data[2][2] = 2.0f / (far - near);
  m.data[2][3] = -(far + near) / (far - near);

  m.data[3][3] = 1;

  return m;
}

Mat4 &Mat4::operator=(const Mat4 &m) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      (*this).data[y][x] = m.data[y][x];

  return *this;
}

Mat4 &Mat4::operator+=(const Mat4 &m) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      (*this).data[y][x] += m.data[y][x];

  return *this;
}

Mat4 &Mat4::operator-=(const Mat4 &m) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      (*this).data[y][x] -= m.data[y][x];

  return *this;
}

Mat4 &Mat4::operator*=(const Mat4 &m) {
  Mat4 res;

  res(0, 0) = (*this)(0, 0) * m(0, 0) + (*this)(0, 1) * m(1, 0) + (*this)(0, 2) * m(2, 0) + (*this)(0, 3) * m(3, 0);
  res(0, 1) = (*this)(0, 0) * m(0, 1) + (*this)(0, 1) * m(1, 1) + (*this)(0, 2) * m(2, 1) + (*this)(0, 3) * m(3, 1);
  res(0, 2) = (*this)(0, 0) * m(0, 2) + (*this)(0, 1) * m(1, 2) + (*this)(0, 2) * m(2, 2) + (*this)(0, 3) * m(3, 2);
  res(0, 3) = (*this)(0, 0) * m(0, 3) + (*this)(0, 1) * m(1, 3) + (*this)(0, 2) * m(2, 3) + (*this)(0, 3) * m(3, 3);

  res(1, 0) = (*this)(1, 0) * m(0, 0) + (*this)(1, 1) * m(1, 0) + (*this)(1, 2) * m(2, 0) + (*this)(1, 3) * m(3, 0);
  res(1, 1) = (*this)(1, 0) * m(0, 1) + (*this)(1, 1) * m(1, 1) + (*this)(1, 2) * m(2, 1) + (*this)(1, 3) * m(3, 1);
  res(1, 2) = (*this)(1, 0) * m(0, 2) + (*this)(1, 1) * m(1, 2) + (*this)(1, 2) * m(2, 2) + (*this)(1, 3) * m(3, 3);
  res(1, 3) = (*this)(1, 0) * m(0, 3) + (*this)(1, 1) * m(1, 3) + (*this)(1, 2) * m(2, 3) + (*this)(1, 3) * m(3, 3);

  res(2, 0) = (*this)(2, 0) * m(0, 0) + (*this)(2, 1) * m(1, 0) + (*this)(2, 2) * m(2, 0) + (*this)(2, 3) * m(3, 0);
  res(2, 1) = (*this)(2, 0) * m(0, 1) + (*this)(2, 1) * m(1, 1) + (*this)(2, 2) * m(2, 1) + (*this)(2, 3) * m(3, 1);
  res(2, 2) = (*this)(2, 0) * m(0, 2) + (*this)(2, 1) * m(1, 2) + (*this)(2, 2) * m(2, 2) + (*this)(2, 3) * m(3, 3);
  res(2, 3) = (*this)(2, 0) * m(0, 3) + (*this)(2, 1) * m(1, 3) + (*this)(2, 2) * m(2, 3) + (*this)(2, 3) * m(3, 3);

  res(3, 0) = (*this)(3, 0) * m(0, 0) + (*this)(3, 1) * m(1, 0) + (*this)(3, 2) * m(2, 0) + (*this)(3, 3) * m(3, 0);
  res(3, 1) = (*this)(3, 0) * m(0, 1) + (*this)(3, 1) * m(1, 1) + (*this)(3, 2) * m(2, 1) + (*this)(3, 3) * m(3, 1);
  res(3, 2) = (*this)(3, 0) * m(0, 2) + (*this)(3, 1) * m(1, 2) + (*this)(3, 2) * m(2, 2) + (*this)(3, 3) * m(3, 3);
  res(3, 3) = (*this)(3, 0) * m(0, 3) + (*this)(3, 1) * m(1, 3) + (*this)(3, 2) * m(2, 3) + (*this)(3, 3) * m(3, 3);

  *this = res;
  return *this;
}

Mat4 &Mat4::operator*=(float n) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      (*this).data[y][x] *= n;

  return *this;
}

Mat4 &Mat4::operator/=(float n) {
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      (*this).data[y][x] *= n;

  return *this;
}

float &Mat4::operator()(int y, int x) {
  return data[y][x];
}

const float &Mat4::operator()(int y, int x) const {
  return data[y][x];
}