/**
 * File: drive_star.cpp
 *
 * Code to drive in a five-pointed star shape without turning. 
 */

#include <iostream>
#include <cmath>

#include <signal.h>

#include <mbot_bridge/robot.h>

#include <mbot_lib/utils.h>

using namespace std;

bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}


int main(int argc, const char *argv[])
{
    signal(SIGINT, ctrlc);
    signal(SIGTERM, ctrlc);

    float velo = .45;
    // Initialize the robot.
    mbot_bridge::MBot robot;

    for (size_t i = 0; i < 5; i++)
    {
        float angle = (M_PI * ((4.0 * i)/ 5.0));
        cout << angle * (180.0 / M_PI) << "\n";
        robot.drive(rayConversionCartesian(velo, angle)[1], rayConversionCartesian(velo, angle)[0], M_PI / 36);
        sleepFor(1.75);
        robot.stop();
        sleepFor(.5);
    }

    // *** End student code *** //

    // Stop the robot.
    robot.stop();
    return 0;
}