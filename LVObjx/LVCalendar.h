/**
 * @file lv_calendar.h
 *
 */

#ifndef LVCALENDAR_H
#define LVCALENDAR_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_calendar.h>

#if LV_USE_CALENDAR != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Represents a date on the calendar object (platform-agnostic).
 */
class LVCalendarDate : public lv_calendar_date_t
{
public:
    LVCalendarDate() {}
};

/*Data of calendar*/
class LVCalendar
        : public LVObject
        , public LVFakeMemHeader<lv_calendar_ext_t>
        , public lv_calendar_ext_t
{
    LV_OBJECT(LVCalendar,lv_calendar_create,lv_calendar_ext_t)
public:

    /** Calendar styles*/
    enum Styles : lv_calendar_style_t
    {
        STYLE_BG               = LV_CALENDAR_STYLE_BG, /**< Background and "normal" date numbers style */
        STYLE_HEADER           = LV_CALENDAR_STYLE_HEADER, /** Calendar header style */
        STYLE_HEADER_PR        = LV_CALENDAR_STYLE_HEADER_PR, /** Calendar header style (when pressed) */
        STYLE_DAY_NAMES        = LV_CALENDAR_STYLE_DAY_NAMES, /** Day name style */
        STYLE_HIGHLIGHTED_DAYS = LV_CALENDAR_STYLE_HIGHLIGHTED_DAYS, /** Highlighted day style */
        STYLE_INACTIVE_DAYS    = LV_CALENDAR_STYLE_INACTIVE_DAYS, /** Inactive day style */
        STYLE_WEEK_BOX         = LV_CALENDAR_STYLE_WEEK_BOX, /** Week highlight style */
        STYLE_TODAY_BOX        = LV_CALENDAR_STYLE_TODAY_BOX, /** Today highlight style */
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a calendar objects
     * @param par pointer to an object, it will be the parent of the new calendar
     * @param copy pointer to a calendar object, if not NULL then the new object will be copied from it
     * @return pointer to the created calendar
     */
    //LVCalendar(LVObject * parent, const LVCalendar * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the today's date
     * @param calendar pointer to a calendar object
     * @param today pointer to an `lv_calendar_date_t` variable containing the date of today. The value
     * will be saved it can be local variable too.
     */
    void setTodayDate(LVCalendarDate * today)
    {
        lv_calendar_set_today_date(this,today);
    }

    /**
     * Set the currently showed
     * @param calendar pointer to a calendar object
     * @param showed pointer to an `lv_calendar_date_t` variable containing the date to show. The value
     * will be saved it can be local variable too.
     */
    void setShowedDate(LVCalendarDate * showed)
    {
        lv_calendar_set_showed_date(this,showed);
    }

    /**
     * Set the the highlighted dates
     * @param calendar pointer to a calendar object
     * @param highlighted pointer to an `lv_calendar_date_t` array containing the dates. ONLY A POINTER
     * WILL BE SAVED! CAN'T BE LOCAL ARRAY.
     * @param date_num number of dates in the array
     */
    void setHighlightedDates(LVCalendarDate * highlighted, uint16_t date_num)
    {
        lv_calendar_set_highlighted_dates(this,highlighted,date_num);
    }

    /**
     * Set the name of the days
     * @param calendar pointer to a calendar object
     * @param day_names pointer to an array with the names. E.g. `const char * days[7] = {"Sun", "Mon",
     * ...}` Only the pointer will be saved so this variable can't be local which will be destroyed
     * later.
     */
    void setDayNames(const char ** day_names)
    {
        lv_calendar_set_day_names(this,day_names);
    }

    /**
     * Set the name of the month
     * @param calendar pointer to a calendar object
     * @param day_names pointer to an array with the names. E.g. `const char * days[12] = {"Jan", "Feb",
     * ...}` Only the pointer will be saved so this variable can't be local which will be destroyed
     * later.
     */
    void setMonthNames(const char ** day_names)
    {
        lv_calendar_set_month_names(this,day_names);
    }

    /**
     * Set a style of a calendar.
     * @param calendar pointer to calendar object
     * @param type which style should be set
     * @param style pointer to a style
     *  */
    void setStyle(Styles type, const LVStyle * style)
    {
        lv_calendar_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the today's date
     * @param calendar pointer to a calendar object
     * @return return pointer to an `lv_calendar_date_t` variable containing the date of today.
     */
    LVCalendarDate * getTodayDate()
    {
        return (LVCalendarDate *)lv_calendar_get_today_date(this);
    }

    /**
     * Get the currently showed
     * @param calendar pointer to a calendar object
     * @return pointer to an `lv_calendar_date_t` variable containing the date is being shown.
     */
    LVCalendarDate * getShowedDate()
    {
        return (LVCalendarDate *)lv_calendar_get_showed_date(this);
    }

    /**
     * Get the the pressed date.
     * @param calendar pointer to a calendar object
     * @return pointer to an `lv_calendar_date_t` variable containing the pressed date.
     */
    LVCalendarDate * getPressedDate()
    {
        return (LVCalendarDate *)lv_calendar_get_pressed_date(this);
    }

    /**
     * Get the the highlighted dates
     * @param calendar pointer to a calendar object
     * @return pointer to an `lv_calendar_date_t` array containing the dates.
     */
    LVCalendarDate * getHighlightedDates()
    {
        return (LVCalendarDate *)lv_calendar_get_highlighted_dates(this);
    }

    /**
     * Get the number of the highlighted dates
     * @param calendar pointer to a calendar object
     * @return number of highlighted days
     */
    uint16_t getHighlightedDatesNum()
    {
        return lv_calendar_get_highlighted_dates_num(this);
    }

    /**
     * Get the name of the days
     * @param calendar pointer to a calendar object
     * @return pointer to the array of day names
     */
    const char ** getDayNames()
    {
        return lv_calendar_get_day_names(this);
    }

    /**
     * Get the name of the month
     * @param calendar pointer to a calendar object
     * @return pointer to the array of month names
     */
    const char ** getMonthNames()
    {
        return lv_calendar_get_month_names(this);
    }

    /**
     * Get style of a calendar.
     * @param calendar pointer to calendar object
     * @param type which style should be get
     * @return style pointer to the style
     *  */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_calendar_get_style(this,type);
    }

};

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CALENDAR*/

#endif /*LVCALENDAR_H*/
