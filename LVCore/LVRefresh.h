/**
 * @file lv_refr.h
 *
 */

#ifndef LVREFR_H
#define LVREFR_H

/*********************
 *      INCLUDES
 *********************/
#include "LVObject.h"
#include <stdbool.h>
#include <lv_core/lv_refr.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

class LVDisplay;
class LVTask;

class LVRefresh
{
    LVRefresh() {}
public:

    /**
     * Initialize the screen refresh subsystem
     */
    static void init(void)
    {
        lv_refr_init();
    }

    /**
     * Redraw the invalidated areas now.
     * Normally the redrawing is periodically executed in `lv_task_handler` but a long blocking process
     * can prevent the call of `lv_task_handler`. In this case if the the GUI is updated in the process
     * (e.g. progress bar) this function can be called when the screen should be updated.
     */
    static void refreshNow(void)
    {
        lv_refr_now(nullptr);
    }

    /**
     * Invalidate an area on display to redraw it
     * @param area_p pointer to area which should be invalidated (NULL: delete the invalidated areas)
     * @param disp pointer to display where the area should be invalidated (NULL can be used if there is
     * only one display)
     */
    static void InvalidateArea(lv_disp_t * disp, const lv_area_t * area_p)
    {
        lv_inv_area(disp,area_p);
    }

    /**
     * Get the display which is being refreshed
     * @return the display being refreshed
     */
    static LVDisplay * getDispalyRefreshing(void)
    {
        return (LVDisplay*)lv_refr_get_disp_refreshing();
    }

    /**
     * Called periodically to handle the refreshing
     * @param task pointer to the task itself
     */
    static void setDisplayRefreshTask(LVTask * task)
    {
        lv_disp_refr_task(task);
    }

};


/**********************
 *   STATIC FUNCTIONS
 **********************/


#endif /*LVREFR_H*/
