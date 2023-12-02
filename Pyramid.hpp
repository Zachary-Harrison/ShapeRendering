#pragma once

#include "Matrix3x3.hpp"
#include "Shape.hpp"
#include "Triple.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Pyramid : public Shape<P, D>
{
  public:
    Pyramid(P length, P width, P height, Triple<P> center);

    Pyramid(P length, P width, P height, P initialX, P initialY, P initialZ);
};

template <typename P, typename D>
Pyramid<P, D>::Pyramid(P length, P width, P height, Triple<P> center)
{
    static_assert(std::is_arithmetic<P>::value, "Type P must be arithmetic");
    static_assert(std::is_arithmetic<D>::value, "Type D must be arithmetic");
    this->Center = center;

    P halfLength = length / 2;
    P halfWidth = width / 2;
    P halfHeight = height / 2;

    for (P x = -halfLength; x <= halfLength; x += 0.75)
    {
        for (P y = -halfWidth; y <= halfWidth; y += 0.75)
        {
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, y, halfHeight },
                                                   Triple<D>{ 0, 0, 1 })); // base is facing upward
        }
    }

    P woh = width / height;  // woh = width over height
    P loh = length / height; // loh = width over height

    // Generating pyramid sides via cross - sections, starting at point of pyramid and moving to base)
    for (P z = -halfHeight; z <= halfHeight; z += 0.75)
    {
        P deltaH = (z + halfHeight);
        P widthProportion = deltaH * woh / 2;
        P lengthProportion = deltaH * loh / 2;

        // y faces
        for (P y = -widthProportion; y <= widthProportion; y += 0.75)
        {
            this->_origData.push_back(Vector<P, D>(Triple<P>{ lengthProportion, y, z },
                                                   Triple<D>{ width, 0, -halfWidth * loh }));
            this->_origData.push_back(Vector<P, D>(Triple<P>{ -lengthProportion, y, z },
                                                   Triple<D>{ -width, 0, -halfWidth * loh }));
        }

        // x faces
        for (P x = -lengthProportion; x <= lengthProportion; x += 0.75)
        {
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, widthProportion, z },
                                                   Triple<D>{ 0, length, -halfWidth * loh }));
            this->_origData.push_back(Vector<P, D>(Triple<P>{ x, -widthProportion, z },
                                                   Triple<D>{ 0, -length, -halfWidth * loh }));
        }
    }
}

template <typename P, typename D>
Pyramid<P, D>::Pyramid(P length, P width, P height, P initialX, P initialY, P initialZ) :
    Pyramid(length, width, height, Triple<P>{ initialX, initialY, initialZ })
{
}