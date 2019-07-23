/**
 * @file LVDisplayer.h
 *
 */



/*********************
 *      INCLUDES
 *********************/

#ifndef LV_DISPLAY_CLASS
    #include "../LVHal/LVHalDisplayDirver.h"
#else

//#ifndef LVDISPLAY_H
//#define LVDISPLAY_H

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

//NOTE:  * NOTE: there is only part of LVDisplay class definition
//#include <lv_core/lv_disp.h>
//class LVObject;
//class LVTask;
//class LVDisplay
//{

    /**
     * Return with a pointer to the active screen
     * @param disp pointer to display which active screen should be get. (NULL to use the default
     * screen)
     * @return pointer to the active screen object (loaded by 'lv_scr_load()')
     */
    //获取当前活动的屏幕上的活动对象
    static LVObject * getScreenActived(LVDisplay * disp_p)
    {
        return (LVObject *)lv_disp_get_scr_act(disp_p);
    }

    //获取显示器上的活动对象
    LVObject * getScreenActived()
    {
        return (LVObject *)lv_disp_get_scr_act(this);
    }

    /**
     * Make a screen active
     * @param scr pointer to a screen
     */
    static void loadScreen(LVObject * scr)//?????????????
    {
        lv_disp_load_scr(scr);
    }

    /**
     * Return with the top layer. (Same on every screen and it is above the normal screen layer)
     * @param disp pointer to display which top layer should be get. (NULL to use the default screen)
     * @return pointer to the top layer object  (transparent screen sized lv_obj)
     */
    static LVObject * getLayerTop(LVDisplay * disp_p)
    {
        return (LVObject *)lv_disp_get_layer_top(disp_p);
    }
    LVObject * getLayerTop()
    {
        return (LVObject *)lv_disp_get_layer_top(this);
    }

    /**
     * Return with the sys. layer. (Same on every screen and it is above the normal screen and the top
     * layer)
     * @param disp pointer to display which sys. layer  should be get. (NULL to use the default screen)
     * @return pointer to the sys layer object  (transparent screen sized lv_obj)
     */
    static LVObject * getLayerSys(LVDisplay * disp_p)
    {
        return (LVObject *)lv_disp_get_layer_sys(disp_p);
    }
    LVObject * getLayerSys()
    {
        return (LVObject *)lv_disp_get_layer_sys(this);
    }

    /**
     * Assign a screen to a display.
     * @param disp pointer to a display where to assign the screen
     * @param scr pointer to a screen object to assign
     */
    void assignScreen(LVObject * scr)
    {
        lv_disp_assign_screen(this,scr);
    }

    /**
     * Get a pointer to the screen refresher task to
     * modify its parameters with `lv_task_...` functions.
     * @param disp pointer to a display
     * @return pointer to the display refresher task. (NULL on error)
     */
    static LVTask * getRefreshTask(LVDisplay * disp_p)
    {
        return (LVTask *)lv_disp_get_refr_task(disp_p);
    }
    LVTask * getRefreshTask()
    {
        return (LVTask *)lv_disp_get_refr_task(this);
    }

    /**
     * Get elapsed time since last user activity on a display (e.g. click)
     * @param disp pointer to an display (NULL to get the overall smallest inactivity)
     * @return elapsed ticks (milliseconds) since the last activity
     */
    static uint32_t getInactiveTime(LVDisplay * disp_p)
    {
        return lv_disp_get_inactive_time(disp_p);
    }
    uint32_t getInactiveTime()
    {
        return lv_disp_get_inactive_time(this);
    }

    /**
     * Manually trigger an activity on a display
     * @param disp pointer to an display (NULL to use the default display)
     */
    static void triggerActivity(LVDisplay * disp_p)
    {
        lv_disp_trig_activity(disp_p);
    }
    void triggerActivity()
    {
        lv_disp_trig_activity(this);
    }
};
//#endif /*LVDISPLAY_H*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_DISPLAY_CLASS*/
