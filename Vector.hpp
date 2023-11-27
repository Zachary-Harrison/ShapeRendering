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
    P getLuminance(const Vector& other) const;

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

template <typename P, typename D>
P Vector<P, D>::getLuminance(const Vector<P, D>& lightsource) const
{
    return direction.x * lightsource.direction.x + direction.y * lightsource.direction.y + direction.z * lightsource.direction.z;
}