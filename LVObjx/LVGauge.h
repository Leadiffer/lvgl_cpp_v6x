/**
 * @file lv_gauge.h
 *
 */

#ifndef LVGAUGE_H
#define LVGAUGE_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_gauge.h>

#if LV_USE_GAUGE != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of gauge*/
class LVGauge
        : public LVObject
        , public lv_gauge_ext_t
{
    LV_OBJECT(LVGauge,lv_gauge_create,lv_gauge_ext_t)
public:

    /*Styles*/
    enum Styles : lv_gauge_style_t
    {
        STYLE_MAIN = LV_GAUGE_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a gauge objects
     * @param par pointer to an object, it will be the parent of the new gauge
     * @param copy pointer to a gauge object, if not NULL then the new object will be copied from it
     * @return pointer to the created gauge
     */
    //LVGauge(LVObject * parent, const LVGauge * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the number of needles
     * @param gauge pointer to gauge object
     * @param needle_cnt new count of needles
     * @param colors an array of colors for needles (with 'num' elements)
     */
    void setNeedleCount(uint8_t needle_cnt, const lv_color_t colors[])
    {
        lv_gauge_set_needle_count(this,needle_cnt,colors);
    }

    /**
     * Set the value of a needle
     * @param gauge pointer to a gauge
     * @param needle_id the id of the needle
     * @param value the new value
     */
    void setValue(uint8_t needle_id, int16_t value)
    {
        lv_gauge_set_value(this,needle_id,value);
    }

    /**
     * Set minimum and the maximum values of a gauge
     * @param gauge pointer to he gauge object
     * @param min minimum value
     * @param max maximum value
     */
    void setRange(int16_t min, int16_t max)
    {
        lv_gauge_set_range(this, min, max);
    }

    /**
     * Set a critical value on the scale. After this value 'line.color' scale lines will be drawn
     * @param gauge pointer to a gauge object
     * @param value the critical value
     */
    void setCriticalValue(int16_t value)
    {
        lv_gauge_set_critical_value(this, value);
    }

    /**
     * Set the scale settings of a gauge
     * @param gauge pointer to a gauge object
     * @param angle angle of the scale (0..360)
     * @param line_cnt count of scale lines.
     * The get a given "subdivision" lines between label, `line_cnt` = (sub_div + 1) * (label_cnt - 1) +
     * 1
     * @param label_cnt count of scale labels.
     */
    void setScale(uint16_t angle, uint8_t line_cnt, uint8_t label_cnt)
    {
        lv_gauge_set_scale(this,angle,line_cnt,label_cnt);
    }

    /**
     * Set the styles of a gauge
     * @param gauge pointer to a gauge object
     * @param type which style should be set (can be only `LV_GAUGE_STYLE_MAIN`)
     * @param style set the style of the gauge
     *  */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_gauge_set_style(this ,type ,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the value of a needle
     * @param gauge pointer to gauge object
     * @param needle the id of the needle
     * @return the value of the needle [min,max]
     */
    int16_t getValue(uint8_t needle)
    {
        return lv_gauge_get_value(this,needle);
    }

    /**
     * Get the count of needles on a gauge
     * @param gauge pointer to gauge
     * @return count of needles
     */
    uint8_t getNeedleCount()
    {
        return lv_gauge_get_needle_count(this);
    }

    /**
     * Get the minimum value of a gauge
     * @param gauge pointer to a gauge object
     * @return the minimum value of the gauge
     */
    int16_t getMinValue()
    {
        return lv_gauge_get_min_value(this);
    }

    /**
     * Get the maximum value of a gauge
     * @param gauge pointer to a gauge object
     * @return the maximum value of the gauge
     */
    int16_t getMaxValue()
    {
        return lv_gauge_get_max_value(this);
    }

    /**
     * Get a critical value on the scale.
     * @param gauge pointer to a gauge object
     * @return the critical value
     */
    int16_t getCriticalValue()
    {
        return lv_gauge_get_critical_value(this);
    }

    /**
     * Set the number of labels (and the thicker lines too)
     * @param gauge pointer to a gauge object
     * @return count of labels
     */
    uint8_t getLabelCount()
    {
        return lv_gauge_get_label_count(this);
    }

    /**
     * Get the scale number of a gauge
     * @param gauge pointer to a gauge object
     * @return number of the scale units
     */
    uint8_t getLineCount()
    {
        return lv_gauge_get_line_count(this);
    }

    /**
     * Get the scale angle of a gauge
     * @param gauge pointer to a gauge object
     * @return angle of the scale
     */
    uint16_t getScaleAngle()
    {
        return lv_gauge_get_scale_angle(this);
    }

    /**
     * Get the style of a gauge
     * @param gauge pointer to a gauge object
     * @param type which style should be get (can be only `LV_GAUGE_STYLE_MAIN`)
     * @return pointer to the gauge's style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_gauge_get_style(this,type);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_GAUGE*/

#endif /*LVGAUGE_H*/
