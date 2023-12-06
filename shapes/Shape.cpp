#include "Shape.hpp"

#include "../utils/Matrix3x3.hpp"

#include <algorithm> // for std::transform
#include <cmath>
#include <execution> // for std::execution::par

Shape::Shape() :
    Center{ 0, 0, 0 }, _data{} // Initialize data to zeros
{
}

Shape::Shape(Triple<double> center, const std::vector<Vector<double, double>>& data) :
    Center(center), _data(data)
{
}

Shape::Shape(const Shape& shape) :
    Center(shape.Center), _data(shape.data())
{
}

void Shape::update(double xAngle, double yAngle, double zAngle)
{
    Matrix3x3<double> rotX = Matrix3x3<double>::rotationX(xAngle);
    Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
    Matrix3x3<double> rotZ = Matrix3x3<double>::rotationZ(zAngle);
    Matrix3x3<double> rot = rotZ * rotY * rotX;

    // Rotate the points and their surface normals
    std::transform(std::execution::par, this->_data.begin(), this->_data.end(), this->_data.begin(),
                   [&rot](Vector<double, double>& vector)
                   {
                       vector.position = rot * vector.position;
                       vector.direction = rot * vector.direction;
                       return vector;
                   });
}

const std::vector<Vector<double, double>> Shape::data() const
{
    return this->_data;
}