#include "Sphere.hpp"

#include "Matrix3x3.hpp"
#include "Triple.hpp"

#include <cmath>

Sphere::Sphere(double Radius, Triple<double> center)
{
    this->Center = center;

    // Iterate over theta and phi to generate points on the sphere's surface
    for (double phi = 0; phi <= PI; phi += 0.05)
    {
        for (double theta = 0; theta <= 2 * PI; theta += 0.1)
        {
            double x = Radius * sin(phi) * cos(theta);
            double y = Radius * sin(phi) * sin(theta);
            double z = Radius * cos(phi);

            this->_data.push_back(Vector<double, double>(Triple<double>{ x, y, z },
                                                         Triple<double>{ x / Radius, y / Radius, z / Radius }));
        }
    }
}

Sphere::Sphere(double Radius, double initialX, double initialY, double initialZ) :
    Sphere(Radius, Triple<double>{ initialX, initialY, initialZ })
{
}