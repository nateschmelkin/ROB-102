/**
 * File: utils.cpp
 * 
 * Sources for functions for handling common tasks like working with geometry and interpreting lidar data.
 */

#include <mbot_lib/utils.h>
#include <cmath>

using namespace std;


std::vector<float> rayConversionCartesian(float dist, float angle) 
{
    float x = dist * cos(angle);
    float y = dist * sin(angle);

    return {x, y};

    // *** End student code *** //
}

std::vector<float> rayConversionVector(float angle) 
{
    // *** Task: Implement this function according to the header file *** //

    float x = cos(angle);
    float y = sin(angle);
    float z = 0.0;

    return {x, y, z};

    // *** End student code *** //
}

int findMinDist(const std::vector<float>& ranges)
{
    float lowest_num = 10000;
    float lowest_index = 0;
    for (int i = 0; i < ranges.size(); i++)
    {
        if (ranges[i] < lowest_num) {
            lowest_num = ranges[i];
            lowest_index = i;
        }
    }
    
    return lowest_index;

    // *** End student code *** //
}

int findMinNonzeroDist(const std::vector<float>& ranges)
{
    float lowest_num = 10000;
    float lowest_index = 0;
    for (int i = 0; i < ranges.size(); i++)
    {
        if (ranges[i] < lowest_num && ranges[i] != 0) {
            lowest_num = ranges[i];
            lowest_index = i;
        }
    }
    
    return lowest_index;
    
    // *** End student code *** //
}

std::vector<float> vectorAdd(const std::vector<float>& v1, const std::vector<float>& v2) 
{
    return {v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]};

    // *** End student code *** //
}

std::vector<float> crossProduct(const std::vector<float>& v1, const std::vector<float>& v2) 
{
    return {v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0]};

    // *** End student code *** //
}

void transformVector2D(std::vector<float>& xy, float theta) 
{
    //Apply the 2D rotation matrix

    float x_prime = xy[0] * cos(theta) - xy[1] * sin(theta);
    float y_prime = xy[0] * sin(theta) - xy[1] * cos(theta);

    xy = {x_prime, y_prime};
    // *** End student code *** //
}
