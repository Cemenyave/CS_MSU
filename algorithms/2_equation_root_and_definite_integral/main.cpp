#include <cmath>
#include <limits>
#include <functional>
#include <iostream>

#include "lineSegment.h"

const float eps = 0.001f;

bool root(float (* f)(float), float (* f1)(float),
          float (* g)(float), float (* g1)(float),
          float a, float b, float eps1, float &x);

float integral(float (* f)(float), float a, float b, float eps2);

float f1  (float x) { return exp(x) + 2; }
float f11 (float x) { return exp(x); }
float f12 (float x) { return exp(x); }

float f2  (float x) { return 8.f - 2.f * x; }
float f21 (float x) { return -2.f; }
float f22 (float x) { return 0.f; }

float f3  (float x) { return -5.f / x; }
float f31 (float x) { return 5.f / (x * x); }
float f32 (float x) { return -10.f / (x * x * x); }

float zero (float x) { return 0.f; }


///
/// Return true if f(x) has equal signs on each end of segment
///
bool testSign(std::function<float (float)> f, LineSegment segment)
{
  return (f(segment.a) * f(segment.b)) > 0;
}

///
/// Returns segment, which satisfy the conditions:
///   - function f(x) has different sign on ends of segment
///   - first Derivative f1(x) has equal sings on ends of segment
///   - second Derivative f1(x) has equal sings on ends of segment
/// This function recursively checks input segment using binary search
///
LineSegment getGoodSegment(std::function<float (float)> f,
                           std::function<float (float)> f1,
                           std::function<float (float)> f2)
{
  std::function<bool(LineSegment)> checkSegment = [&](LineSegment segment) {
    return !testSign(f, segment) && /*not same sign*/
      testSign(f1, segment) &&      /*ferst Derivative change sign*/
      testSign(f2, segment);        /*second Derivative change sign*/
  };

  std::function<LineSegment(LineSegment)> binarySearch = [&](LineSegment segment) {
    if (checkSegment(segment)) {
      return segment;
    } else {
      LineSegment high = segment.getHighHalf();
      if (!testSign(f, high)) {
        return binarySearch(high);
      } else {
        return binarySearch(segment.getLowHalf());
      }
    }
  };

  LineSegment segment(FLT_MIN, FLT_MAX);
  return binarySearch(segment);
}

int main (void)
{
  std::function<float(float)> F_1_2 = [](float x) { return f1(x) - f2(x); },
                              F_1_2_firstDer = [](float x) { return f11(x) - f21(x); },
                              F_1_2_secondDer = [](float x) { return f12(x) - f22(x); };

  LineSegment segment = getGoodSegment(F_1_2, F_1_2_firstDer, F_1_2_secondDer);
  std::cout << "a = " << segment.a << std::endl
            << "b = " << segment.b << std::endl;



  std::function<float(float)> F_3_2 = [](float x) { return f3(x) - f2(x); },
                              F_3_2_firstDer = [](float x) { return f31(x) - f21(x); },
                              F_3_2_secondDer = [](float x) { return f32(x) - f22(x); };

  segment = getGoodSegment(F_3_2, F_3_2_firstDer, F_3_2_secondDer);
  std::cout << "a = " << segment.a << std::endl
            << "b = " << segment.b << std::endl;




  std::function<float(float)> F_1_3 = [](float x) { return f1(x) - f3(x); },
                              F_1_3_firstDer = [](float x) { return f11(x) - f31(x); },
                              F_1_3_secondDer = [](float x) { return f12(x) - f32(x); };

  segment = getGoodSegment(F_1_3, F_1_3_firstDer, F_1_3_secondDer);
  std::cout << "a = " << segment.a << std::endl
            << "b = " << segment.b << std::endl;

//   root(f1, f11, f12, f2, f21, f22, a, b, 0.001f);
//
//
//   std::cout << integral(zero, 0.f, 1.0, 0.00001f) << std::endl;
  return 0;
}

float root(float (* f)(float), float (* f1)(float),
           float (* g)(float), float (* g1)(float),
           LineSegment segment, float eps1, float &x)
{
  bool moveFromLeftToRight = false;

  std::function<float(float)> F = [&](float x) { return f(x) - g(x); };

  moveFromLeftToRight = F(segment.getCenter()) > (F(segment.a) + F(segment.b)) / 2
                        ? true
                        : false; /* !!! This may be wrong !!!*/

  float d = 0.f; // if (f1(x) * f2(x) > 0) { d = b} else {d = a}

  float c = d - f(d) / f1(d);


  if (c > 0){
    // same signs
  } else {
    // different signs
  }

  //from right
  if (f(c) * f(c - eps1) < 0) { return x; }

  //from left
  if (f(c) * f(c + eps1) < 0) { return x; }
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
