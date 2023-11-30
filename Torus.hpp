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

    for (double xAngle = 0; xAngle < TAU; xAngle += 0.05)
    {
        P sinX = sin(xAngle);
        P cosX = cos(xAngle);

        P circleX = R_2 + R_1 * cosX;
        P circleY = R_1 * sinX;
        for (double yAngle = 0; yAngle < 2 * TAU; yAngle += 0.02)
        {
            P sinY = sin(yAngle);
            P cosY = cos(yAngle);
            Triple<P> pos{
                cosY * circleX,
                circleY,
                -sinY * circleX
            };
            Triple<D> normal{
                cosY * cosX,
                sinX,
                -sinY * cosX
            };
            // Matrix3x3<double> rotY{
            //     { cosY, 0, sinY },
            //     { 0, 1, 0 },
            //     { -sinY, 0, cosY }
            // };
            //  Triple<P> pos = rotY * Triple<P>{ circleX, circleY, circleX };
            //  Triple<D> normal = rotY * Triple<D>{ cosX, cosY, 0 };
            this->_origData.push_back(Vector<P, P>{ pos, normal });
        }
    }
}

template <typename P, typename D>
Torus<P, D>::Torus(P R_1, P R_2, P initialX, P initialY, P initialZ) :
    Cube(R_1, R_2, Triple<P>{ initialX, initialY, initialZ })
{
}