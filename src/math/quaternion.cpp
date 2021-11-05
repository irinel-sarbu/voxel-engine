#include "quaternion.hpp"

#include <cmath>

Quaternion::Quaternion() : w(0.0f), x(0.0f), y(0.0f), z(0.0f) {}

Quaternion::Quaternion(const Quaternion &other) : w(other.w), x(other.x), y(other.y), z(other.z) {}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

Quaternion::Quaternion(float realPart, Vec3 imaginaryPart) : w(realPart), x(imaginaryPart.x), y(imaginaryPart.y), z(imaginaryPart.z) {}

Quaternion::Quaternion(const Vec3 &v) : w(0.0f), x(v.x), y(v.y), z(v.z) {}

Quaternion::Quaternion(float n) : w(n), x(0.0f), y(0.0f), z(0.0f) {}

inline float Quaternion::lenSqr() {
  return sqr(w) + sqr(x) + sqr(y) + sqr(z);
}

inline float Quaternion::len() {
  return std::sqrt(lenSqr());
}

Quaternion Quaternion::conjugate() {
  return Quaternion{w, -x, -y, -z};
}

Quaternion Quaternion::inverse() {
  float l = len();
  if (l == 0.0f) {
    std::printf("ERROR: Quaternion is a zero length quaternion!");
    exit(-1);
  }

  return Quaternion(conjugate() / l);
}

Quaternion Quaternion::angle_axis(float angle, Vec3 axis) {
  float c = std::cos(DegToRad(angle / 2.0f));
  float s = std::sin(DegToRad(angle / 2.0f));
  Vec3 axisNormalized = axis.normalized();

  return Quaternion{c, axisNormalized * s};
}

Quaternion &Quaternion::operator=(const Quaternion &q) {
  w = q.w;
  x = q.x;
  y = q.y;
  z = q.z;
  return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &q) {
  w += q.w;
  x += q.x;
  y += q.y;
  z += q.z;
  return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q) {
  w -= q.w;
  x -= q.x;
  y -= q.y;
  z -= q.z;
  return *this;
}

Quaternion &Quaternion::operator*=(float n) {
  w *= n;
  x *= n;
  y *= n;
  z *= n;
  return *this;
}

Quaternion &Quaternion::operator/=(float n) {
  w /= n;
  x /= n;
  y /= n;
  z /= n;
  return *this;
}

/* Hamilton product */
Quaternion &Quaternion::operator*=(Quaternion &q) {
  Vec3 a = (*this).imaginary();
  Vec3 b = q.imaginary();

  float sa = (*this).real();
  float sb = q.real();

  float realPart = sa * sb - dot(a, b);
  Vec3 imaginaryPart = ((sa * b) + (sb * a)) + cross(a, b);

  Quaternion res{realPart, imaginaryPart};
  *this = res;
  return *this;
}
