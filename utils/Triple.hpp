#pragma once

#include <cmath>

template <typename T>
class Triple
{
  public:
    T x, y, z;

    Triple<T> normalized() const
    {
        T magnitude = std::sqrt(x * x + y * y + z * z);
        return { x / magnitude, y / magnitude, z / magnitude };
    }
};