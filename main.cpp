#include "Cube.hpp"
#include "Pyramid.hpp"
#include "RendererConsole.hpp"
#include "Screen.hpp"
#include "Shape.hpp"
#include "Torus.hpp"
#include "Vector.hpp"
#include "rlutil.h"

#include <array>
#include <cstdint>
#include <thread>

int main()
{
    double PI = 3.141592653589793238462643383279502884197169399375105820974944; // not sure how many digits to use
    double TAU = 2 * PI;
    // double X_ANGLE_INCREMENT = 0;
    // double Y_ANGLE_INCREMENT = 0;
    // double Z_ANGLE_INCREMENT = 0;
    double X_ANGLE_INCREMENT = 0.05;
    double Y_ANGLE_INCREMENT = 0.05;
    double Z_ANGLE_INCREMENT = 0.01;

    Vector<double, double> camera{ 0, 0, 0, 0, 0, 1 };
    // Triple<double> lightsource{ 0, 0, 1 }; // pointed directly at the shape
    Triple<double> lightsource{ 0, -1, 1 }; // above the shape and to the left, pointed at it
    // Triple<double> lightsource{ 0, 0, 1 }; // above the shape and to the left, pointed at it
    Triple<double> shapeCenter{ 0, 0, 80 };
    Screen screen{ 80, 30, 40 };
    RendererConsole renderer{ camera, lightsource, screen, shapeCenter };

    std::vector<std::unique_ptr<Shape<double, double>>> shapes;
    shapes.push_back(std::make_unique<Cube<double, double>>(30, shapeCenter));
    shapes.push_back(std::make_unique<Torus<double, double>>(7, 15, shapeCenter));
    shapes.push_back(std::make_unique<Pyramid<double, double>>(20, 30, 20, shapeCenter));
    int currentShapeIndex = 0;

    double xAngle = 0;
    double yAngle = 0;
    double zAngle = 0;
    rlutil::hidecursor();
    rlutil::cls();
    for (bool done = false; !done;)
    {
        // update render loop
        if (!renderer.isPaused())
        {
            shapes[currentShapeIndex]->update(xAngle, yAngle, zAngle);
            xAngle += X_ANGLE_INCREMENT;
            xAngle = (xAngle > TAU) ? xAngle - TAU : xAngle;
            yAngle += Y_ANGLE_INCREMENT;
            yAngle = (yAngle > TAU) ? yAngle - TAU : yAngle;
            zAngle += Z_ANGLE_INCREMENT;
            zAngle = (zAngle > TAU) ? zAngle - TAU : zAngle;

            renderer.render((*shapes[currentShapeIndex]));
            std::cout.flush(); // force console changes to render

            // sleep for a bit cuz our update/render loop is giga fast
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
            else if (key == rlutil::KEY_LEFT)
            {
                currentShapeIndex = (currentShapeIndex - 1 + shapes.size()) % shapes.size();
                xAngle = 0.0;
                yAngle = 0.0;
                zAngle = 0.0;
            }
            else if (key == rlutil::KEY_RIGHT)
            {
                currentShapeIndex = (currentShapeIndex + 1) % shapes.size();
                xAngle = 0.0;
                yAngle = 0.0;
                zAngle = 0.0;
            }
        }
    }
    // cleanup to not disturb potential console users
    rlutil::showcursor();
    rlutil::cls();

    return 0;
}