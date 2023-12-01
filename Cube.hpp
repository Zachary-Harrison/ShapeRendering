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

    Triple<D> posXNormal{ 1, 0, 0 };
    Triple<D> negXNormal{ -1, 0, 0 };
    Triple<D> posYNormal{ 0, 1, 0 };
    Triple<D> negYNormal{ 0, -1, 0 };
    Triple<D> posZNormal{ 0, 0, 1 };
    Triple<D> negZNormal{ 0, 0, -1 };
    for (P i = -halfLen; i <= halfLen; i += 0.75)
    {
        for (P j = -halfLen; j <= halfLen; j += 0.75)
        {
            // x faces
            this->_origData.push_back(Vector<P, P>(Triple<P>{ -halfLen, i, j }, posXNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ halfLen, i, j }, negXNormal));
            // y faces
            this->_origData.push_back(Vector<P, P>(Triple<P>{ i, -halfLen, j }, posYNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ i, halfLen, j }, negYNormal));
            // z faces
            this->_origData.push_back(Vector<P, P>(Triple<P>{ i, j, -halfLen }, posZNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ i, j, halfLen }, negZNormal));
        }
    }
}

template <typename P, typename D>
Cube<P, D>::Cube(P sideLength, P initialX, P initialY, P initialZ) :
    Cube(sideLength, Triple<P>{ initialX, initialY, initialZ })
{
}