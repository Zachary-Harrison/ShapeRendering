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

    // Generate hollow circle of radius R_1 in the xy-plane
    for (double xAngle = 0; xAngle < TAU; xAngle += 0.05)
    {
        P sinX = sin(xAngle);
        P cosX = cos(xAngle);

        P circleX = R_1 * cosX + R_2;
        P circleY = R_1 * sinX;

        Triple<P> position = { circleX, circleY, 0 };
        Triple<D> normal = { cosX, sinX, 0 };
        // Rotate each point on the circle around the y-axis
        for (double yAngle = 0; yAngle < TAU; yAngle += 0.02)
        {
            Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
            this->_origData.push_back(Vector<P, D>{ rotY * position,
                                                    rotY * normal });
        }
    }
}

template <typename P, typename D>
Torus<P, D>::Torus(P R_1, P R_2, P initialX, P initialY, P initialZ) :
    Cube(R_1, R_2, Triple<P>{ initialX, initialY, initialZ })
{
}