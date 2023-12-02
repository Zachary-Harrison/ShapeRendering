#pragma once

#include "../utils/Matrix3x3.hpp"
#include "../utils/Triple.hpp"
#include "Shape.hpp"

class Sphere : public Shape
{
  public:
    Sphere(Triple<double> center, double Radius);

    Sphere(double centerX, double centerY, double centerZ, double Radius);
};