/**
 * File: behaviors.cpp
 * 
 * Sources for high level functions that determine how the robot should move.
 */

#include <mbot_lib/behaviors.h>
#include <cmath>

using namespace std;


std::vector<float> computeWallFollowerCommand(const std::vector<float>& ranges, const std::vector<float>& thetas, float setpoint, float kP, float max_velo)
{
    int min_idx = findMinNonzeroDist(ranges);
    if (min_idx < 0 || min_idx >= (int)ranges.size()) {
        return {0.f, 0.f, 0.f}; // no data → stop
    }
    float dist_to_wall = ranges[min_idx];
    float angle_to_wall = thetas[min_idx];

    vector<float> normal = rayConversionCartesian(1.0, angle_to_wall);
    vector<float> tangent = crossProduct(normal, {0, 0, 1});

    float velo_tang = max_velo;
    float velo_normal = -pControl(dist_to_wall, setpoint, kP);

    float vx = velo_tang * tangent[0] + velo_normal * normal[0];
    float vy = velo_tang * tangent[1] + velo_normal * normal[1];

    float hypo = hypot(vx, vy);
    float vmax = fabs(max_velo);
    if (hypo > vmax && hypo > 0) {
        float scale = vmax/hypo;
        vx *= scale; vy *= scale;
    }
    return {vx, vy, 0.0};

    // *** End student code *** //
}

std::vector<float> computeDriveToPoseCommand(const std::vector<float>& goal, const std::vector<float>& pose, const vector<float> kP, float max_velo)
{   
    vector<float> output_velos(3, 0);
    vector<float> errors = {goal[0] - pose[0], goal[1] - pose[1], goal[2] - pose[2]};

    output_velos = {errors[0] * kP[0], errors[1] * kP[1], errors[2] * kP[2]};

    vector<float> output_xy = {output_velos[0], output_velos[1]};
    transformVector2D(output_xy, pose[2]);
    output_velos[0] = output_xy[0];
    output_velos[1] = output_xy[1];

    for (int i = 0; i < 2; i++)
    {
        if (fabs(output_velos[i]) > max_velo) {
            output_velos[i] = copysign(max_velo, output_velos[i]);
        }
    }
    
    // *** Task: Implement this function according to the header file *** //
    return output_velos;

    // *** End student code *** //
}

bool isGoalAngleObstructed(const std::vector<float>& goal, const std::vector<float>& pose,
                           const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // *** Task: Implement this function according to the header file *** //

    float dx = goal[0] - pose[0];
    float dy = goal[1] - pose[1];
    // float dist_to_goal = sqrt(dx * dx + dy * dy);
    float target_angle = normalizeAngle(atan2(dy, dx) - pose[2]);

    int idx = findMinNonzeroDistInSlice(ranges, thetas, target_angle, M_PI/6);
    if (idx == -1) return false;
    
    return ranges[idx] <= .3;
    // *** End student code *** //
}