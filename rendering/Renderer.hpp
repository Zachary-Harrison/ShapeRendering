#pragma once

#include "../shapes/Shape.hpp"

class Renderer
{
  public:
    virtual void render(const Shape& shape) = 0;
    void togglePause() { _isPaused = !_isPaused; }
    bool isPaused() { return _isPaused; }

  private:
    bool _isPaused = false;
};