#include "Screen.hpp"

Screen::Screen(int width, int height, int distance)
{
    _width = width;
    _height = height;
    _distance = distance;
}

int Screen::width() const
{
    return _width;
}

int Screen::height() const
{
    return _height;
}

int Screen::distance() const
{
    return _distance;
}
