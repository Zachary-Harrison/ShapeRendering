#pragma once

#include "Shape.hpp"

class Torus : public Shape
{
  public:
    Torus(double R_1, double R_2, Triple<double> center);

    Torus(double R_1, double R_2, double initialX, double initialY, double initialZ);
};