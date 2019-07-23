/**
 * @file lv_line.h
 *
 */

#ifndef LVLINE_H
#define LVLINE_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_line.h>

#if LV_USE_LINE != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVLine
        : public LVObject
        , public LVFakeMemHeader<lv_line_ext_t>
        , public lv_line_ext_t
{
    LV_OBJECT(LVLine,lv_line_create,lv_line_ext_t)
public:

    /*Styles*/
    enum Styles : lv_line_style_t
    {
        STYLE_MAIN = LV_LINE_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a line objects
     * @param par pointer to an object, it will be the parent of the new line
     * @return pointer to the created line
     */
    //LVLine(LVObject * par, const LVLine * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set an array of points. The line object will connect these points.
     * @param line pointer to a line object
     * @param point_a an array of points. Only the address is saved,
     * so the array can NOT be a local variable which will be destroyed
     * @param point_num number of points in 'point_a'
     */
    void setPoints(const LVPoint point_a[], uint16_t point_num)
    {
        lv_line_set_points(this,point_a,point_num);
    }

    /**
     * Enable (or disable) the auto-size option. The size of the object will fit to its points.
     * (set width to x max and height to y max)
     * @param line pointer to a line object
     * @param en true: auto size is enabled, false: auto size is disabled
     */
    void setAutoSize(bool en)
    {
        lv_line_set_auto_size(this,en);
    }

    /**
     * Enable (or disable) the y coordinate inversion.
     * If enabled then y will be subtracted from the height of the object,
     * therefore the y=0 coordinate will be on the bottom.
     * @param line pointer to a line object
     * @param en true: enable the y inversion, false:disable the y inversion
     */
    void setYInvert(bool en)
    {
        lv_line_set_y_invert(this,en);
    }


    /**
     * Set the style of a line
     * @param line pointer to a line object
     * @param type which style should be set (can be only `LV_LINE_STYLE_MAIN`)
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_line_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the auto size attribute
     * @param line pointer to a line object
     * @return true: auto size is enabled, false: disabled
     */
    bool getAutoSize()
    {
        return lv_line_get_auto_size(this);
    }

    /**
     * Get the y inversion attribute
     * @param line pointer to a line object
     * @return true: y inversion is enabled, false: disabled
     */
    bool getYInvert()
    {
        return lv_line_get_y_invert(this);
    }

    /**
     * Get the style of an line object
     * @param line pointer to an line object
     * @param type which style should be get (can be only `LV_LINE_STYLE_MAIN`)
     * @return pointer to the line's style
     */
    const LVStyle * getStyle(Styles type = STYLE_MAIN)
    {
        return (const LVStyle *)lv_line_get_style(this,type);
    }

};
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_LINE*/


#endif /*LVLINE_H*/
