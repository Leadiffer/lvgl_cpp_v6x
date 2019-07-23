/**
 * @file lv_led.h
 *
 */

#ifndef LVLED_H
#define LVLED_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_objx/lv_led.h>

#if LV_USE_LED != 0

#include "../LVCore/LVObject.h"


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVLed
        : public LVObject //!< 功能基类,第一个继承
        , public LVFakeMemHeader<lv_led_ext_t> //!< 假的内存块信息,模拟lvgl的内存布局
        , public lv_led_ext_t //!< LVObject的扩展属性

{
    LV_OBJECT(LVLed,lv_led_create,lv_led_ext_t)

public:

    /*Styles*/
    enum Styles: lv_led_style_t
    {
        STYLE_MAIN = LV_LED_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a led objects
     * @param par pointer to an object, it will be the parent of the new led
     * @param copy pointer to a led object, if not NULL then the new object will be copied from it
     * @return pointer to the created led
     */
    //LVLed(LVObject * parent, const LVLed * copy = nullptr);

    /**
     * Set the brightness of a LED object
     * @param led pointer to a LED object
     * @param bright 0 (max. dark) ... 255 (max. light)
     */
    void setBrightness(uint8_t bright)
    {
        lv_led_set_bright(this,bright);
    }

    /**
     * Light on a LED
     * @param led pointer to a LED object
     */
    void on()
    {
        lv_led_on(this);
    }

    /**
     * Light off a LED
     * @param led pointer to a LED object
     */
    void off()
    {
        lv_led_off(this);
    }

    /**
     * Toggle the state of a LED
     * @param led pointer to a LED object
     */
    void toggle()
    {
        lv_led_toggle(this);
    }

    /**
     * Set the style of a led
     * @param led pointer to a led object
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_led_set_style(this, type, style);
    }

    /**
     * Get the brightness of a LEd object
     * @param led pointer to LED object
     * @return bright 0 (max. dark) ... 255 (max. light)
     */
    uint8_t getBrightness()
    {
        return lv_led_get_bright(this);
    }

    /**
     * Get the style of an led object
     * @param led pointer to an led object
     * @return pointer to the led's style
     */
    const LVStyle * getStyle(Styles type = STYLE_MAIN) const
    {
        return (const LVStyle*)lv_led_get_style(this,type);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_LED*/

#endif /*LV_LED_H*/
