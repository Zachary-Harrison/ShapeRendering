#pragma once

#include "../utils/Matrix3x3.hpp"
#include "../utils/Triple.hpp"
#include "Shape.hpp"

class Pyramid : public Shape
{
  public:
    Pyramid(Triple<double> center, double length, double width, double height);

    Pyramid(double centerX, double centerY, double centerZ, double length, double width, double height);
};
