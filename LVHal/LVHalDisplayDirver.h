/**
 * @file lv_hal_disp.h
 *
 * @description Display Driver HAL interface header file
 *
 */

#ifndef LVHALDISP_H
#define LVHALDISP_H

/*********************
 *      INCLUDES
 *********************/
#include "../LVMisc/LVColor.h"
#include "../LVMisc/LVArea.h"
#include "../LVMisc/LVLinkList.h"
#include "../LVMisc/LVTask.h"
#include "../LVCore/LVObject.h"
#include "../LVCore/LVDispaly.h"
#include <lv_core/lv_disp.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/


class LVDispalyBuffer;
class LVDisplayDriver;
class LVDisplay;
class LVObject;

/**
 * Structure for holding display buffer information.
 */
class LVDispalyBuffer
        : public lv_disp_buf_t
{
public:
    LVDispalyBuffer(void * buf1, void * buf2, uint32_t size_in_px_cnt)
    {
        init(buf1, buf2, size_in_px_cnt);
    }

    /**
     * Initialize a display buffer
     * @param disp_buf pointer `lv_disp_buf_t` variable to initialize
     * @param buf1 A buffer to be used by LittlevGL to draw the image.
     *             Always has to specified and can't be NULL.
     *             Can be an array allocated by the user. E.g. `static lv_color_t disp_buf1[1024 * 10]`
     *             Or a memory address e.g. in external SRAM
     * @param buf2 Optionally specify a second buffer to make image rendering and image flushing
     *             (sending to the display) parallel.
     *             In the `disp_drv->flush` you should use DMA or similar hardware to send
     *             the image to the display in the background.
     *             It lets LittlevGL to render next frame into the other buffer while previous is being
     * sent. Set to `NULL` if unused.
     * @param size_in_px_cnt size of the `buf1` and `buf2` in pixel count.
     */
    void init(void * buf1, void * buf2, uint32_t size_in_px_cnt)
    {
        lv_disp_buf_init(this, buf1, buf2, size_in_px_cnt);
    }
};


/**
 * Display Driver structure to be registered by HAL
 */
class LVDisplayDriver : public lv_disp_drv_t
{
    LV_MEMORY
public:
    LVDisplayDriver()
    {
        init();
    }

    /**
     * Initialize a display driver with default values.
     * It is used to surly have known values in the fields ant not memory junk.
     * After it you can set the fields.
     * @param driver pointer to driver variable to initialize
     */
    void init()
    {
        lv_disp_drv_init(this);
    }

    /**
     * Register an initialized display driver.
     * Automatically set the first display as active.
     * @param driver pointer to an initialized 'lv_disp_drv_t' variable (can be local variable)
     * @return pointer to the new display or NULL on error
     */
    LVDisplay * register_()
    {
        return (LVDisplay *)lv_disp_drv_register(this);
    }

    /**
     * Update the driver in run time.
     * @param disp pointer to a display. (return value of `lv_disp_drv_register`)
     * @param new_drv pointer to the new driver
     */
    void update(LVDisplay * disp)
    {
        lv_disp_drv_update((lv_disp_t *)disp,this);
    }

    /**
     * Call in the display driver's `flush_cb` function when the flushing is finished
     * @param disp_drv pointer to display driver in `flush_cb` where this function is called
     */
    void flushReady()
    {
        lv_disp_flush_ready(this);
    }
};

#endif /*LVDISPLAY_H*/

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**********************
 *      MACROS
 **********************/


