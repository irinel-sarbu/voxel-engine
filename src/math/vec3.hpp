#ifndef __VEC3_H__
#define __VEC3_H__

#include <cstdio>

static inline float sqr(float n) {
  return n * n;
}

struct Vec3 {
  float x, y, z;
  Vec3();
  Vec3(const Vec3 &other);
  Vec3(float x, float y, float z);
  Vec3(float n);

  inline float lenSqr();
  inline float len();

  float normalize();
  Vec3 normalized();

  void rotate(float angle, Vec3 axis);

  void show() {
    std::printf("%.3f x, %.3f y, %.3f z\n", x, y, z);
  }

  Vec3 &operator=(const Vec3 &v);
  Vec3 &operator+=(const Vec3 &v);
  Vec3 &operator-=(const Vec3 &v);
  Vec3 &operator*=(float n);
  Vec3 &operator/=(float n);
  Vec3 operator-() const;
};

float dot(Vec3 v1, Vec3 v2);
Vec3 cross(Vec3 v1, Vec3 v2);

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
  return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator*(const Vec3 &v, float n) {
  return Vec3(v.x * n, v.y * n, v.z * n);
}

inline Vec3 operator*(float n, const Vec3 &v) {
  return Vec3(v.x * n, v.y * n, v.z * n);
}

inline Vec3 operator/(const Vec3 &v, float n) {
  return Vec3(v.x / n, v.y / n, v.z / n);
}

#endif // __VEC3_H__