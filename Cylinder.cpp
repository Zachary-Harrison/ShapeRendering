#include "Cylinder.hpp"

#include "Matrix3x3.hpp"
#include "Triple.hpp"

Cylinder::Cylinder(double height, double radius, Triple<double> center)
{
    this->Center = center;

    double halfHeight = height / 2;

    // Rotate rectangle in the yz-plane aroundouble the z-axis
    for (double yAngle = 0; yAngle < TAU; yAngle += 0.02)
    {
        Matrix3x3<double> rotZ = Matrix3x3<double>::rotationZ(yAngle);
        // todouble andouble bottom of rectangle
        for (double y = 0; y <= radius; y += 0.75)
        {
            this->_data.push_back(Vector<double, double>{ rotZ * Triple<double>{ 0, y, halfHeight },
                                                              rotZ * Triple<double>{ 0, 0, 1 } });
            this->_data.push_back(Vector<double, double>{ rotZ * Triple<double>{ 0, y, -halfHeight },
                                                              rotZ * Triple<double>{ 0, 0, -1 } });
        }

        // Rectangle side in the y-axis
        for (double z = -halfHeight; z <= halfHeight; z += 0.75)
        {
            this->_data.push_back(Vector<double, double>{ rotZ * Triple<double>{ 0, radius, z },
                                                              rotZ * Triple<double>{ 0, 1, 0 } });
        }
    }
}

Cylinder::Cylinder(double height, double radius, double initialX, double initialY, double initialZ) :
    Cylinder(height, radius, Triple<double>{ initialX, initialY, initialZ })
{
}