/**
 * File: utils.cpp
 * 
 * Sources for functions for handling common tasks like working with geometry and interpreting lidar data.
 */

#include <mbot_lib/utils.h>
#include <cmath>

using namespace std;


std::vector<float> rayConversionCartisean(float dist, float angle) 
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
    // *** Task: Implement this function according to the header file *** //

    return std::vector<float>();

    // *** End student code *** //
}

std::vector<float> crossProduct(const std::vector<float>& v1, const std::vector<float>& v2) 
{
    // *** Task: Implement this function according to the header file *** //

    return std::vector<float>();

    // *** End student code *** //
}

void transformVector2D(std::vector<float>& xy, float theta) 
{
    // *** Task: Implement this function according to the header file *** //

    // *** End student code *** //
}
