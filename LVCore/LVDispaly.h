/**
 * @file LVDisplayer.h
 *
 */

#ifndef LVDISPLAY_H
#define LVDISPLAY_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_core/lv_disp.h>
#include "../LVHal/LVHalDisplayDirver.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVObject;
class LVTask;

/**********************
 * GLOBAL PROTOTYPES
 **********************/



/**
 * Display structure.
 * ::lv_disp_drv_t is the first member of the structure.
 *
 * NOTE: 类对象无法由用户实例化,只能注册驱动时获得
 * NOTE: there is only part of LVDisplay class definition
 */
class LVDisplay
        : public lv_disp_t
{

    LVDisplay() {}

public:

    /**
     * Remove a display
     * @param disp pointer to display
     */
    void remove()
    {
        lv_disp_remove(this);
    }

    /**
     * Set a default screen. The new screens will be created on it by default.
     * @param disp pointer to a display
     */
    void setDefault()
    {
        lv_disp_set_default(this);
    }

    /**
     * Get the default display
     * @return pointer to the default display
     */
    static LVDisplay * getDefault(void)
    {
        return (LVDisplay *)lv_disp_get_default();
    }

    /**
     * Get the horizontal resolution of a display
     * @param disp pointer to a display (NULL to use the default display)
     * @return the horizontal resolution of the display
     */
    LVCoord getHorizontalResolution()
    {
        return lv_disp_get_hor_res(this);
    }

    /**
     * Get the vertical resolution of a display
     * @param disp pointer to a display (NULL to use the default display)
     * @return the vertical resolution of the display
     */
    LVCoord getVerticalResolution()
    {
        return lv_disp_get_ver_res(this);
    }

    /**
     * Get if anti-aliasing is enabled for a display or not
     * @param disp pointer to a display (NULL to use the default display)
     * @return true: anti-aliasing is enabled; false: disabled
     */
    bool getAntialiasing()
    {
        return lv_disp_get_antialiasing(this);
    }

    /**
     * Get the next display.
     * @param disp pointer to the current display. NULL to initialize.
     * @return the next display or NULL if no more. Give the first display when the parameter is NULL
     */
    LVDisplay * getNext()
    {
        return (LVDisplay*)lv_disp_get_next(this);
    }

    /**
     * Get the internal buffer of a display
     * @param disp pointer to a display
     * @return pointer to the internal buffers
     */
    LVDispalyBuffer * getBuffer()
    {
        return (LVDispalyBuffer *)lv_disp_get_buf(this);
    }

    /**
     * Get the number of areas in the buffer
     * @return number of invalid areas
     */
    uint16_t getInvalidBufferSize()
    {
        return lv_disp_get_inv_buf_size(this);
    }

    /**
     * Pop (delete) the last 'num' invalidated areas from the buffer
     * @param num number of areas to delete
     */
    void popFromInvalidBuffer(uint16_t num)
    {
        lv_disp_pop_from_inv_buf(this,num);
    }

    /**
     * Check the driver configuration if it's double buffered (both `buf1` and `buf2` are set)
     * @param disp pointer to to display to check
     * @return true: double buffered; false: not double buffered
     */
    bool isDoubleBuffer()
    {
        return lv_disp_is_double_buf(this);
    }

    /**
     * Check the driver configuration if it's TRUE double buffered (both `buf1` and `buf2` are set and
     * `size` is screen sized)
     * @param disp pointer to to display to check
     * @return true: double buffered; false: not double buffered
     */
    bool isTrueDoubleBuffer()
    {
        return lv_disp_is_true_double_buf(this);
    }
    /**
     * Return with a pointer to the active screen
     * @param disp pointer to display which active screen should be get. (NULL to use the default
     * screen)
     * @return pointer to the active screen object (loaded by 'lv_scr_load()')
     */
    //获取当前活动的屏幕上的活动对象
    static LVObject * getScreenActived(LVDisplay * disp_p)
    {
        return lvobject_cast<LVObject*>(lv_disp_get_scr_act(disp_p),true);
    }

    //获取显示器上的活动对象
    LVObject * getScreenActived()
    {
        return lvobject_cast<LVObject*>(lv_disp_get_scr_act(this),true);
    }

    /**
     * Make a screen active
     * @param scr pointer to a screen
     */
    static void loadScreen(LVObject * scr)
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
        return lvobject_cast<LVObject*>(lv_disp_get_layer_top(disp_p),true);
    }
    LVObject * getLayerTop()
    {
        return lvobject_cast<LVObject*>(lv_disp_get_layer_top(this),true);
    }

    /**
     * Return with the sys. layer. (Same on every screen and it is above the normal screen and the top
     * layer)
     * @param disp pointer to display which sys. layer  should be get. (NULL to use the default screen)
     * @return pointer to the sys layer object  (transparent screen sized lv_obj)
     */
    static LVObject * getLayerSys(LVDisplay * disp_p)
    {
        return lvobject_cast<LVObject*>(lv_disp_get_layer_sys(disp_p),true);
    }
    LVObject * getLayerSys()
    {
        return lvobject_cast<LVObject*>(lv_disp_get_layer_sys(this),true);
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

/**********************
 *      MACROS
 **********************/
#endif /*LVDISPLAY_H*/
