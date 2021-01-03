/**
 * @file lv_slider.h
 *
 */

#ifndef LVSLIDER_H
#define LVSLIDER_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_slider.h>

#if LV_USE_SLIDER != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of slider*/
class LVSlider
        : public LVObject
        , public lv_slider_ext_t
{
    LV_OBJECT(LVSlider,lv_slider_create,lv_slider_ext_t)
public:

    /** Built-in styles of slider*/
    enum Styles : lv_slider_style_t
    {
        STYLE_BG    = LV_SLIDER_STYLE_BG,    /** Slider background style. */
        STYLE_INDIC = LV_SLIDER_STYLE_INDIC, /** Slider indicator (filled area) style. */
        STYLE_KNOB  = LV_SLIDER_STYLE_KNOB,  /** Slider knob style. */
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a slider objects
     * @param par pointer to an object, it will be the parent of the new slider
     * @param copy pointer to a slider object, if not NULL then the new object will be copied from it
     * @return pointer to the created slider
     */
    //LVSlider(LVObject * parent, const LVSlider * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a new value on the slider
     * @param slider pointer to a slider object
     * @param value new value
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     */
    void setValue(int16_t value, lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        if(getValue() != value)
            lv_slider_set_value(this, value, anim);
    }

    /**
     * Set minimum and the maximum values of a bar
     * @param slider pointer to the slider object
     * @param min minimum value
     * @param max maximum value
     */
    void setRange(int16_t min, int16_t max)
    {
        lv_slider_set_range(this, min, max);
    }

    /**
     * Set the animation time of the slider
     * @param slider pointer to a bar object
     * @param anim_time the animation time in milliseconds.
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_slider_set_anim_time(this, anim_time);
    }

    /**
     * Set the 'knob in' attribute of a slider
     * @param slider pointer to slider object
     * @param in true: the knob is drawn always in the slider;
     *           false: the knob can be out on the edges
     */
    void setKnobIn(bool in)
    {
        lv_slider_set_knob_in(this,in);
    }

    /**
     * Set a style of a slider
     * @param slider pointer to a slider object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_slider_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the value of a slider
     * @param slider pointer to a slider object
     * @return the value of the slider
     */
    int16_t getValue()
    {
        return lv_slider_get_value(this);
    }

    /**
     * Get the minimum value of a slider
     * @param slider pointer to a slider object
     * @return the minimum value of the slider
     */
    int16_t getMinValue()
    {
        return lv_slider_get_min_value(this);
    }

    /**
     * Get the maximum value of a slider
     * @param slider pointer to a slider object
     * @return the maximum value of the slider
     */
    int16_t getMaxValue()
    {
        return lv_slider_get_max_value(this);
    }

    /**
     * Give the slider is being dragged or not
     * @param slider pointer to a slider object
     * @return true: drag in progress false: not dragged
     */
    bool isDragged()
    {
        return lv_slider_is_dragged(this);
    }

    /**
     * Get the 'knob in' attribute of a slider
     * @param slider pointer to slider object
     * @return true: the knob is drawn always in the slider;
     *         false: the knob can be out on the edges
     */
    bool getKnobIn()
    {
        return lv_slider_get_knob_in(this);
    }

    /**
     * Get a style of a slider
     * @param slider pointer to a slider object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(lv_slider_style_t type)
    {
        return (const LVStyle *)lv_slider_get_style(this,type);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_SLIDER*/

#endif /*LVSLIDER_H*/
