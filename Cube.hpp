#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Cube : public Shape<P, D>
{
  public:
    Cube(P sideLength, Triple<P> center);

    Cube(P sideLength, P initialX, P initialY, P initialZ);
};

template <typename P, typename D>
Cube<P, D>::Cube(P sideLength, Triple<P> center)
{
    static_assert(std::is_arithmetic<P>::value, "Type P must be arithmetic");
    static_assert(std::is_arithmetic<D>::value, "Type D must be arithmetic");
    this->Center = center;

    P halfLen = sideLength / 2;

    // generating the top and bottom of the cube
    for (P x = -halfLen; x <= halfLen; x += 0.75)
    {
        for (P y = -halfLen; y <= halfLen; y += 0.75)
        {
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, y, halfLen },
                                                   Triple<D>{ 0, 0, 1 }));
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, y, -halfLen },
                                                   Triple<D>{ 0, 0, -1 }));
        }
    }

    // Stack in the z-plane hollow squares in the xy-plane
    for (P z = -halfLen; z <= halfLen; z += 0.75)
    {
        // x sides of hollow square
        for (P x = -halfLen; x <= halfLen; x += 0.75)
        {
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, halfLen, z },
                                                   Triple<D>{ 0, 1, 0 }));
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, -halfLen, z },
                                                   Triple<D>{ 0, -1, 0 }));
        }
        // y sides of hollow square
        for (P y = -halfLen; y <= halfLen; y += 0.75)
        {
            this->_origData.push_back(Vector<P, D>(Triple<P>{ halfLen, y, z },
                                                   Triple<D>{ 1, 0, 0 }));
            this->_origData.push_back(Vector<P, D>(Triple<P>{ -halfLen, y, z },
                                                   Triple<D>{ -1, 0, 0 }));
        }
    }
}

template <typename P, typename D>
Cube<P, D>::Cube(P sideLength, P initialX, P initialY, P initialZ) :
    Cube(sideLength, Triple<P>{ initialX, initialY, initialZ })
{
}