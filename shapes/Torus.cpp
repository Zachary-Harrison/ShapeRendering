#include "Torus.hpp"

#include "../utils/Matrix3x3.hpp"
#include "../utils/Triple.hpp"

#include <cmath>

Torus::Torus(Triple<double> center, double R_1, double R_2)
{
    this->Center = center;

    // Generate hollow circle of radius R_1 in the xy-plane
    for (double xAngle = 0; xAngle < TAU; xAngle += 0.05)
    {
        double sinX = sin(xAngle);
        double cosX = cos(xAngle);

        double circleX = R_1 * cosX + R_2;
        double circleY = R_1 * sinX;

        Triple<double> position = { circleX, circleY, 0 };
        Triple<double> normal = { cosX, sinX, 0 };
        // Rotate each point on the circle around the y-axis
        for (double yAngle = 0; yAngle < TAU; yAngle += 0.02)
        {
            Matrix3x3<double> rotY = Matrix3x3<double>::rotationY(yAngle);
            this->_data.push_back(Vector<double, double>{ rotY * position,
                                                          rotY * normal });
        }
    }
}

Torus::Torus(double centerX, double centerY, double centerZ, double R_1, double R_2) :
    Torus(Triple<double>{ centerX, centerY, centerZ }, R_1, R_2)
{
}