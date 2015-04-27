struct LineSegment
{
  float a;
  float b;

  LineSegment(float a, float b) :
    a(a),
    b(b)
  {}

  LineSegment getLowHalf()
  {
    return LineSegment(a, getCenter());
  }

  LineSegment getHighHalf()
  {
    return LineSegment(getCenter(), b);
  }

  float getCenter()
  {
    return (a + b) / 2;
  }
};
