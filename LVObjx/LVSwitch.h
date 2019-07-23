/**
 * @file lv_sw.h
 *
 */

#ifndef LVSWITCH_H
#define LVSWITCH_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_sw.h>

#if LV_USE_SW != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of switch*/

class LVSwitch
        : public LVObject
        , public LVFakeMemHeader<lv_sw_ext_t>
        , public lv_sw_ext_t
{
    LV_OBJECT(LVSwitch,lv_sw_create,lv_sw_ext_t)
public:
    /**
     * Switch styles.
     */
    enum Styles : lv_sw_style_t
    {
        STYLE_BG        = LV_SW_STYLE_BG, /**< Switch background. */
        STYLE_INDIC     = LV_SW_STYLE_INDIC, /**< Switch fill area. */
        STYLE_KNOB_OFF  = LV_SW_STYLE_KNOB_OFF, /**< Switch knob (when off). */
        STYLE_KNOB_ON   = LV_SW_STYLE_KNOB_ON, /**< Switch knob (when on). */
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a switch objects
     * @param par pointer to an object, it will be the parent of the new switch
     * @param copy pointer to a switch object, if not NULL then the new object will be copied from it
     * @return pointer to the created switch
     */
    //LVSwitch(LVObject * par, const LVSwitch * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Turn ON the switch
     * @param sw pointer to a switch object
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     */
    void on(bool anim = true)
    {
        lv_sw_on(this,anim);
    }

    /**
     * Turn OFF the switch
     * @param sw pointer to a switch object
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     */
    void off(bool anim)
    {
        lv_sw_off(this,anim);
    }

    /**
     * Toggle the position of the switch
     * @param sw pointer to a switch object
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     * @return resulting state of the switch.
     */
    bool toggle(lv_anim_enable_t anim)
    {
        return lv_sw_toggle(this,anim);
    }

    /**
     * Set a style of a switch
     * @param sw pointer to a switch object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(Styles type, const LVStyle * style)
    {
        lv_sw_set_style(this,type,style);
    }

    /**
     * Set the animation time of the switch
     * @param sw pointer to a  switch object
     * @param anim_time animation time
     * @return style pointer to a style
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_sw_set_anim_time(this,anim_time);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the state of a switch
     * @param sw pointer to a switch object
     * @return false: OFF; true: ON
     */
    bool getState()
    {
        return lv_sw_get_state(this);
    }

    /**
     * Get a style of a switch
     * @param sw pointer to a  switch object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_sw_get_style(this,type);
    }

    /**
     * Get the animation time of the switch
     * @param sw pointer to a  switch object
     * @return style pointer to a style
     */
    uint16_t getAnimTime()
    {
        return lv_sw_get_anim_time(this);
    }

    /**********************
     *      MACROS
     **********************/

};

#endif /*LV_USE_SW*/

#endif /*LVSWITCH_H*/
