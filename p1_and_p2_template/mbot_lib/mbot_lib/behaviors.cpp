/**
 * File: behaviors.cpp
 * 
 * Sources for high level functions that determine how the robot should move.
 */

#include <mbot_lib/behaviors.h>

using namespace std;


std::vector<float> computeWallFollowerCommand(const std::vector<float>& ranges, const std::vector<float>& thetas, float setpoint, float kP, float max_velo)
{
    float min_idx = findMinNonzeroDist(ranges);
    float dist_to_wall = ranges[min_idx];
    float angle_to_wall = thetas[min_idx];

    float velo = max_velo - pControl(dist_to_wall, setpoint, kP);

    if (fabs(velo) > max_velo) {
        velo = max_velo;
        if (max_velo < 0) {
            max_velo *= -1;
        }
    }
    vector<float> cartesian = rayConversionCartesian(velo, angle_to_wall);

    vector<float> velo_vector = crossProduct(cartesian, {0, 0, 1});
    
    return velo_vector;

    // *** End student code *** //
}

std::vector<float> computeDriveToPoseCommand(const std::vector<float>& goal, const std::vector<float>& pose)
{   
    // *** Task: Implement this function according to the header file *** //

    return std::vector<float>();

    // *** End student code *** //
}

bool isGoalAngleObstructed(const std::vector<float>& goal, const std::vector<float>& pose,
                           const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //

    return false;

    // *** End student code *** //
}