/**
 * @file math_base.h
 *
 */

#ifndef LVMATH_H
#define LVMATH_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_misc/lv_math.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVMath
{
public:
    LVMath() {}


    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Return with sinus of an angle
     * @param angle
     * @return sinus of 'angle'. sin(-90) = -1, sin(90) = 1
     */
    float sin(int16_t angle)
    {
        return float(lv_trigo_sin(angle))/32767.0f;
    }

    /**
     * Calculate a value of a Cubic Bezier function.
     * @param t time in range of [0..LV_BEZIER_VAL_MAX]
     * @param u0 start values in range of [0..LV_BEZIER_VAL_MAX]
     * @param u1 control value 1 values in range of [0..LV_BEZIER_VAL_MAX]
     * @param u2 control value 2 in range of [0..LV_BEZIER_VAL_MAX]
     * @param u3 end values in range of [0..LV_BEZIER_VAL_MAX]
     * @return the value calculated from the given parameters in range of [0..LV_BEZIER_VAL_MAX]
     */
    int32_t bezier3(uint32_t t, int32_t u0, int32_t u1, int32_t u2, int32_t u3)
    {
        return lv_bezier3( t,  u0,  u1,  u2,  u3);
    }


    //TODO:增加数学功能


};

/**********************
 *      MACROS
 **********************/


#endif
