#include <cmath>
#include <limits>
#include <functional>
#include <iostream>

#include "lineSegment.h"

const float eps = 0.001f;

float root(float (* f)(float), float (* f1)(float),
          float (* g)(float), float (* g1)(float),
          float a, float b, float eps1);

float integral(float (* f)(float), float a, float b, float eps2);

float f1  (float x) { return exp(x) + 2; }
float f11 (float x) { return exp(x); }

float f2  (float x) { return 8.f - 2.f * x; }
float f21 (float x) { return -2.f; }

float f3  (float x) { return -5.f / x; }
float f31 (float x) { return 5.f / (x * x); }

int main (void)
{
  float eps1 = 0.0001f;
  float eps2 = 0.0001f;
  float inttersection12 = root(f1, f11, f2, f21, 0.f, 5.f, eps1);
  float inttersection13 = root(f1, f11, f3, f31, -10.f, -0.00001f, eps1);
  float inttersection23 = root(f2, f21, f3, f31, -5.f, -0.2f, eps1);

  std::cout << inttersection12 << std::endl
            << inttersection13 << std::endl
            << inttersection23 << std::endl;

  float area = integral(f3, inttersection13, inttersection23, eps2) +
               integral(f2, inttersection23, inttersection12, eps2) -
               integral(f1, inttersection13, inttersection12, eps2);

  std::cout << area << std::endl;
  return 0;
}

float root(float (* f)(float), float (* f1)(float),
           float (* g)(float), float (* g1)(float),
           float a, float b, float eps1)
{
  LineSegment segment(a, b);
  bool moveFromLeftToRight = false;

  std::function<float(float)> F  = [&f, &f1, &g, &g1](float x) { return f(x)  - g(x);  };
  std::function<float(float)> F1 = [&f, &f1, &g, &g1](float x) { return f1(x) - g1(x); };

  float c = 0.f;
  bool isRising = F(segment.a) < 0;
  bool isAboveChord = F(segment.getCenter()) > ((F(segment.a) + F(segment.b)) / 2);
  bool fromLeft = false;
  if (isRising && !isAboveChord || !isRising && isAboveChord) {
    c = segment.b;
  } else {
    c = segment.a;
    fromLeft = true;
  }

  do {
    c = c - F(c) / F1(c);
  } while (F(c)*F(c + (fromLeft ? eps1 : (- eps1))) > 0);

  return c;
}

const float p = 1.f / 3.f;

float integral(float (* f)(float), float a, float b, float eps2)
{
  float result = 0.f;
  int partitionsCount = 2;
  for ( ; ; )
  {
    float newResult = 0.f;
    float h = fabs(b - a) / partitionsCount;

    for (int i = 1; i < partitionsCount + 1; ++i) {
      newResult += f(a + (i + 0.5f) * h);
    }
    newResult *= h;

    if (p * fabs(newResult - result) < eps2) {
      return newResult;
    } else {
      result = newResult;
      partitionsCount *= 2;
    }
  }
}
