/**
 * @file lv_ddlist.h
 *
 */

#ifndef LVDROPDOWNLIST_H
#define LVDROPDOWNLIST_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_ddlist.h>

#if LV_USE_DDLIST != 0

#include "../LVCore/LVObject.h"
#include "LVPage.h"
#include "LVLabel.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of drop down list*/

class LVDropDownList
        : public LVObject
        , public lv_ddlist_ext_t
{
    LV_OBJECT(LVDropDownList,lv_ddlist_create,lv_ddlist_ext_t)
public:


    enum Styles : lv_ddlist_style_t
    {
        STYLE_BG  = LV_DDLIST_STYLE_BG,
        STYLE_SEL = LV_DDLIST_STYLE_SEL,
        STYLE_SB  = LV_DDLIST_STYLE_SB,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/
    /**
     * Create a drop down list objects
     * @param par pointer to an object, it will be the parent of the new drop down list
     * @param copy pointer to a drop down list object, if not NULL then the new object will be copied
     * from it
     * @return pointer to the created drop down list
     */
    //LVDropDownList(LVObject * parent, const LVDropDownList * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the options in a drop down list from a string
     * @param ddlist pointer to drop down list object
     * @param options a string with '\n' separated options. E.g. "One\nTwo\nThree"
     */
    void setOptions(const char * options)
    {
        lv_ddlist_set_options(this,options);
    }

    /**
     * Set the selected option
     * @param ddlist pointer to drop down list object
     * @param sel_opt id of the selected option (0 ... number of option - 1);
     */
    void setSelected(uint16_t sel_opt)
    {
        lv_ddlist_set_selected(this,sel_opt);
    }

    /**
     * Set a fix height for the drop down list
     * If 0 then the opened ddlist will be auto. sized else the set height will be applied.
     * @param ddlist pointer to a drop down list
     * @param h the height when the list is opened (0: auto size)
     */
    void setFixHeight(LVCoord h)
    {
        lv_ddlist_set_fix_height(this,h);
    }

    /**
     * Set a fix width for the drop down list
     * @param ddlist pointer to a drop down list
     * @param w the width when the list is opened (0: auto size)
     */
    void setFixWidth(LVCoord w)
    {
        lv_ddlist_set_fix_width(this,w);
    }

    /**
     * Set arrow draw in a drop down list
     * @param ddlist pointer to drop down list object
     * @param en enable/disable a arrow draw. E.g. "true" for draw.
     */
    void setDrawArrow(bool en)
    {
        lv_ddlist_set_draw_arrow(this,en);
    }

    /**
     * Leave the list opened when a new value is selected
     * @param ddlist pointer to drop down list object
     * @param en enable/disable "stay open" feature
     */
    void setStayOpen(bool en)
    {
        lv_ddlist_set_stay_open(this,en);
    }

    /**
     * Set the scroll bar mode of a drop down list
     * @param ddlist pointer to a drop down list object
     * @param sb_mode the new mode from 'lv_page_sb_mode_t' enum
     */
    void setScrollBarMode(LVPage::SBModes mode)
    {
        lv_ddlist_set_sb_mode(this, mode);
    }
    /**
     * Set the open/close animation time.
     * @param ddlist pointer to a drop down list
     * @param anim_time: open/close animation time [ms]
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_ddlist_set_anim_time(this, anim_time);
    }

    /**
     * Set a style of a drop down list
     * @param ddlist pointer to a drop down list object
     * @param type which style should be set
     * @param style pointer to a style
     *  */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_ddlist_set_style(this,type,style);
    }

    /**
     * Set the alignment of the labels in a drop down list
     * @param ddlist pointer to a drop down list object
     * @param align alignment of labels
     */
    void setAlign(lv_label_align_t align)
    {
        lv_ddlist_set_align(this,align);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the options of a drop down list
     * @param ddlist pointer to drop down list object
     * @return the options separated by '\n'-s (E.g. "Option1\nOption2\nOption3")
     */
    const char * getOptions()
    {
        return lv_ddlist_get_options(this);
    }

    /**
     * Get the selected option
     * @param ddlist pointer to drop down list object
     * @return id of the selected option (0 ... number of option - 1);
     */
    uint16_t getSelected()
    {
        return lv_ddlist_get_selected(this);
    }

    /**
     * Get the current selected option as a string
     * @param ddlist pointer to ddlist object
     * @param buf pointer to an array to store the string
     * @param buf_size size of `buf` in bytes. 0: to ignore it.
     */
    void getSelectedStr(char * buf, uint16_t buf_size)
    {
        lv_ddlist_get_selected_str(this,buf,buf_size);
    }

    /**
     * Get the fix height value.
     * @param ddlist pointer to a drop down list object
     * @return the height if the ddlist is opened (0: auto size)
     */
    LVCoord getFixHeight()
    {
        return lv_ddlist_get_fix_height(this);
    }

    /**
     * Get arrow draw in a drop down list
     * @param ddlist pointer to drop down list object
     */
    bool getDrawArrow()
    {
        return lv_ddlist_get_draw_arrow(this);
    }

    /**
     * Get whether the drop down list stay open after selecting a  value or not
     * @param ddlist pointer to drop down list object
     */
    bool getStayOpen()
    {
        return lv_ddlist_get_stay_open(this);
    }

    /**
     * Get the scroll bar mode of a drop down list
     * @param ddlist pointer to a  drop down list object
     * @return scrollbar mode from 'lv_page_sb_mode_t' enum
     */
    LVPage::SBModes getScrollBarMode()
    {
        return (LVPage::SBModes)lv_ddlist_get_sb_mode(this);
    }

    /**
     * Get the open/close animation time.
     * @param ddlist pointer to a drop down list
     * @return open/close animation time [ms]
     */
    uint16_t getAnimTime()
    {
        return lv_ddlist_get_anim_time(this);
    }

    /**
     * Get a style of a drop down list
     * @param ddlist pointer to a drop down list object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_ddlist_get_style(this,type);
    }

    /**
     * Get the alignment of the labels in a drop down list
     * @param ddlist pointer to a drop down list object
     * @return alignment of labels
     */
     LVLabel::AlignPolicy getAlign()
     {
         return (LVLabel::AlignPolicy)lv_ddlist_get_align(this);
     }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Open the drop down list with or without animation
     * @param ddlist pointer to drop down list object
     * @param anim_en LV_ANIM_ON: use animation; LV_ANOM_OFF: not use animations
     */
    void open(lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_ddlist_open(this,anim);
    }

    /**
     * Close (Collapse) the drop down list
     * @param ddlist pointer to drop down list object
     * @param anim_en LV_ANIM_ON: use animation; LV_ANOM_OFF: not use animations
     */
    void close(lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_ddlist_close(this,anim);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_DDLIST*/

#endif /*LVDROPDOWNLIST_H*/
