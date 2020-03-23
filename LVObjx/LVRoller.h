/**
 * @file lv_roller.h
 *
 */

#ifndef LVROLLER_H
#define LVROLLER_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_roller.h>

#if LV_USE_ROLLER != 0

#include "../LVCore/LVObject.h"
#include "LVLabel.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of roller*/
class LVRoller
        : public LVObject
        , lv_roller_ext_t
{
public:

    enum Styles : lv_roller_style_t
    {
        STYLE_BG  = LV_ROLLER_STYLE_BG,
        STYLE_SEL = LV_ROLLER_STYLE_SEL,
    };

    /** Roller mode. */
    enum Modes : lv_roller_mode_t
    {
        MODE_NORMAL    = LV_ROLLER_MODE_NORMAL,    /**< Normal mode (roller ends at the end of the options). */
        MODE_INIFINITE = LV_ROLLER_MODE_INIFINITE, /**< Infinite mode (roller can be scrolled forever). */
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a roller object
     * @param par pointer to an object, it will be the parent of the new roller
     * @param copy pointer to a roller object, if not NULL then the new object will be copied from it
     * @return pointer to the created roller
     */
    //LVRoller(LVObject * par, const LVRoller * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the options on a roller
     * @param roller pointer to roller object
     * @param options a string with '\n' separated options. E.g. "One\nTwo\nThree"
     * @param mode `LV_ROLLER_MODE_NORMAL` or `LV_ROLLER_MODE_INFINITE`
     */
    void setOptions(const char * options, lv_roller_mode_t mode)
    {
        lv_roller_set_options(this,options,mode);
    }

    /**
     * Set the align of the roller's options (left, right or center[default])
     * @param roller - pointer to a roller object
     * @param align - one of lv_label_align_t values (left, right, center)
     */
    void setAlign(lv_label_align_t align)
    {
        lv_roller_set_align(this,align);
    }

    /**
     * Set the selected option
     * @param roller pointer to a roller object
     * @param sel_opt id of the selected option (0 ... number of option - 1);
     * @param anim LV_ANOM_ON: set with animation; LV_ANIM_OFF set immediately
     */
    void setSelected(uint16_t sel_opt, lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_roller_set_selected(this,sel_opt,anim);
    }

    /**
     * Set the height to show the given number of rows (options)
     * @param roller pointer to a roller object
     * @param row_cnt number of desired visible rows
     */
    void setVisibleRowCount(uint8_t row_cnt)
    {
        lv_roller_set_visible_row_count(this,row_cnt);
    }

    /**
     * Set a fix width for the drop down list
     * @param roller pointer to a roller obejct
     * @param w the width when the list is opened (0: auto size)
     */
    void setFixWidth(LVCoord w = 0)
    {
        lv_roller_set_fix_width(this, w);
    }

    /**
     * Set the open/close animation time.
     * @param roller pointer to a roller object
     * @param anim_time: open/close animation time [ms]
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_roller_set_anim_time(this, anim_time);
    }

    /**
     * Set a style of a roller
     * @param roller pointer to a roller object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_roller_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/
    /**
     * Get the id of the selected option
     * @param roller pointer to a roller object
     * @return id of the selected option (0 ... number of option - 1);
     */
    uint16_t getSelected()
    {
        return lv_roller_get_selected(this);
    }

    /**
     * Get the current selected option as a string
     * @param roller pointer to roller object
     * @param buf pointer to an array to store the string
     * @param buf_size size of `buf` in bytes. 0: to ignore it.
     */
    void getSelectedStr(char * buf, uint16_t buf_size)
    {
        lv_roller_get_selected_str(this, buf, buf_size);
    }

    /**
     * Get the align attribute. Default alignment after _create is LV_LABEL_ALIGN_CENTER
     * @param roller pointer to a roller object
     * @return LV_LABEL_ALIGN_LEFT, LV_LABEL_ALIGN_RIGHT or LV_LABEL_ALIGN_CENTER
     */
    LVLabel::AlignPolicy getAlign()
    {
        return (LVLabel::AlignPolicy)lv_roller_get_align(this);
    }

    /**
     * Get the options of a roller
     * @param roller pointer to roller object
     * @return the options separated by '\n'-s (E.g. "Option1\nOption2\nOption3")
     */
    const char * getOptions()
    {
        return lv_roller_get_options(this);
    }

    /**
     * Get the open/close animation time.
     * @param roller pointer to a roller
     * @return open/close animation time [ms]
     */
    uint16_t getAnimTime()
    {
        return lv_roller_get_anim_time(this);
    }

    /**
     * Get the auto width set attribute
     * @param roller pointer to a roller object
     * @return true: auto size enabled; false: manual width settings enabled
     */
    bool getHorFit()
    {
        return lv_roller_get_hor_fit(this);
    }

    /**
     * Get a style of a roller
     * @param roller pointer to a roller object
     * @param type which style should be get
     * @return style pointer to a style
     *  */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_roller_get_style(this,type);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ROLLER*/

#endif /*LVROLLER_H*/
