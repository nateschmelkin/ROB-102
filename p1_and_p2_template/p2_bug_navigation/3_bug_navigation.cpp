#include <cmath>
#include <iostream>
#include <signal.h>

#include <mbot_bridge/robot.h>

#include <mbot_lib/behaviors.h>
#include <mbot_lib/controllers.h>
#include <mbot_lib/utils.h>


using namespace std;

bool ctrl_c_pressed;
void ctrlc(int) {
    ctrl_c_pressed = true;
}


int main() {
    signal(SIGINT, ctrlc);
    signal(SIGTERM, ctrlc);

    // Initialize the robot.
    mbot_bridge::MBot robot;
    // Reset the robot odometry to zero.
    robot.resetOdometry();

    float x, y, theta;
    vector<float> kPs = {.8, .8, .4};
    float max_velo = 0.5;
    float max_velo_wall = 0.4;
    float kp_wall = 0.6;
    float set_point = 0.3;

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

    vector<float> ranges;
    vector<float> thetas;
    vector<float> velos(3, 0);

    while (true) {
        vector<float> current_pose = robot.readOdometry();
        robot.readLidarScan(ranges, thetas);

        if (isGoalAngleObstructed(target_pose, current_pose, ranges, thetas)) {
            cout << "Wall Following\n";
            velos = computeWallFollowerCommand(ranges, thetas, set_point, kp_wall, max_velo_wall);
        } else {
            cout << "Path Finding\n";
            velos = computeDriveToPoseCommand(target_pose, current_pose, kPs, max_velo);
        }
        robot.drive(velos[0], velos[1], velos[2]);
        if(ctrl_c_pressed) break;
    }

    // *** End student code *** //

    // Stop the robot.
    robot.stop();
    cout << "Robot Pose| X: " << robot.readOdometry()[0] << " | Y: "  << robot.readOdometry()[1] << " | Theta: "  << robot.readOdometry()[2];

    // *** Task: Print out the robot's final odometry pose *** //
    
    // *** End student code *** //
}
