#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

class Pyramid : public Shape
{
  public:
    Pyramid(double length, double width, double height, Triple<double> center);

    Pyramid(double length, double width, double height, double initialX, double initialY, double initialZ);
};
