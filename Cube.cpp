#include "Cube.hpp"

#include "Matrix3x3.hpp"
#include "Triple.hpp"

Cube::Cube(double sideLength, Triple<double> center)
{
    this->Center = center;

    double halfLen = sideLength / 2;

    // generating the todouble and bottom of the cube
    for (double x = -halfLen; x <= halfLen; x += 0.75)
    {
        for (double y = -halfLen; y <= halfLen; y += 0.75)
        {
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, y, halfLen },
                                                         Triple<double>{ 0, 0, 1 }));
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, y, -halfLen },
                                                         Triple<double>{ 0, 0, -1 }));
        }
    }

    // Stack in the z-plane hollow squares in the xy-plane
    for (double z = -halfLen; z <= halfLen; z += 0.75)
    {
        // x sides of hollow square
        for (double x = -halfLen; x <= halfLen; x += 0.75)
        {
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, halfLen, z },
                                                         Triple<double>{ 0, 1, 0 }));
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, -halfLen, z },
                                                         Triple<double>{ 0, -1, 0 }));
        }
        // y sides of hollow square
        for (double y = -halfLen; y <= halfLen; y += 0.75)
        {
            this->_data.push_back(Vector<double, double>(Triple<double>{ halfLen, y, z },
                                                         Triple<double>{ 1, 0, 0 }));
            this->_data.push_back(Vector<double, double>(Triple<double>{ -halfLen, y, z },
                                                         Triple<double>{ -1, 0, 0 }));
        }
    }
}

Cube::Cube(double sideLength, double initialX, double initialY, double initialZ) :
    Cube(sideLength, Triple<double>{ initialX, initialY, initialZ })
{
}