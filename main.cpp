#include "Cube.hpp"
#include "RendererConsole.hpp"
#include "Screen.hpp"
#include "Shape.hpp"
#include "Vector.hpp"
#include "rlutil.h"

#include <array>
#include <cstdint>
#include <thread>

int main()
{
    double xAngle = 0.0;
    double yAngle = 0.0;
    double zAngle = 0.0;
    // double X_ANGLE_INCREMENT = 0.0;
    // double Y_ANGLE_INCREMENT = 0.0;
    // double Z_ANGLE_INCREMENT = 0.0;
    double X_ANGLE_INCREMENT = 0.05;
    double Y_ANGLE_INCREMENT = 0.05;
    double Z_ANGLE_INCREMENT = 0.01;

    Vector<double, double> camera{ 0, 0, 0, 0, 0, 1 };
    Vector<double, double> lightsource{ 0, 0, 0, 0, 0, 1 }; // pointed directly at the shape
    // Vector<double, double> lightsource{ 0, 50, 0, 0, -0.7071, 0.7071 }; // pointed above the shape
    Triple<double> shapeCenter{ 0, 0, 110 };
    Screen screen{ 160, 44, 40 };
    RendererConsole renderer{ camera, lightsource, screen, shapeCenter };
    std::unique_ptr<Shape<double, double>> currentShape = std::make_unique<Cube<double, double>>(40, shapeCenter);

    rlutil::hidecursor();
    rlutil::cls();

    for (bool done = false; !done;)
    {
        // update render loop
        if (!renderer.isPaused())
        {
            currentShape->update(xAngle, yAngle, zAngle);
            xAngle += X_ANGLE_INCREMENT;
            yAngle += Y_ANGLE_INCREMENT;
            zAngle += Z_ANGLE_INCREMENT;
            renderer.render(*currentShape); // not sure if this is allowed due to unique_pointer
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
        }
        std::cout.flush(); // force console changes to render
    }
    // cleanup to not disturb potential console users
    rlutil::showcursor();
    rlutil::cls();

    return 0;
}