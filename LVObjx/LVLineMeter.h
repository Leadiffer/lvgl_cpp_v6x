/**
 * @file lv_lmeter.h
 *
 */

#ifndef LVLMETER_H
#define LVLMETER_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_lmeter.h>

#if LV_USE_LMETER != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of line meter*/
class LVLineMeter
        : public LVObject
        , public LVFakeMemHeader<lv_lmeter_ext_t>
        , public lv_lmeter_ext_t
{
    LV_OBJECT(LVLineMeter,lv_lmeter_create,lv_lmeter_ext_t)
public:

    /*Styles*/
    enum Styles : lv_lmeter_style_t
    {
        LV_LMETER_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a line meter objects
     * @param par pointer to an object, it will be the parent of the new line meter
     * @param copy pointer to a line meter object, if not NULL then the new object will be copied from
     * it
     * @return pointer to the created line meter
     */
    //LVLineMeter(LVObject * par, const LVLineMeter * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a new value on the line meter
     * @param lmeter pointer to a line meter object
     * @param value new value
     */
    void setValue(int16_t value)
    {
        lv_lmeter_set_value(this,value);
    }

    /**
     * Set minimum and the maximum values of a line meter
     * @param lmeter pointer to he line meter object
     * @param min minimum value
     * @param max maximum value
     */
    void setRange(int16_t min, int16_t max)
    {
        lv_lmeter_set_range(this,min,max);
    }

    /**
     * Set the scale settings of a line meter
     * @param lmeter pointer to a line meter object
     * @param angle angle of the scale (0..360)
     * @param line_cnt number of lines
     */
    void setScale(uint16_t angle, uint8_t line_cnt)
    {
        lv_lmeter_set_scale(this,angle,line_cnt);
    }

    /**
     * Set the styles of a line meter
     * @param lmeter pointer to a line meter object
     * @param type which style should be set (can be only `LV_LMETER_STYLE_MAIN`)
     * @param style set the style of the line meter
     */
    void setStyle(Styles type, LVStyle * style)
    {
        lv_lmeter_set_style(this, type, style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the value of a line meter
     * @param lmeter pointer to a line meter object
     * @return the value of the line meter
     */
    int16_t getValue()
    {
        return lv_lmeter_get_value(this);
    }

    /**
     * Get the minimum value of a line meter
     * @param lmeter pointer to a line meter object
     * @return the minimum value of the line meter
     */
    int16_t getMinValue()
    {
        return lv_lmeter_get_min_value(this);
    }

    /**
     * Get the maximum value of a line meter
     * @param lmeter pointer to a line meter object
     * @return the maximum value of the line meter
     */
    int16_t getMaxValue()
    {
        return lv_lmeter_get_max_value(this);
    }

    /**
     * Get the scale number of a line meter
     * @param lmeter pointer to a line meter object
     * @return number of the scale units
     */
    uint8_t getLineCount()
    {
        return lv_lmeter_get_line_count(this);
    }

    /**
     * Get the scale angle of a line meter
     * @param lmeter pointer to a line meter object
     * @return angle of the scale
     */
    uint16_t getScaleAngle()
    {
        return lv_lmeter_get_scale_angle(this);
    }

    /**
     * Get the style of a line meter
     * @param lmeter pointer to a line meter object
     * @param type which style should be get (can be only `LV_LMETER_STYLE_MAIN`)
     * @return pointer to the line meter's style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_lmeter_get_style(this,type);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_LMETER*/

#endif /*LVLMETER_H*/
