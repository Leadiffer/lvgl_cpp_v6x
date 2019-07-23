/**
 * @file lv_indev.h
 *
 */

/*********************
 *      INCLUDES
 *********************/

#ifndef LV_INPUTDEVICE_CLASS
    #include "../LVHal/LVHalInputDirver.h"
#else

//#ifndef LVINDEV_H
//#define LVINDEV_H

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

//NOTE: there is only part of LVInputDevice class definition
//#include <lv_core/lv_indev.h>
//#include "../LVMisc/LVTask.h"
//#include "../LVCore/LVObject.h"
//#include "../LVCore/LVGroup.h"
//class LVInputDevice
//{

    /**
     * Initialize the display input device subsystem
     */
    static void init(void)
    {
        lv_indev_init();
    }

    /**
     * Called periodically to read the input devices
     * @param task pointer to the task itself
     */
    static void readTask(LVTask * task)
    {
        lv_indev_read_task(task);
    }

    /**
     * Get the currently processed input device. Can be used in action functions too.
     * @return pointer to the currently processed input device or NULL if no input device processing
     * right now
     */
    static LVInputDevice * getActived(void)
    {
        return (LVInputDevice*)lv_indev_get_act();
    }

    /**
     * Get the type of an input device
     * @param indev pointer to an input device
     * @return the type of the input device from `lv_hal_indev_type_t` (`LV_INDEV_TYPE_...`)
     */
    IndevType getType()
    {
        return (IndevType)lv_indev_get_type(this);
    }

    /**
     * Reset one or all input devices
     * @param indev pointer to an input device to reset or NULL to reset all of them
     */
    static void reset(LVInputDevice * indev)
    {
        lv_indev_reset(indev);
    }
    void reset()
    {
        lv_indev_reset(this);
    }

    /**
     * Reset the long press state of an input device
     * @param indev_proc pointer to an input device
     */
    void resetLongPress()
    {
        lv_indev_reset_long_press(this);
    }

    /**
     * Enable or disable an input devices
     * @param indev pointer to an input device
     * @param en true: enable; false: disable
     */
    void setEnable(bool en = true)
    {
        lv_indev_enable(this,en);
    }

    /**
     * Set a cursor for a pointer input device (for LV_INPUT_TYPE_POINTER and LV_INPUT_TYPE_BUTTON)
     * @param indev pointer to an input device
     * @param cur_obj pointer to an object to be used as cursor
     */
    void setCursor(LVObject * cur_obj)
    {
        lv_indev_set_cursor(this,cur_obj);
    }

    #if LV_USE_GROUP
    /**
     * Set a destination group for a keypad input device (for LV_INDEV_TYPE_KEYPAD)
     * @param indev pointer to an input device
     * @param group point to a group
     */
    void setGroup(LVGroup * group)
    {
        lv_indev_set_group(this,group);
    }
    #endif

    /**
     * Set the an array of points for LV_INDEV_TYPE_BUTTON.
     * These points will be assigned to the buttons to press a specific point on the screen
     * @param indev pointer to an input device
     * @param group point to a group
     */
    void setButtonPoints(const LVPoint * points)
    {
        lv_indev_set_button_points(this,points);
    }

    /**
     * Get the last point of an input device (for LV_INDEV_TYPE_POINTER and LV_INDEV_TYPE_BUTTON)
     * @param indev pointer to an input device
     * @param point pointer to a point to store the result
     */
    LVPoint getPoint()
    {
        LVPoint point;
        lv_indev_get_point(this,&point);
        return point;
    }

    /**
     * Get the last pressed key of an input device (for LV_INDEV_TYPE_KEYPAD)
     * @param indev pointer to an input device
     * @return the last pressed key (0 on error)
     */
    uint32_t getKey()
    {
        return lv_indev_get_key(this);
    }

    /**
     * Check if there is dragging with an input device or not (for LV_INDEV_TYPE_POINTER and
     * LV_INDEV_TYPE_BUTTON)
     * @param indev pointer to an input device
     * @return true: drag is in progress
     */
    bool isDragging()
    {
        return lv_indev_is_dragging(this);
    }

    /**
     * Get the vector of dragging of an input device (for LV_INDEV_TYPE_POINTER and
     * LV_INDEV_TYPE_BUTTON)
     * @param indev pointer to an input device
     * @param point pointer to a point to store the vector
     */
    LVPoint getVector()
    {
        LVPoint vector;
        lv_indev_get_vect(this,&vector);
        return vector;
    }

    /**
     * Do nothing until the next release
     * @param indev pointer to an input device
     */
    void waitRelease()
    {
        lv_indev_wait_release(this);
    }

    /**
     * Get a pointer to the indev read task to
     * modify its parameters with `lv_task_...` functions.
     * @param indev pointer to an inout device
     * @return pointer to the indev read refresher task. (NULL on error)
     */
    static LVTask * getReadTask(LVDisplay * disp)
    {
        //LVDispaly和LVInputDevice共用任务
        return (LVTask *)lv_indev_get_read_task(disp);
    }

    /**
     * Gets a pointer to the currently active object in indev proc functions.
     * NULL if no object is currently being handled or if groups aren't used.
     * @return pointer to currently active object
     */
    LVObject * getObjectActived(void)
    {
        return (LVObject *)lv_indev_get_obj_act();
    }


};

/**********************
 *      MACROS
 **********************/


//#endif /*LVINDEV_H*/

#endif /* LV_INPUTDEVICE_CLASS */
