#pragma once

#include "Shape.hpp"

class Cylinder : public Shape
{
  public:
    Cylinder(double height, double radius, Triple<double> center);

    Cylinder(double height, double radius, double initialX, double initialY, double initialZ);
};
