#pragma once
#include <cmath>

template <typename T = double> class Vector2D {
public:
  T x;
  T y;

  Vector2D() : x(T(0)), y(T(0)) {}
  Vector2D(T xVal, T yVal) : x(xVal), y(yVal) {}

  Vector2D operator-() const { return Vector2D(-x, -y); }

  Vector2D operator+(const Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
  }

  Vector2D operator-(const Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
  }

  Vector2D operator*(T scalar) const {
    return Vector2D(x * scalar, y * scalar);
  }

  Vector2D operator/(T scalar) const {
    return Vector2D(x / scalar, y / scalar);
  }

  Vector2D &operator+=(const Vector2D &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vector2D &operator-=(const Vector2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vector2D &operator*=(T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vector2D &operator/=(T scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  T length() const { return std::sqrt((x * x) + (y * y)); }

  Vector2D normalized() const {
    T len = length();
    return len > T(0) ? Vector2D(x / len, y / len) : Vector2D();
  }

  T dot(const Vector2D &other) const { return (x * other.x) + (y * other.y); }
};

// Type alias for convenience - allows using Vector2D without template brackets
using Vector2Dd = Vector2D<double>;
using Vector2Df = Vector2D<float>;