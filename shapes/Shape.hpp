#pragma once

#include "../utils/Vector.hpp"

#include <vector>

class Shape
{
  public:
    Triple<double> Center;
    Shape();

    Shape(Triple<double> center, const std::vector<Vector<double, double>>& data);

    Shape(const Shape& shape);

    virtual ~Shape() = default;

    void update(double xAngle, double yAngle, double zAngle);

    const std::vector<Vector<double, double>> data() const;

  protected:
    const double PI = 3.141592653589793238462643383279502884197169399375105820974944; // not sure how many digits to use
    const double TAU = 2 * PI;
    std::vector<Vector<double, double>> _data;
};