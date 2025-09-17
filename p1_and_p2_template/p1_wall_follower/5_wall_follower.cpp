/**
 * File: wall_follower.cpp
 *
 * Controls robot to follow a wall. 
 */

#include <iostream>
#include <cmath>

#include <signal.h>

#include <mbot_bridge/robot.h>

#include <mbot_lib/behaviors.h>
#include <mbot_lib/controllers.h>
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

    // Initialize the robot.
    mbot_bridge::MBot robot;
    // Create empty vectors to store the scan data.
    std::vector<float> ranges;
    std::vector<float> thetas;

    while (true) {

        // *** Task: Implement wall following *** //

        robot.readLidarScan(ranges, thetas);

        vector<float> velo_command = computeWallFollowerCommand(ranges, thetas, 0.2, 1, 0.6);

        robot.drive(velo_command[0], velo_command[1], velo_command[2]);
        // *** End student code *** //

        if (ctrl_c_pressed) break;
    }

    // Stop the robot.
    robot.stop();
    return 0;
}
