#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Sphere : public Shape<P, D>
{
  public:
    Sphere(P Radius, Triple<P> center);

    Sphere(P Radius, P initialX, P initialY, P initialZ);

  private:
    double PI = 3.141592653589793238462643383279502884197169399375105820974944; // not sure how many digits to use
    double TAU = 2 * PI;
};

template <typename P, typename D>
Sphere<P, D>::Sphere(P Radius, Triple<P> center)
{
    static_assert(std::is_arithmetic<P>::value, "Type P must be arithmetic");
    static_assert(std::is_arithmetic<D>::value, "Type D must be arithmetic");
    this->Center = center;

    // Iterate over theta and phi to generate points on the sphere's surface
    for (double phi = 0; phi <= PI; phi += 0.05)
    {
        for (double theta = 0; theta <= 2 * PI; theta += 0.1)
        {
            P x = Radius * sin(phi) * cos(theta);
            P y = Radius * sin(phi) * sin(theta);
            P z = Radius * cos(phi);

            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, y, z },
                                                   Triple<D>{ x / Radius, y / Radius, z / Radius }));
        }
    }
}

template <typename P, typename D>
Sphere<P, D>::Sphere(P Radius, P initialX, P initialY, P initialZ) :
    Cube(Radius, Triple<P>{ initialX, initialY, initialZ })
{
}