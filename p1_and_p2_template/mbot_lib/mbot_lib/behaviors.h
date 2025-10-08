/**
 * File: behaviors.h
 * 
 * Definitions for high level functions that determine how the robot should move.
 */

#ifndef MBOT_LIB_BEHAVIORS_H
#define MBOT_LIB_BEHAVIORS_H

#include <cmath>
#include <vector>

#include <mbot_lib/controllers.h>
#include <mbot_lib/utils.h>

/**
 * Computes a drive command that will make the robot follow a wall. 
 * @param  ranges Vector of ray ranges.
 * @param  thetas Vector of ray angles.
 * @param  setpoint The goal distance from the wall in meters.
 * @param  kP The proportional gain for the controller.
 * @param  max_velo The maximum velocity the robot should drive at in m/s.
 * @return  The drive command as a (vx, vy, wtheta) vector. 
 *
 * NOTE: This function is not unit tested, it is simply meant to help you structure your code.
 */
std::vector<float> computeWallFollowerCommand(const std::vector<float>& ranges, const std::vector<float>& thetas, float setpoint, float kP, float max_velo);

/**
 * Computes a drive command that will make the robot drive towards a goal pose.
 * @param  goal The goal pose of the robot in world frame.
 * @param  pose The current pose of the robot in world frame, according to odometry. 
 * @param  kP The vector of kPs for the x, y and theta
 * @param  max_velo The max velocity of the robot
 * @return  The drive command as a (vx, vy, wtheta) vector. 
 *
 * NOTE: This function is not unit tested, it is simply meant to help you structure your code.
 */
std::vector<float> computeDriveToPoseCommand(const std::vector<float>& goal, const std::vector<float>& pose, const std::vector<float> kP, float max_velo);

/**
 * Checks if the straight line path to a goal pose is obstructed such that another method of navigation must be used.
 * @param  goal The goal pose of the robot in world frame.
 * @param  pose The current pose of the robot in world frame, according to odometry. 
 * @param  ranges Vector of ray ranges.
 * @param  thetas Vector of ray angles.
 * @return  True if the straight line path to the goal pose is obstructed, false otherwise.
 *
 * NOTE: This function is not unit tested, it is simply meant to help you structure your code.
 */
bool isGoalAngleObstructed(const std::vector<float>& goal, const std::vector<float>& pose,
                           const std::vector<float>& ranges, const std::vector<float>& thetas);

#endif  // MBOT_LIB_BEHAVIORS_H