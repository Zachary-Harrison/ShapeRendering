#pragma once

#include "Shape.hpp"

class Torus : public Shape
{
  public:
    Torus(Triple<double> center, double R_1, double R_2);

    Torus(double centerX, double centerY, double centerZ, double R_1, double R_2);
};