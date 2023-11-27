#pragma once

#include <type_traits>

class Screen
{
  public:
    Screen(int width, int height, int distance);
    int width() const;
    int height() const;
    int distance() const;

  private:
    int _width;
    int _height;
    int _distance;
};