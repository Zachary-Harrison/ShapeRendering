#include "Shape.hpp"

#include "Matrix3x3.hpp"

#include <cmath>

Shape::Shape() :
    _data{}, Center{ 0, 0, 0 } // Initialize data to zeros
{
}

Shape::Shape(const std::vector<Vector<double, double>>& data, Triple<double> center) :
    _data(data), Center(center)
{
}

Shape::Shape(const Shape& shape) :
    _data(shape.data()), Center(shape.Center)
{
}

void Shape::update(double xAngle, double yAngle, double zAngle)
{
    Matrix3x3<double> rotX = Matrix3x3<double>::rotationX(xAngle);
    Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
    Matrix3x3<double> rotZ = Matrix3x3<double>::rotationZ(zAngle);
    Matrix3x3<double> rot = rotZ * rotY * rotX;

    std::vector<Vector<double, double>> newData;
    // Rotate the points and their surface normals
    for (const Vector<double, double>& vector : this->_data)
    {
        Vector<double, double> newVector;
        newVector.position = rot * vector.position;
        newVector.direction = rot * vector.direction;
        newData.push_back(newVector);
    }

    // Update data
    this->_data = newData;
}

const std::vector<Vector<double, double>> Shape::data() const
{
    return this->_data;
}