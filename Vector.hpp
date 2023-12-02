#pragma once

#include "Triple.hpp"

#include <type_traits>

template <typename P, typename D> // P = PositionType, D = DirectionType
class Vector
{
  public:
    Vector();
    Vector(P xPos, P yPos, P zPos, D xDir, D yDir, D zDir);
    Vector(const Triple<P>& position, const Triple<D>& direction);
    Vector(const Vector& vector);

    Triple<P> position;
    Triple<D> direction;
};

// Definitions
template <typename P, typename D>
Vector<P, D>::Vector() :
    position(), direction()
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Vector<P, D>::Vector(P xPos, P yPos, P zPos, D xDir, D yDir, D zDir) :
    position(xPos, yPos, zPos), direction(xDir, yDir, zDir)
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Vector<P, D>::Vector(const Triple<P>& pos, const Triple<D>& dir) :
    position(pos), direction(dir)
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Vector<P, D>::Vector(const Vector& vector) :
    position(vector.position), direction(vector.direction)
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}