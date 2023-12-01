#pragma once

#include "Renderer.hpp"
#include "Screen.hpp"
#include "Vector.hpp"
#include "rlutil.h"

#include <array>
#include <cstdint>
#include <stdexcept>
#include <vector>

template <typename P, typename D> // P = PositionType, D = DirectionType
class RendererConsole : public Renderer<P, D>
{
  public:
    RendererConsole(Vector<P, D> camera, Triple<D> lightsource, Screen screen, Triple<P> shapeCenter);
    void render(const Shape<P, D>& shape) override;

  private:
    Vector<P, D> _camera;
    Triple<D> _lightsource;
    Screen _screen;
    std::string _luminanceChars = ".,-~:;=!*#$@";
    double K_1;
    double K_2;
    std::vector<std::vector<double>> _zBuffer;
    std::vector<std::vector<char>> _buffer;
    std::vector<std::vector<char>> _prevBuffer;

    double getLuminance(const Vector<P, D>& vector);
};

template <typename P, typename D>
RendererConsole<P, D>::RendererConsole(Vector<P, D> camera, Triple<D> lightsource, Screen screen, Triple<P> shapeCenter) :
    _camera(camera), _lightsource(lightsource), _screen(screen)
{
    static_assert(std::is_arithmetic<P>::value, "Type T must be arithmetic");

    K_1 = screen.distance();
    K_2 = shapeCenter.z - camera.position.z;
    // initialize variables
    if (K_1 < 0 || K_2 < 0)
    {
        throw std::range_error("Screen must be inbetween Camera and Shape");
    }

    // normalizing direction vectors
    _camera.direction = _camera.direction.normalized();
    _lightsource = _lightsource.normalized();

    _prevBuffer = std::vector<std::vector<char>>(_screen.height(), std::vector<char>(_screen.width(), ' '));
}

template <typename P, typename D>
void RendererConsole<P, D>::render(const Shape<P, D>& shape)
{
    _zBuffer = std::vector<std::vector<double>>(_screen.height(), std::vector<double>(_screen.width(), 0));
    _buffer = std::vector<std::vector<char>>(_screen.height(), std::vector<char>(_screen.width(), ' '));
    for (auto& vector : shape.data())
    {
        double luminance = getLuminance(vector);
        if (luminance < 0)
        {
            continue;
        }

        double ooz = 1 / (K_2 + vector.position.z); // "one over z"
        // projecting the 3D shape onto the 2D screen
        int x_proj = _screen.width() / 2 + static_cast<int>(K_1 * ooz * vector.position.x);
        int y_proj = _screen.height() / 2 - static_cast<int>(K_1 * ooz * vector.position.y);

        if (x_proj >= 0 && x_proj < _screen.width() && y_proj >= 0 && y_proj < _screen.height())
        {
            if (ooz > _zBuffer[y_proj][x_proj])
            {
                _zBuffer[y_proj][x_proj] = ooz;
                int lumIdx = static_cast<int>(luminance * (_luminanceChars.size() - 1));
                _buffer[y_proj][x_proj] = _luminanceChars[lumIdx];
            }
        }
    }

    // In theory, the shape should already be centered in the console.
    for (int j = 0; j < _screen.height(); j++)
    {
        for (int i = 0; i < _screen.width(); i++)
        {
            // Display only chars that have changed
            if (_buffer[j][i] != _prevBuffer[j][i])
            {
                // Start at (1, 1) in case of Windows user
                rlutil::locate(i + 1, j + 1);
                std::cout << _buffer[j][i];
            }
        }
    }
    _prevBuffer = _buffer;
}

template <typename P, typename D>
double RendererConsole<P, D>::getLuminance(const Vector<P, D>& vector)
{
    Triple<D> v_norm = vector.direction.normalized();
    // return v_norm.x * _lightsource.x + v_norm.y * _lightsource.y + v_norm.z * _lightsource.z;
    double result = v_norm.x * _lightsource.x + v_norm.y * _lightsource.y + v_norm.z * _lightsource.z;
    // return (result > 0) ? result : -result; // equivalent to abs(result);
    return (result > 0) ? result : 0; // equivalent to max(result, 0);
}