#pragma once

#include "Renderer.hpp"
#include "Screen.hpp"
#include "utils/Vector.hpp"
#include "utils/rlutil.h"

#include <array>
#include <cstdint>
#include <stdexcept>
#include <vector>

template <typename P, typename D>
class RendererConsole : public Renderer<P, D>
{
  public:
    RendererConsole(Vector<P, D> camera, Triple<D> lightsource, Screen screen, Triple<P> shapeCenter);
    void render(const Shape& shape) override;

  private:
    Vector<P, D> _camera;
    Triple<D> _lightsource;
    Screen _screen;
    double K_1;
    double K_2;
    std::string _luminanceChars = " .,-~:;=!*#$@";
    std::vector<std::vector<double>> _zBuffer;
    std::vector<std::vector<std::uint8_t>> _buffer;
    std::vector<std::vector<std::uint8_t>> _prevBuffer;

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

    _prevBuffer = std::vector<std::vector<std::uint8_t>>(_screen.height(), std::vector<std::uint8_t>(_screen.width(), 0));
}

template <typename P, typename D>
void RendererConsole<P, D>::render(const Shape& shape)
{
    _zBuffer = std::vector<std::vector<double>>(_screen.height(), std::vector<double>(_screen.width(), 0));
    _buffer = std::vector<std::vector<std::uint8_t>>(_screen.height(), std::vector<std::uint8_t>(_screen.width(), 0));
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

        if ((x_proj >= 0 && x_proj < _screen.width() && y_proj >= 0 && y_proj < _screen.height()) // within the screen
            && ooz >= _zBuffer[y_proj][x_proj]                                                    // closer to screen than previous choices
        )
        {
            // if two points are equidistant, choose the brighter one.
            if (_zBuffer[y_proj][x_proj] == ooz)
            {
                // map luminance to _luminanceChars, excluding the first item (' ')
                std::uint8_t newLumIdx = static_cast<std::uint8_t>(1 + luminance * (_luminanceChars.size() - 2));
                // equivalent to _buffer[y_proj][x_proj] = max(_buffer[y_proj][x_proj], newLumIdx)
                _buffer[y_proj][x_proj] = (_buffer[y_proj][x_proj] < newLumIdx) ? newLumIdx : _buffer[y_proj][x_proj];
            }
            else
            {
                _zBuffer[y_proj][x_proj] = ooz;
                // map luminance to _luminanceChars, excluding the first item (' ')
                std::uint8_t newLumIdx = static_cast<std::uint8_t>(1 + luminance * (_luminanceChars.size() - 2));
                _buffer[y_proj][x_proj] = newLumIdx;
            }
        }
    }

    // In theory, the shape should already be centered in the console.
    for (int j = 0; j < _screen.height(); j++)
    {
        for (int i = 0; i < _screen.width(); i++)
        {
            if (_buffer[j][i] != _prevBuffer[j][i])
            {
                // Start at (1, 1) in case of Windows user
                rlutil::locate(i + 1, j + 1);
                std::cout << _luminanceChars[_buffer[j][i]];
            }
        }
    }
    _prevBuffer = _buffer;
}

template <typename P, typename D>
double RendererConsole<P, D>::getLuminance(const Vector<P, D>& vector)
{
    Triple<D> v_norm = vector.direction.normalized();
    double dotProduct = v_norm.x * _lightsource.x + v_norm.y * _lightsource.y + v_norm.z * _lightsource.z;
    // the above code is equivalent to:
    if (dotProduct > 0) // vectors with positive dot product => facing the same direction
    {
        return 0;
    }
    else // return a positive luminance
    {
        return -dotProduct;
    }
}