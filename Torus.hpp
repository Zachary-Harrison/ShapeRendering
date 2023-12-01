#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Torus : public Shape<P, D>
{
  public:
    Torus(P R_1, P R_2, Triple<P> center);

    Torus(P R_1, P R_2, P initialX, P initialY, P initialZ);

  private:
    double PI = 3.141592653589793238462643383279502884197169399375105820974944; // not sure how many digits to use
    double TAU = 2 * PI;
};

template <typename P, typename D>
Torus<P, D>::Torus(P R_1, P R_2, Triple<P> center)
{
    static_assert(std::is_arithmetic<P>::value, "Type P must be arithmetic");
    static_assert(std::is_arithmetic<D>::value, "Type D must be arithmetic");
    this->Center = center;

    // generate circle of radius R_1
    for (double xAngle = 0; xAngle < TAU; xAngle += 0.05)
    {
        P sinX = sin(xAngle);
        P cosX = cos(xAngle);

        P circleX = R_2 + R_1 * cosX;
        P circleY = R_1 * sinX;
        // rotate circle around y-axis using radius R_2
        for (double yAngle = 0; yAngle < 2 * TAU; yAngle += 0.02)
        {
            Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
            Triple<P> pos = rotY * Triple<P>{ circleX, circleY, 0 };
            Triple<P> normal = rotY * Triple<P>{ -cosX, -sinX, 0 };
            this->_origData.push_back(Vector<P, P>{ pos, normal });
        }
    }
}

template <typename P, typename D>
Torus<P, D>::Torus(P R_1, P R_2, P initialX, P initialY, P initialZ) :
    Cube(R_1, R_2, Triple<P>{ initialX, initialY, initialZ })
{
}