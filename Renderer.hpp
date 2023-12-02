#pragma once

#include "Shape.hpp"

template <typename P, typename D> // P = PositionType, D = DirectionType
class Renderer
{
  public:
    virtual void render(const Shape& shape) = 0;
    void togglePause();
    bool isPaused();

  private:
    bool _isPaused = false;
};

template <typename P, typename D>
void Renderer<P, D>::togglePause()
{
    _isPaused = !_isPaused;
}

template <typename P, typename D>
bool Renderer<P, D>::isPaused()
{
    return _isPaused;
}