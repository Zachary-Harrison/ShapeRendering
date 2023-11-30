#pragma once

#include "Vector.hpp"

#include <cmath>
#include <type_traits>
#include <vector>

template <typename P, typename D> // P = PositionType, D = DirectionType
class Shape
{
  public:
    Triple<P> Center;
    Shape();

    Shape(const std::vector<Vector<P, D>>& data, Triple<P> center);

    Shape(const Shape& shape);

    virtual ~Shape() = default;

    void update(double xAngle, double yAngle, double zAngle);

    const std::vector<Vector<P, D>> data() const;

  protected:
    std::vector<Vector<P, D>> _origData;
    std::vector<Vector<P, D>> _data;
};

template <typename P, typename D>
Shape<P, D>::Shape() :
    _data{} // Initialize data to zeros
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Shape<P, D>::Shape(const std::vector<Vector<P, D>>& data, Triple<P> center) :
    _data(data), Center(center)
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
Shape<P, D>::Shape(const Shape& shape) :
    _data(shape.data()), Center(shape.Center())
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");
}

template <typename P, typename D>
void Shape<P, D>::update(double xAngle, double yAngle, double zAngle)
{
    Matrix3x3<double> rotX = Matrix3x3<double>::rotationX(xAngle);
    Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
    Matrix3x3<double> rotZ = Matrix3x3<double>::rotationZ(zAngle);

    Matrix3x3<double> rot = rotZ * rotY * rotX;

    std::vector<Vector<P, D>> newData;
    // Rotate the points and their surface normals
    for (const Vector<P, D>& vector : this->_origData)
    {
        Vector<P, D> newVector;
        newVector.position = rot * vector.position;
        newVector.direction = rot * vector.direction;
        newData.push_back(newVector);
    }

    // Update data
    this->_data = newData;
}

template <typename P, typename D>
const std::vector<Vector<P, D>> Shape<P, D>::data() const
{
    return this->_data;
}