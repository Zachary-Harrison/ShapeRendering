#pragma once

#include "Shape.hpp"

class Cube : public Shape
{
  public:
    Cube(Triple<double> center, double sideLength);

    Cube(double centerX, double centerY, double centerZ, double sideLength);
};