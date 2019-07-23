/**
 * @file lv_hal_tick.h
 * Provide access to the system tick with 1 millisecond resolution
 */

#ifndef LVHALTICK_H
#define LVHALTICK_H

/*********************
 *      INCLUDES
 *********************/
#include "lv_hal/lv_hal_tick.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

class LVTick
{
    LVTick() {}
public:
/**
 * You have to call this function periodically
 * @param tick_period the call period of this function in milliseconds
 */
void increase(uint32_t tick_period)
{
    lv_tick_inc(tick_period);
}

/**
 * Get the elapsed milliseconds since start up
 * @return the elapsed milliseconds
 */
uint32_t elapsed(void)
{
    return lv_tick_get();
}

/**
 * Get the elapsed milliseconds since a previous time stamp
 * @param prev_tick a previous time stamp (return value of systick_get() )
 * @return the elapsed milliseconds since 'prev_tick'
 */
uint32_t elapsed(uint32_t prev_tick)
{
    return lv_tick_elaps(prev_tick);
}
};
/**********************
 *      MACROS
 **********************/

#endif /*LVHALTICK_H*/
