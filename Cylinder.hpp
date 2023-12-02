#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Cylinder : public Shape<P, D>
{
  public:
    Cylinder(P height, P radius, Triple<P> center);

    Cylinder(P height, P radius, P initialX, P initialY, P initialZ);

  private:
    double PI = 3.141592653589793238462643383279502884197169399375105820974944; // not sure how many digits to use
    double TAU = 2 * PI;
};

template <typename P, typename D>
Cylinder<P, D>::Cylinder(P height, P radius, Triple<P> center)
{
    static_assert(std::is_arithmetic<P>::value, "Type P must be arithmetic");
    static_assert(std::is_arithmetic<D>::value, "Type D must be arithmetic");
    this->Center = center;

    P halfHeight = height / 2;

    //// Generating top and bottom of cylinder by fitting circles of increasing radius together
    // for (double theta = 0; theta < TAU; theta += 0.05)
    //{
    //     P sinTheta = sin(theta);
    //     P cosTheta = cos(theta);
    //     for (double r = 0; r < radius; r += 0.75)
    //     {
    //         P circleX = r * cosTheta;
    //         P circleY = r * sinTheta;
    //         this->_origData.push_back(Vector<P, D>{ Triple<P>{ circleX, circleY, halfHeight },
    //                                                 Triple<D>{ 0, 0, 1 } });
    //         this->_origData.push_back(Vector<P, D>{ Triple<P>{ circleX, circleY, -halfHeight },
    //                                                 Triple<D>{ 0, 0, -1 } });
    //     }
    // }
    //// Generating sides of cylinder by stacking hollow circles in the z-direction
    // for (P z = -halfHeight; z <= halfHeight; z += 0.75)
    //{
    //     Triple<P> position{ 0, radius, z };
    //     Triple<P> normal{ 0, 1, 1 };

    //    // Generate the circle by rotating a point around the y-axis
    //    for (P yAngle = 0; yAngle < TAU; yAngle += 0.02)
    //    {
    //        Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
    //        this->_origData.push_back(Vector<P, D>{ rotY * position,
    //                                                rotY * normal });
    //    }
    //}

    // Rotate rectangle in the yz-plane around the z-axis
    for (P yAngle = 0; yAngle < TAU; yAngle += 0.02)
    {
        Matrix3x3<double> rotZ = Matrix3x3<double>::rotationZ(yAngle);
        // top and bottom of rectangle
        for (P y = 0; y <= radius; y += 0.75)
        {
            this->_origData.push_back(Vector<P, D>{ rotZ * Triple<P>{ 0, y, halfHeight },
                                                    rotZ * Triple<D>{ 0, 0, 1 } });
            this->_origData.push_back(Vector<P, D>{ rotZ * Triple<P>{ 0, y, -halfHeight },
                                                    rotZ * Triple<D>{ 0, 0, -1 } });
        }

        // Rectangle side in the y-axis
        for (P z = -halfHeight; z <= halfHeight; z += 0.75)
        {
            this->_origData.push_back(Vector<P, D>{ rotZ * Triple<P>{ 0, radius, z },
                                                    rotZ * Triple<D>{ 0, 1, 0 } });
        }
    }
}

template <typename P, typename D>
Cylinder<P, D>::Cylinder(P height, P radius, P initialX, P initialY, P initialZ) :
    Cube(height, radius, Triple<P>{ initialX, initialY, initialZ })
{
}