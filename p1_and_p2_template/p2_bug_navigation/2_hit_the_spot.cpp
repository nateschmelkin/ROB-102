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
    // Reset the robot odometry to zero at the beginning of the run.
    robot.resetOdometry();

    // *** Task: Get the goal pose (x, y, theta) from the user *** //

    // *** End student code *** //
    float x, y, theta;
    vector<float> kPs = {1, 1, .7};
    float max_velo = 0.8;

    cout << "Please enter a target pose x (m): ";
    cin >> x;
    cout << endl;

    cout << "Please enter a target pose y (m): ";
    cin >> y;
    cout << endl;

    cout << "Please enter a target pose theta (rad): ";
    cin >> theta;
    cout << endl;

    vector<float> target_pose = {x, y, theta};

    while (true) {
        vector<float> current_pose = robot.readOdometry();
        vector<float> velos = computeDriveToPoseCommand(target_pose, current_pose, kPs, max_velo);
        cout << "current x, y, theta: " << current_pose[0] << ", " << current_pose[1] << ", " << current_pose[2] << "| current velos x, y, omega: " << velos[0] << ", " << velos[1] << ", " << velos[2] << endl;
        // *** Task: Implement hit the spot *** //
        robot.drive(velos[0], velos[1], velos[2]);

        // *** End student code *** //
        
        if (ctrl_c_pressed) break;
    }

    // Stop the robot before exiting.
    robot.stop();
    cout << "Robot Pose| X: " << robot.readOdometry()[0] << " | Y: "  << robot.readOdometry()[1] << " | Theta: "  << robot.readOdometry()[2];

    // *** Task: Print out the robot's final odometry pose *** //
    
    // *** End student code *** //

    return 0;
}
