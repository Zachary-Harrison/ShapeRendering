#include "Pyramid.hpp"

#include "../utils/Matrix3x3.hpp"
#include "../utils/Triple.hpp"

#include <cmath>

Pyramid::Pyramid(Triple<double> center, double length, double width, double height)
{
    this->Center = center;

    double halfLength = length / 2;
    double halfWidth = width / 2;
    double halfHeight = height / 2;

    for (double x = -halfLength; x <= halfLength; x += 0.75)
    {
        for (double y = -halfWidth; y <= halfWidth; y += 0.75)
        {
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, y, halfHeight },
                                                         Triple<double>{ 0, 0, 1 })); // base is facing upward
        }
    }

    double woh = width / height;  // woh = width over height
    double loh = length / height; // loh = width over height

    // Generating pyramid sides via cross - sections, starting at point of pyramid and moving to base)
    for (double z = -halfHeight; z <= halfHeight; z += 0.75)
    {
        double deltaH = (z + halfHeight);
        double widthProportion = deltaH * woh / 2;
        double lengthProportion = deltaH * loh / 2;

        for (double y = -widthProportion; y <= widthProportion; y += 0.75)
        {
            this->_data.push_back(Vector<double, double>(Triple<double>{ lengthProportion, y, z },
                                                         Triple<double>{ width, 0, -halfWidth * loh }));
            this->_data.push_back(Vector<double, double>(Triple<double>{ -lengthProportion, y, z },
                                                         Triple<double>{ -width, 0, -halfWidth * loh }));
        }

        for (double x = -lengthProportion; x <= lengthProportion; x += 0.75)
        {
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, widthProportion, z },
                                                         Triple<double>{ 0, length, -halfWidth * loh }));
            this->_data.push_back(Vector<double, double>(Triple<double>{ x, -widthProportion, z },
                                                         Triple<double>{ 0, -length, -halfWidth * loh }));
        }
    }
}

Pyramid::Pyramid(double centerX, double centerY, double centerZ, double length, double width, double height) :
    Pyramid(Triple<double>{ centerX, centerY, centerZ }, length, width, height)
{
}