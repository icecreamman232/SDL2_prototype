#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#include "Vector2.h"
#include <cmath>
namespace MathHelper
{
    constexpr float PI = 3.141;
    constexpr float RadToDeg = (180.0/PI);
    constexpr float DegToRad = (PI/180.0);

    
    /**
     * \brief Find angles between 2 vector
     * \param a Vector a (start point)
     * \param b Vector b (end point)
     * \return Angles in degree
     */
    static float AngleBetween(Vector2 a, Vector2 b)
    {
        return atan2(b.y - a.y, b.x - a.x) * RadToDeg;
    }

    /**
     * \brief Remaps a value x in internal [A,B] to the proportional value in interval [C,D] 
     * \param x The value to remap
     * \param A The minimum bound of interval [A,B]
     * \param B The maximum bound of interval [A,B]
     * \param C The minimum bound of interval [C,D]
     * \param D The maximum bound of interval [C,D]
     */
    static float Remap(float x, float A, float B, float C, float D)
    {
        return (C + (x-A)/(B-A) * (D-C));
    }

    /**
     * \brief Return percent of value x
     * \param x Value to get percentage
     * \param percent Percentage
     */
    static float PercentOf(float x, float percent)
    {
        return (x / 100.0 * percent);
    }
    
}






#endif
