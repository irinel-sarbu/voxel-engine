#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "vec3.hpp"
#include <cstdio>

#define PI 3.14159265358979323846
#define DegToRad(x) x *PI / 180.0

struct Quaternion {
  float w, x, y, z;

  Quaternion();
  Quaternion(const Quaternion &other);
  Quaternion(float w, float x, float y, float z);
  Quaternion(float realPart, Vec3 imaginaryPart);
  Quaternion(const Vec3 &v);
  Quaternion(float n);

  inline float lenSqr();
  inline float len();

  float real() {
    return w;
  }

  Vec3 imaginary() {
    return Vec3(x, y, z);
  }

  void show() {
    std::printf("%.3f, %.3fi, %.3fj, %.3fk\n", w, x, y, z);
  }

  Quaternion conjugate();

  Quaternion inverse();

  static Quaternion angle_axis(float angle, Vec3 axis);

  Quaternion &operator=(const Quaternion &q);
  Quaternion &operator+=(const Quaternion &q);
  Quaternion &operator-=(const Quaternion &q);
  Quaternion &operator*=(float n);
  Quaternion &operator/=(float n);

  /* Hamilton product */
  Quaternion &operator*=(Quaternion &q);
};

inline Quaternion operator+(const Quaternion &q1, const Quaternion &q2) {
  return Quaternion(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
}

inline Quaternion operator-(const Quaternion &q1, const Quaternion &q2) {
  return Quaternion(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
}

inline Quaternion operator*(const Quaternion &q, float n) {
  return Quaternion(q.w * n, q.x * n, q.y * n, q.z * n);
}

inline Quaternion operator*(float n, const Quaternion &q) {
  return Quaternion(q.w * n, q.x * n, q.y * n, q.z * n);
}

inline Quaternion operator/(const Quaternion &q, float n) {
  return Quaternion(q.w / n, q.x / n, q.y / n, q.z / n);
}

/* Hamilton product */
inline Quaternion operator*(Quaternion q1, Quaternion q2) {
  Vec3 a = q1.imaginary();
  Vec3 b = q2.imaginary();

  float sa = q1.real();
  float sb = q2.real();

  float realPart = sa * sb - dot(a, b);
  Vec3 imaginaryPart = ((sa * b) + (sb * a)) + cross(a, b);

  return Quaternion{realPart, imaginaryPart};
}

#endif // __QUATERNION_H__