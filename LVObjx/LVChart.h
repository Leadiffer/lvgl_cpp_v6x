/**
 * @file lv_chart.h
 *
 */

#ifndef LVCHART_H
#define LVCHART_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_chart.h>

#if LV_USE_CHART != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/


class LVChartSeries : public lv_chart_series_t
{
public:
    LVChartSeries() {}
};

class LVChartAxisCfg : public lv_chart_axis_cfg_t
{
public:
    LVChartAxisCfg() {}
};

/*Data of chart */
class LVChart
        : public LVObject
        , public lv_chart_ext_t
{
    LV_OBJECT(LVChart,lv_chart_create,lv_chart_ext_t)
public:
    /** Chart types*/
    enum Types : lv_chart_type_t
    {
        TYPE_NONE          = LV_CHART_TYPE_NONE          , /**< Don't draw the series*/
        TYPE_LINE          = LV_CHART_TYPE_LINE          , /**< Connect the points with lines*/
        TYPE_COLUMN        = LV_CHART_TYPE_COLUMN        , /**< Draw columns*/
        TYPE_POINT         = LV_CHART_TYPE_POINT         , /**< Draw circles on the points*/
        TYPE_VERTICAL_LINE = LV_CHART_TYPE_VERTICAL_LINE , /**< Draw vertical lines on points (useful when chart width == point count)*/
        TYPE_AREA          = LV_CHART_TYPE_AREA          , /**< Draw area chart*/
    };

    /** Chart update mode for `lv_chart_set_next`*/
    enum UpdateModes : lv_chart_update_mode_t
    {
        UPDATE_MODE_SHIFT    = LV_CHART_UPDATE_MODE_SHIFT,     /**< Shift old data to the left and add the new one o the right*/
        UPDATE_MODE_CIRCULAR = LV_CHART_UPDATE_MODE_CIRCULAR,  /**< Add the new data in a circular way*/
    };

    /** Data of axis */
    enum AxisOptions : lv_chart_axis_options_t
    {
        AXIS_SKIP_LAST_TICK = LV_CHART_AXIS_SKIP_LAST_TICK ,    /**< don't draw the last tick */
        AXIS_DRAW_LAST_TICK = LV_CHART_AXIS_DRAW_LAST_TICK      /**< draw the last tick */
    };

    enum Styles : lv_chart_style_t
    {
        STYLE_MAIN = LV_CHART_STYLE_MAIN,
    };


    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a chart background objects
     * @param par pointer to an object, it will be the parent of the new chart background
     * @param copy pointer to a chart background object, if not NULL then the new object will be copied
     * from it
     * @return pointer to the created chart background
     */
    //LVChart(LVObject * parent, const LVChart * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Allocate and add a data series to the chart
     * @param chart pointer to a chart object
     * @param color color of the data series
     * @return pointer to the allocated data series
     */
    LVChartSeries * addSeries(LVColor color)
    {
        return (LVChartSeries *)lv_chart_add_series(this,color);
    }

    /**
     * Clear the point of a serie
     * @param chart pointer to a chart object
     * @param serie pointer to the chart's serie to clear
     */
    void clearSerie(LVChartSeries * serie)
    {
        lv_chart_clear_serie(this,serie);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the number of horizontal and vertical division lines
     * @param chart pointer to a graph background object
     * @param hdiv number of horizontal division lines
     * @param vdiv number of vertical division lines
     */
    void setDivLineCount(uint8_t hdiv, uint8_t vdiv)
    {
        lv_chart_set_div_line_count(this,hdiv,vdiv);
    }

    /**
     * Set the minimal and maximal y values
     * @param chart pointer to a graph background object
     * @param ymin y minimum value
     * @param ymax y maximum value
     */
    void setRange(LVCoord ymin, LVCoord ymax)
    {
        lv_chart_set_range(this,ymin,ymax);
    }

    /**
     * Set a new type for a chart
     * @param chart pointer to a chart object
     * @param type new type of the chart (from 'lv_chart_type_t' enum)
     */
    void setType(Types type)
    {
        lv_chart_set_type(this,type);
    }

    /**
     * Set the number of points on a data line on a chart
     * @param chart pointer r to chart object
     * @param point_cnt new number of points on the data lines
     */
    void setPointCount(uint16_t point_cnt)
    {
        lv_chart_set_point_count(this,point_cnt);
    }

    /**
     * Set the opacity of the data series
     * @param chart pointer to a chart object
     * @param opa opacity of the data series
     */
    void setSeriesOpa(lv_opa_t opa)
    {
        lv_chart_set_series_opa(this,opa);
    }

    /**
     * Set the line width or point radius of the data series
     * @param chart pointer to a chart object
     * @param width the new width
     */
    void setSeriesWidth(LVCoord width)
    {
        lv_chart_set_series_width(this,width);
    }

    /**
     * Set the dark effect on the bottom of the points or columns
     * @param chart pointer to a chart object
     * @param dark_eff dark effect level (LV_OPA_TRANSP to turn off)
     */
    void setSeriesDarking(lv_opa_t dark_eff)
    {
        lv_chart_set_series_darking(this,dark_eff);
    }

    /**
     * Initialize all data points with a value
     * @param chart pointer to chart object
     * @param ser pointer to a data series on 'chart'
     * @param y the new value  for all points
     */
    void initPoints(LVChartSeries * ser, LVCoord y)
    {
        lv_chart_init_points(this,ser,y);
    }

    /**
     * Set the value of points from an array
     * @param chart pointer to chart object
     * @param ser pointer to a data series on 'chart'
     * @param y_array array of 'lv_coord_t' points (with 'points count' elements )
     */
    void setPoints(LVChartSeries * ser, LVCoord y_array[])
    {
        lv_chart_set_points(this,ser,y_array);
    }

    /**
     * Shift all data right and set the most right data on a data line
     * @param chart pointer to chart object
     * @param ser pointer to a data series on 'chart'
     * @param y the new value of the most right data
     */
    void setNext(LVChartSeries * ser, LVCoord y)
    {
        lv_chart_set_next(this,ser,y);
    }

    /**
     * Set update mode of the chart object.
     * @param chart pointer to a chart object
     * @param update mode
     */
    void setUpdateMode(UpdateModes update_mode)
    {
        lv_chart_set_update_mode(this,update_mode);
    }

    /**
     * Set the style of a chart
     * @param chart pointer to a chart object
     * @param type which style should be set (can be only `LV_CHART_STYLE_MAIN`)
     * @param style pointer to a style
     */
    void setStyle(const  LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_chart_set_style(this,type, style);
    }

    /**
     * Set the length of the tick marks on the x axis
     * @param chart pointer to the chart
     * @param major_tick_len the length of the major tick or `LV_CHART_TICK_LENGTH_AUTO` to set automatically
     *                       (where labels are added)
     * @param minor_tick_len the length of the minor tick, `LV_CHART_TICK_LENGTH_AUTO` to set automatically
     *                       (where no labels are added)
     */
    void setXTickLength(uint8_t major_tick_len, uint8_t minor_tick_len)
    {
        lv_chart_set_x_tick_length(this,major_tick_len,minor_tick_len);
    }

    /**
     * Set the length of the tick marks on the y axis
     * @param chart pointer to the chart
     * @param major_tick_len the length of the major tick or `LV_CHART_TICK_LENGTH_AUTO` to set automatically
     *                       (where labels are added)
     * @param minor_tick_len the length of the minor tick, `LV_CHART_TICK_LENGTH_AUTO` to set automatically
     *                       (where no labels are added)
     */
    void setYTickLength(uint8_t major_tick_len, uint8_t minor_tick_len)
    {
        lv_chart_set_y_tick_length(this,major_tick_len,minor_tick_len);
    }

    /**
     * Set the x-axis tick count and labels of a chart
     * @param chart             pointer to a chart object
     * @param list_of_values    list of string values, terminated with \n, except the last
     * @param num_tick_marks    if list_of_values is NULL: total number of ticks per axis
     *                          else number of ticks between two value labels
     * @param options           extra options
     */
    void setXTickTexts(const char * list_of_values, uint8_t num_tick_marks, AxisOptions options)
    {
        lv_chart_set_x_tick_texts(this,list_of_values,num_tick_marks,options);
    }

    /**
     * Set the y-axis tick count and labels of a chart
     * @param chart             pointer to a chart object
     * @param list_of_values    list of string values, terminated with \n, except the last
     * @param num_tick_marks    if list_of_values is NULL: total number of ticks per axis
     *                          else number of ticks between two value labels
     * @param options           extra options
     */
    void setYTickTexts(const char * list_of_values, uint8_t num_tick_marks,AxisOptions options)
    {
        lv_chart_set_y_tick_texts(this,list_of_values,num_tick_marks,options);
    }

    /**
     * Set the margin around the chart, used for axes value and ticks
     * @param chart     pointer to an chart object
     * @param margin    value of the margin [px]
     */
    void setMargin(uint16_t margin)
    {
        lv_chart_set_margin(this,margin);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the type of a chart
     * @param chart pointer to chart object
     * @return type of the chart (from 'lv_chart_t' enum)
     */
    Types getType()
    {
        return (Types)lv_chart_get_type(this);
    }

    /**
     * Get the data point number per data line on chart
     * @param chart pointer to chart object
     * @return point number on each data line
     */
    uint16_t getPointCnt()
    {
        return lv_chart_get_point_cnt(this);
    }

    /**
     * Get the opacity of the data series
     * @param chart pointer to chart object
     * @return the opacity of the data series
     */
    lv_opa_t getSeriesOpa()
    {
        return lv_chart_get_series_opa(this);
    }

    /**
     * Get the data series width
     * @param chart pointer to chart object
     * @return the width the data series (lines or points)
     */
    LVCoord getSeriesWidth()
    {
        return lv_chart_get_series_width(this);
    }

    /**
     * Get the dark effect level on the bottom of the points or columns
     * @param chart pointer to chart object
     * @return dark effect level (LV_OPA_TRANSP to turn off)
     */
    lv_opa_t getSeriesDarking()
    {
        return lv_chart_get_series_darking(this);
    }

    /**
     * Get the style of an chart object
     * @param chart pointer to an chart object
     * @param type which style should be get (can be only `LV_CHART_STYLE_MAIN`)
     * @return pointer to the chart's style
     */
    const LVStyle * getStyle(Styles type)
    {
        return ( const LVStyle *)lv_chart_get_style(this,type);
    }

    /**
     * Get the margin around the chart, used for axes value and labels
     * @param chart pointer to an chart object
     * @param return value of the margin
     */
    uint16_t getMargin()
    {
        return lv_chart_get_margin(this);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Refresh a chart if its data line has changed
     * @param chart pointer to chart object
     */
    void refresh()
    {
        lv_chart_refresh(this);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CHART*/

#endif /*LVCHART_H*/
