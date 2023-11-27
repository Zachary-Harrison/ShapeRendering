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
    double PI = 3.141592653589793238462643383279502884197169399375105820974944; // not sure how many digits to use
    double TAU = 2 * PI;
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
    Screen screen{ 120, 30, 40 };
    RendererConsole renderer{ camera, lightsource, screen, shapeCenter };
    std::unique_ptr<Shape<double, double>> currentShape = std::make_unique<Cube<double, double>>(40, shapeCenter);

    currentShape->update(0, 0, 0);
    rlutil::hidecursor();
    rlutil::cls();

    // renderer.togglePause();

    for (bool done = false; !done;)
    {
        // update render loop
        if (!renderer.isPaused())
        {
            currentShape->update(xAngle, yAngle, zAngle);
            xAngle += X_ANGLE_INCREMENT;
            xAngle = (xAngle > TAU) ? xAngle - TAU : xAngle;
            yAngle += Y_ANGLE_INCREMENT;
            yAngle = (yAngle > TAU) ? yAngle - TAU : yAngle;
            zAngle += Z_ANGLE_INCREMENT;
            zAngle = (zAngle > TAU) ? zAngle - TAU : zAngle;

            renderer.render(*currentShape); // not sure if this is allowed due to unique_pointer
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            std::cout.flush(); // force console changes to render
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
    }
    // cleanup to not disturb potential console users
    rlutil::showcursor();
    rlutil::cls();

    return 0;
}