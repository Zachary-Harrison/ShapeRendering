#include "RendererConsole.hpp"
#include "Screen.hpp"
#include "shapes/Cube.hpp"
#include "shapes/Cylinder.hpp"
#include "shapes/Pyramid.hpp"
#include "shapes/Shape.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Torus.hpp"
#include "utils/Vector.hpp"
#include "utils/rlutil.h"

#include <array>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <thread>

int main()
{
    // Handles Ctrl + C exit behavior
    std::signal(SIGINT, [](int signum) {
        rlutil::cls(); // clear the console
        exit(signum);
    });

    // Keep these multiples of each other so that all sides are seen and rotation feels cyclic and rhythmic
    double X_ANGLE = 0.03;
    double Y_ANGLE = 0.02;
    double Z_ANGLE = 0.04;

    Vector<double, double> camera{ 0, 0, 0, 0, 0, 1 };
    Triple<double> lightsource{ 1, -1, 1 };
    Triple<double> shapeCenter{ 0, 0, 80 };
    Screen screen{ 80, 30, 40 };
    RendererConsole renderer{ camera, lightsource, screen, shapeCenter };

    // Generating the list of shapes
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Cube>(shapeCenter, 30));
    shapes.push_back(std::make_unique<Torus>(shapeCenter, 7, 15));
    shapes.push_back(std::make_unique<Pyramid>(shapeCenter, 30, 40, 30));
    shapes.push_back(std::make_unique<Sphere>(shapeCenter, 20));
    shapes.push_back(std::make_unique<Cylinder>(shapeCenter, 30, 15));
    int currentShapeIndex = 0;

    rlutil::hidecursor();
    rlutil::cls();
    for (bool done = false; !done;)
    {
        // update render loop
        if (!renderer.isPaused())
        {
            auto start = std::chrono::high_resolution_clock::now();

            shapes[currentShapeIndex]->update(X_ANGLE, Y_ANGLE, Z_ANGLE);

            renderer.render((*shapes[currentShapeIndex]));
            std::cout.flush(); // force console changes to render

            // don't render faster than 60 FPS
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            int sleepTime = 16 - duration;
            if (sleepTime > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }

        // handle user input
        if (kbhit())
        {
            int key = rlutil::getkey();

            if (key == rlutil::KEY_ESCAPE)
            {
                done = true;
            }
            else if (key == rlutil::KEY_SPACE)
            {
                renderer.togglePause();
            }
            else if (key == rlutil::KEY_LEFT)
            {
                currentShapeIndex = (currentShapeIndex - 1 + shapes.size()) % shapes.size();
            }
            else if (key == rlutil::KEY_RIGHT)
            {
                currentShapeIndex = (currentShapeIndex + 1) % shapes.size();
            }
        }
    }
    // cleanup to not disturb potential console users
    rlutil::showcursor();
    rlutil::cls();

    return 0;
}