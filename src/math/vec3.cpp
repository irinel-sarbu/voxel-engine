#include "vec3.hpp"
#include "quaternion.hpp"
#include <cmath>

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::Vec3(float n) : x(n), y(n), z(n) {}

inline float Vec3::lenSqr() {
  return sqr(x) + sqr(y) + sqr(z);
}

inline float Vec3::len() {
  return std::sqrt(lenSqr());
}

float Vec3::normalize() {
  float l = len();
  *this /= l;
  return l;
}

Vec3 Vec3::normalized() {
  Vec3 v(*this);
  v.normalize();
  return v;
}

void Vec3::rotate(float angle, Vec3 axis) {
  float c = std::cos(DegToRad(angle / 2.0f));
  float s = std::sin(DegToRad(angle / 2.0f));
  Quaternion q{c, axis.normalized() * s};
  Quaternion p{(*this)};

  Quaternion result = q * p * q.inverse();
  *this = result.imaginary();
}

Vec3 &Vec3::operator=(const Vec3 &v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

Vec3 &Vec3::operator+=(const Vec3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

Vec3 &Vec3::operator*=(float n) {
  x *= n;
  y *= n;
  z *= n;
  return *this;
}

Vec3 &Vec3::operator/=(float n) {
  x /= n;
  y /= n;
  z /= n;
  return *this;
}

Vec3 Vec3::operator-() const {
  return Vec3(-x, -y, -z);
}

float dot(Vec3 v1, Vec3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(Vec3 v1, Vec3 v2) {
  return Vec3(
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x);
}