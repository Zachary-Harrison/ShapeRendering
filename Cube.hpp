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

    // Normals for x faces
    Triple<D> posXNormal{ 1, 0, 0 };
    Triple<D> negXNormal{ -1, 0, 0 };
    for (P y = -halfLen; y <= halfLen; y += 1)
    {
        for (P z = -halfLen; z <= halfLen; z += 1)
        {
            this->_origData.push_back(Vector<P, P>(Triple<P>{ -halfLen, y, z }, posXNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ halfLen, y, z }, negXNormal));
        }
    }

    // Normals for y faces
    Triple<D> posYNormal{ 0, 1, 0 };
    Triple<D> negYNormal{ 0, -1, 0 };
    for (P x = -halfLen; x <= halfLen; x += 1)
    {
        for (P z = -halfLen; z <= halfLen; z += 1)
        {
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, -halfLen, z }, posYNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, halfLen, z }, negYNormal));
        }
    }

    // Normals for z faces
    Triple<D> posZNormal{ 0, 0, 1 };
    Triple<D> negZNormal{ 0, 0, -1 };
    for (P x = -halfLen; x <= halfLen; x += 1)
    {
        for (P y = -halfLen; y <= halfLen; y += 1)
        {
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, y, -halfLen }, posZNormal));
            this->_origData.push_back(Vector<P, P>(Triple<P>{ x, y, halfLen }, negZNormal));
        }
    }
}

template <typename P, typename D>
Cube<P, D>::Cube(P sideLength, P initialX, P initialY, P initialZ) :
    Cube(sideLength, Triple<P>{ initialX, initialY, initialZ })
{
}