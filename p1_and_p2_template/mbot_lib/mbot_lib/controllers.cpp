/**
 * File: controllers.cpp
 *
 * Sources for feedback controllers.
 */

#include <mbot_lib/controllers.h>
#include <cmath>


float bangBangControl(float current, float setpoint, float scaling, float tolerance)
{
    float error = setpoint - current;
    bool within_tolerance = fabs(error) < tolerance;

    if (within_tolerance) {
        return 0.0;
    } else if (error > 0) {
        return scaling;
    } else  {
        return -scaling;
    }

    // *** End student code *** //
}

float pControl(float current, float setpoint, float kp)
{
    float error = setpoint - current;

    return error * kp;

    // *** End student code *** //
}