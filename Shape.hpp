#pragma once

#include "Vector.hpp"

#include <cmath>
#include <type_traits>
#include <vector>

template <typename P, typename D> // P = PositionType, D = DirectionType
class Shape
{
  public:
    Shape();

    Shape(const std::vector<Vector<P, D>>& data, Triple<P> center);

    Shape(const Shape& shape);

    virtual ~Shape() = default;

    virtual void update(double xAngle, double yAngle, double zAngle) = 0;

    const std::vector<Vector<P, D>> data() const;

    const Triple<P> center() const;

  protected:
    std::vector<Vector<P, D>> _data;
    Triple<P> _center;
    void setCenter(const Triple<P>& center);
};

template <typename P, typename D>
Shape<P, D>::Shape() :
    _data{} // Initialize data to zeros
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Shape<P, D>::Shape(const std::vector<Vector<P, D>>& data, Triple<P> center) :
    _data(data), _center(center)
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Shape<P, D>::Shape(const Shape& shape) :
    _data(shape.data()), _center(shape.center())
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
const std::vector<Vector<P, D>> Shape<P, D>::data() const
{
    return this->_data;
}

template <typename P, typename D>
const Triple<P> Shape<P, D>::center() const
{
    return this->_center;
}

template <typename P, typename D>
void Shape<P, D>::setCenter(const Triple<P>& center)
{
    _center = center;
}