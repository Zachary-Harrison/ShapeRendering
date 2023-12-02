#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

class Sphere : public Shape
{
  public:
    Sphere(double Radius, Triple<double> center);

    Sphere(double Radius, double initialX, double initialY, double initialZ);
};