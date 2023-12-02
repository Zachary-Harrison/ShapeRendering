#pragma once

#include "Shape.hpp"

class Cylinder : public Shape
{
  public:
    Cylinder(Triple<double> center, double height, double radius);

    Cylinder(double centerX, double centerY, double centerZ, double height, double radius);
};
