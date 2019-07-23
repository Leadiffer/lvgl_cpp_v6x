/**
 * @file lv_hal_indev.h
 *
 * @description Input Device HAL interface layer header file
 *
 */

#ifndef LVHALINDEV_H
#define LVHALINDEV_H

/*********************
 *      INCLUDES
 *********************/

#include "../LVMisc/LVArea.h"
#include "../LVMisc/LVTask.h"
#include <lv_core/lv_indev.h>
#include "../LVCore/LVObject.h"
#include "../LVCore/LVGroup.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVInputDeviceData;
class LVInputDeviceDriver;
class LVInputDeviceProc;
class LVInputDevice;


/*States for input devices*/
enum IndevState : lv_indev_state_t
{
    INDEV_STATE_REL = LV_INDEV_STATE_REL,
    INDEV_STATE_PR  = LV_INDEV_STATE_PR
};

/*Possible input device types*/
enum IndevType : lv_indev_type_t
{
    INDEV_TYPE_NONE     = LV_INDEV_TYPE_NONE,    /*Show uninitialized state*/
    INDEV_TYPE_POINTER  = LV_INDEV_TYPE_POINTER, /*Touch pad, mouse, external button*/
    INDEV_TYPE_KEYPAD   = LV_INDEV_TYPE_KEYPAD,  /*Keypad or keyboard*/
    INDEV_TYPE_BUTTON   = LV_INDEV_TYPE_BUTTON,  /*External (hardware button) which is assinged
                                                   to a specific point of thescreen*/
    INDEV_TYPE_ENCODER  = LV_INDEV_TYPE_ENCODER, /*Encoder with only Left, Right turn and a Button*/
};

/*Data type when an input device is read */
class LVInputDeviceData : public lv_indev_data_t
{
public:

    //NOTE: 尝试改变内部数据成员的数据类型
//    //same as lv_indev_data_t
//    //but member`s type has change
//    struct Private
//    {
//        LVPoint point; /**< For LV_INDEV_TYPE_POINTER the currently pressed point*/
//        uint32_t key;     /**< For LV_INDEV_TYPE_KEYPAD the currently pressed key*/
//        uint32_t btn_id;  /**< For LV_INDEV_TYPE_BUTTON the currently pressed button*/
//        int16_t enc_diff; /**< For LV_INDEV_TYPE_ENCODER number of steps since the previous read*/

//        IndevState state; /**< LV_INDEV_STATE_REL or LV_INDEV_STATE_PR*/
//    };
//    Private * operator->(){ return (Private*)this; }


    LVInputDeviceData () {}

};

/*Initialized by the user and registered by 'lv_indev_add()'*/
class LVInputDeviceDriver : public lv_indev_drv_t
{
    LV_MEMORY

public:
    LVInputDeviceDriver() { init(); }

    /**
     * Initialize an input device driver with default values.
     * It is used to surly have known values in the fields ant not memory junk.
     * After it you can set the fields.
     * @param driver pointer to driver variable to initialize
     */
    void init()
    {
        lv_indev_drv_init(this);
    }

    /**
     * Register an initialized input device driver.
     * @param driver pointer to an initialized 'lv_indev_drv_t' variable (can be local variable)
     * @return pointer to the new input device or NULL on error
     */
    LVInputDevice * registerDriver()
    {
        return (LVInputDevice *)lv_indev_drv_register(this);
    }

    /**
     * Update the driver in run time.
     * @param indev pointer to a input device. (return value of `lv_indev_drv_register`)
     * @param new_drv pointer to the new driver
     */
    void update(LVInputDevice * indev)
    {
        lv_indev_drv_update((lv_indev_t *)indev, this);
    }

};

/*Run time data of input devices*/
class LVInputDeviceProc : public lv_indev_proc_t
{
public:
    LVInputDeviceProc(){}
};


/*The main input device descriptor with driver, runtime data ('proc') and some additional
 * information*/

/**
 * @brief 输入设备
 * 用户无法实例化,只能由输入设备驱动注册时得到
 * NOTE: there is only part of LVInputDevice class definition
 */
class LVInputDevice : public lv_indev_t
{
    LVInputDevice() {}
public:

    /**
     * Get the next input device.
     * @param indev pointer to the current input device. NULL to initialize.
     * @return the next input devise or NULL if no more. Give the first input device when the parameter
     * is NULL
     */
    LVInputDevice * getNext()
    {
        return (LVInputDevice *)lv_indev_get_next(this);
    }

    /**
     * Read data from an input device.
     * @param indev pointer to an input device
     * @param data input device will write its data here
     * @return false: no more data; true: there more data to read (buffered)
     */
    bool read(LVInputDeviceData * data)
    {
        return lv_indev_read(this, data);
    }

#define LV_INPUTDEVICE_CLASS
#include "../LVCore/LVInputDevice.h"
#undef LV_INPUTDEVICE_CLASS

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**********************
 *      MACROS
 **********************/


#endif
