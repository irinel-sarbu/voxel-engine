#ifndef __MAT4_H__
#define __MAT4_H__

#include "quaternion.hpp"

class Mat4 {
private:
  float data[4][4] = {0};

public:
  Mat4();
  Mat4(const Mat4 &m);
  Mat4(float n);
  Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);

  static Mat4 rotate(Quaternion rotation);
  static Mat4 scale(Vec3 v);
  static Mat4 translate(Vec3 v);
  static Mat4 lookAt(const Vec3 &from, const Vec3 &to, const Vec3 &tmp = Vec3{0, 1, 0});

  static Mat4 ortho(float left, float right, float bottom, float top, float near, float far);

  void show() {
    std::printf("%9.3f %9.3f %9.3f %9.3f\n", data[0][0], data[0][1], data[0][2], data[0][3]);
    std::printf("%9.3f %9.3f %9.3f %9.3f\n", data[1][0], data[1][1], data[1][2], data[1][3]);
    std::printf("%9.3f %9.3f %9.3f %9.3f\n", data[2][0], data[2][1], data[2][2], data[2][3]);
    std::printf("%9.3f %9.3f %9.3f %9.3f\n", data[3][0], data[3][1], data[3][2], data[3][3]);
  }

  Mat4 &operator=(const Mat4 &m);
  Mat4 &operator+=(const Mat4 &m);
  Mat4 &operator-=(const Mat4 &m);
  Mat4 &operator*=(const Mat4 &m);
  Mat4 &operator*=(float n);
  Mat4 &operator/=(float n);

  float &operator()(int y, int x);
  const float &operator()(int y, int x) const;
};

inline Mat4 operator+(const Mat4 &m1, const Mat4 &m2) {
  Mat4 res;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      res(y, x) = m1(y, x) + m2(y, x);

  return res;
}

inline Mat4 operator-(const Mat4 &m1, const Mat4 &m2) {
  Mat4 res;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      res(y, x) = m1(y, x) - m2(y, x);

  return res;
}

inline Mat4 operator*(const Mat4 &m, float n) {
  Mat4 res;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      res(y, x) *= n;

  return res;
}

inline Mat4 operator*(float n, const Mat4 &m) {
  Mat4 res;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      res(y, x) *= n;

  return res;
}

inline Mat4 operator*(const Mat4 &m1, const Mat4 &m2) {
  Mat4 res;

  res(0, 0) = m1(0, 0) * m2(0, 0) + m1(0, 1) * m2(1, 0) + m1(0, 2) * m2(2, 0) + m1(0, 3) * m2(3, 0);
  res(0, 1) = m1(0, 0) * m2(0, 1) + m1(0, 1) * m2(1, 1) + m1(0, 2) * m2(2, 1) + m1(0, 3) * m2(3, 1);
  res(0, 2) = m1(0, 0) * m2(0, 2) + m1(0, 1) * m2(1, 2) + m1(0, 2) * m2(2, 2) + m1(0, 3) * m2(3, 2);
  res(0, 3) = m1(0, 0) * m2(0, 3) + m1(0, 1) * m2(1, 3) + m1(0, 2) * m2(2, 3) + m1(0, 3) * m2(3, 3);

  res(1, 0) = m1(1, 0) * m2(0, 0) + m1(1, 1) * m2(1, 0) + m1(1, 2) * m2(2, 0) + m1(1, 3) * m2(3, 0);
  res(1, 1) = m1(1, 0) * m2(0, 1) + m1(1, 1) * m2(1, 1) + m1(1, 2) * m2(2, 1) + m1(1, 3) * m2(3, 1);
  res(1, 2) = m1(1, 0) * m2(0, 2) + m1(1, 1) * m2(1, 2) + m1(1, 2) * m2(2, 2) + m1(1, 3) * m2(3, 3);
  res(1, 3) = m1(1, 0) * m2(0, 3) + m1(1, 1) * m2(1, 3) + m1(1, 2) * m2(2, 3) + m1(1, 3) * m2(3, 3);

  res(2, 0) = m1(2, 0) * m2(0, 0) + m1(2, 1) * m2(1, 0) + m1(2, 2) * m2(2, 0) + m1(2, 3) * m2(3, 0);
  res(2, 1) = m1(2, 0) * m2(0, 1) + m1(2, 1) * m2(1, 1) + m1(2, 2) * m2(2, 1) + m1(2, 3) * m2(3, 1);
  res(2, 2) = m1(2, 0) * m2(0, 2) + m1(2, 1) * m2(1, 2) + m1(2, 2) * m2(2, 2) + m1(2, 3) * m2(3, 3);
  res(2, 3) = m1(2, 0) * m2(0, 3) + m1(2, 1) * m2(1, 3) + m1(2, 2) * m2(2, 3) + m1(2, 3) * m2(3, 3);

  res(3, 0) = m1(3, 0) * m2(0, 0) + m1(3, 1) * m2(1, 0) + m1(3, 2) * m2(2, 0) + m1(3, 3) * m2(3, 0);
  res(3, 1) = m1(3, 0) * m2(0, 1) + m1(3, 1) * m2(1, 1) + m1(3, 2) * m2(2, 1) + m1(3, 3) * m2(3, 1);
  res(3, 2) = m1(3, 0) * m2(0, 2) + m1(3, 1) * m2(1, 2) + m1(3, 2) * m2(2, 2) + m1(3, 3) * m2(3, 3);
  res(3, 3) = m1(3, 0) * m2(0, 3) + m1(3, 1) * m2(1, 3) + m1(3, 2) * m2(2, 3) + m1(3, 3) * m2(3, 3);

  return res;
}

inline Mat4 operator/(const Mat4 &m, float n) {
  Mat4 res;
  for (int y = 0; y < 4; y++)
    for (int x = 0; x < 4; x++)
      res(y, x) /= n;

  return res;
}

#endif // __MAT4_H__