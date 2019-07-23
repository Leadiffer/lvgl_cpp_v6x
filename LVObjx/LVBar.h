/**
 * @file lv_bar.h
 *
 */

#ifndef LVBAR_H
#define LVBAR_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_bar.h>

#if LV_USE_BAR != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/** Data of bar*/
class LVBar
        : public LVObject
        , public LVFakeMemHeader<lv_bar_ext_t>
        , public lv_bar_ext_t
{

    LV_OBJECT(LVBar,lv_bar_create,lv_bar_ext_t)

public:
    /** Bar styles. */
    enum Styles : lv_bar_style_t
    {
        STYLE_BG = LV_BAR_STYLE_BG, /** Bar background style. */
        STYLE_INDIC = LV_BAR_STYLE_INDIC, /** Bar fill area style. */
    };


    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a bar objects
     * @param par pointer to an object, it will be the parent of the new bar
     * @param copy pointer to a bar object, if not NULL then the new object will be copied from it
     * @return pointer to the created bar
     */
    //LVBar(LVObject * parent, LVObject * copy)

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a new value on the bar
     * @param bar pointer to a bar object
     * @param value new value
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     */
    void setValue(int16_t value, lv_anim_enable_t anim)
    {
        lv_bar_set_value(this,value,anim);
    }

    /**
     * Set minimum and the maximum values of a bar
     * @param bar pointer to the bar object
     * @param min minimum value
     * @param max maximum value
     */
    void setRange(int16_t min, int16_t max)
    {
        lv_bar_set_range(this,min,max);
    }

    /**
     * Make the bar symmetric to zero. The indicator will grow from zero instead of the minimum
     * position.
     * @param bar pointer to a bar object
     * @param en true: enable disable symmetric behavior; false: disable
     */
    void setSymmetric(bool en)
    {
        lv_bar_set_sym(this,en);
    }

    /**
     * Set the animation time of the bar
     * @param bar pointer to a bar object
     * @param anim_time the animation time in milliseconds.
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_bar_set_anim_time(this,anim_time);
    }

    /**
     * Set a style of a bar
     * @param bar pointer to a bar object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_bar_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the value of a bar
     * @param bar pointer to a bar object
     * @return the value of the bar
     */
    int16_t getValue()
    {
        return lv_bar_get_value(this);
    }

    /**
     * Get the minimum value of a bar
     * @param bar pointer to a bar object
     * @return the minimum value of the bar
     */
    int16_t getMinValue()
    {
        return lv_bar_get_min_value(this);
    }

    /**
     * Get the maximum value of a bar
     * @param bar pointer to a bar object
     * @return the maximum value of the bar
     */
    int16_t getMaxValue()
    {
        return lv_bar_get_max_value(this);
    }

    /**
     * Get whether the bar is symmetric or not.
     * @param bar pointer to a bar object
     * @return true: symmetric is enabled; false: disable
     */
    bool getSymmetric()
    {
        return lv_bar_get_sym(this);
    }

    /**
     * Get the animation time of the bar
     * @param bar pointer to a bar object
     * @return the animation time in milliseconds.
     */
    uint16_t getAnimTime()
    {
        return lv_bar_get_anim_time(this);
    }

    /**
     * Get a style of a bar
     * @param bar pointer to a bar object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_bar_get_style(this,type);
    }

};
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_BAR*/

#endif /*LVBAR_H*/
