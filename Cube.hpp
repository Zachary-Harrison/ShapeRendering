#pragma once

#include "Shape.hpp"

class Cube : public Shape
{
  public:
    Cube(double sideLength, Triple<double> center);

    Cube(double sideLength, double initialX, double initialY, double initialZ);
};