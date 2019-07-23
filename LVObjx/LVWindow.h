/**
 * @file lv_win.h
 *
 */

#ifndef LVWINDOW_H
#define LVWINDOW_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_win.h>

#if LV_USE_WIN != 0

#include "../LVCore/LVObject.h"
#include "LVImage.h"
#include "LVLabel.h"
#include "LVPage.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of window*/
class LVWindow
        : public LVObject
        , public LVFakeMemHeader<lv_win_ext_t>
        , public lv_win_ext_t
{
    LV_OBJECT(LVWindow,lv_win_create,lv_win_ext_t)
public:

    /** Window styles. */
    enum Styles : lv_win_style_t
    {
        STYLE_BG       = LV_WIN_STYLE_BG,      /**< Window object background style. */
        STYLE_CONTENT  = LV_WIN_STYLE_CONTENT, /**< Window content style. */
        STYLE_SB       = LV_WIN_STYLE_SB,      /**< Window scrollbar style. */
        STYLE_HEADER   = LV_WIN_STYLE_HEADER,  /**< Window titlebar background style. */
        STYLE_BTN_REL  = LV_WIN_STYLE_BTN_REL, /**< Same meaning as ordinary button styles. */
        STYLE_BTN_PR   = LV_WIN_STYLE_BTN_PR,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a window objects
     * @param par pointer to an object, it will be the parent of the new window
     * @param copy pointer to a window object, if not NULL then the new object will be copied from it
     * @return pointer to the created window
     */
    //LVWindow(LVObject * par, const LVWindow * copy);

    /**
     * Delete all children of the scrl object, without deleting scrl child.
     * @param obj pointer to an object
     */
    void clean()
    {
        lv_win_clean(this);
    }

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Add control button to the header of the window
     * @param win pointer to a window object
     * @param img_src an image source ('lv_img_t' variable, path to file or a symbol)
     * @return pointer to the created button object
     */
    lv_obj_t * addBtn(const void * img_src)
    {
        return lv_win_add_btn(this,img_src);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Can be assigned to a window control button to close the window
     * @param btn pointer to the control button on teh widows header
     * @param evet the event type
     */
    void closeEventCallBack(lv_event_t event)
    {
        lv_win_close_event_cb(this,event);
    }

    /**
     * Set the title of a window
     * @param win pointer to a window object
     * @param title string of the new title
     */
    void setTitle(const char * title)
    {
        lv_win_set_title(this,title);
    }

    /**
     * Set the control button size of a window
     * @param win pointer to a window object
     * @return control button size
     */
    void setBtnSize(lv_coord_t size)
    {
        lv_win_set_btn_size(this,size);
    }

    /**
     * Set the layout of the window
     * @param win pointer to a window object
     * @param layout the layout from 'lv_layout_t'
     */
    void setLayout(lv_layout_t layout)
    {
        lv_win_set_layout(this,layout);
    }

    /**
     * Set the scroll bar mode of a window
     * @param win pointer to a window object
     * @param sb_mode the new scroll bar mode from  'lv_sb_mode_t'
     */
    void setScrollBarMode(LVPage::Modes sb_mode)
    {
        lv_win_set_sb_mode(this,sb_mode);
    }

    /**
     * Set focus animation duration on `lv_win_focus()`
     * @param win pointer to a window object
     * @param anim_time duration of animation [ms]
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_win_set_anim_time(this,anim_time);
    }

    /**
     * Set a style of a window
     * @param win pointer to a window object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(Styles type, const LVStyle * style)
    {
        lv_win_set_style(this,type,style);
    }

    /**
     * Set drag status of a window. If set to 'true' window can be dragged like on a PC.
     * @param win pointer to a window object
     * @param en whether dragging is enabled
     */
    void setDrag(bool en)
    {
        lv_win_set_drag(this,en);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the title of a window
     * @param win pointer to a window object
     * @return title string of the window
     */
    const char * getTitle()
    {
        return lv_win_get_title(this);
    }

    /**
     * Get the content holder object of window (`lv_page`) to allow additional customization
     * @param win pointer to a window object
     * @return the Page object where the window's content is
     */
    lv_obj_t * getContent()
    {
        return lv_win_get_content(this);
    }

    /**
     * Get the control button size of a window
     * @param win pointer to a window object
     * @return control button size
     */
    lv_coord_t getBtnSize()
    {
        return lv_win_get_btn_size(this);
    }

    /**
     * Get the pointer of a widow from one of  its control button.
     * It is useful in the action of the control buttons where only button is known.
     * @param ctrl_btn pointer to a control button of a window
     * @return pointer to the window of 'ctrl_btn'
     */
    static LVWindow * getFromBtn(const lv_obj_t * ctrl_btn)
    {
        return (LVWindow *)lv_win_get_from_btn(ctrl_btn);
    }

    /**
     * Get the layout of a window
     * @param win pointer to a window object
     * @return the layout of the window (from 'lv_layout_t')
     */
    LVLayouts getLayout()
    {
        return (LVLayouts)lv_win_get_layout(this);
    }

    /**
     * Get the scroll bar mode of a window
     * @param win pointer to a window object
     * @return the scroll bar mode of the window (from 'lv_sb_mode_t')
     */
    LVPage::Modes getScrollBarMode()
    {
        return (LVPage::Modes)lv_win_get_sb_mode(this);
    }

    /**
     * Get focus animation duration
     * @param win pointer to a window object
     * @return duration of animation [ms]
     */
    uint16_t getAnimTime()
    {
        return lv_win_get_anim_time(this);
    }

    /**
     * Get width of the content area (page scrollable) of the window
     * @param win pointer to a window object
     * @return the width of the content area
     */
    lv_coord_t getWidth()
    {
        return lv_win_get_width(this);
    }

    /**
     * Get a style of a window
     * @param win pointer to a button object
     * @param type which style window be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_win_get_style(this,type);
    }

    /**
     * Get drag status of a window. If set to 'true' window can be dragged like on a PC.
     * @param win pointer to a window object
     * @return whether window is draggable
     */
    bool getDrag()
    {
        return lv_win_get_drag(this);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Focus on an object. It ensures that the object will be visible in the window.
     * @param win pointer to a window object
     * @param obj pointer to an object to focus (must be in the window)
     * @param anim_en LV_ANIM_ON focus with an animation; LV_ANIM_OFF focus without animation
     */
    void focus(lv_obj_t * obj, lv_anim_enable_t anim_en)
    {
        lv_win_focus(this,obj,anim_en);
    }

    /**
     * Scroll the window horizontally
     * @param win pointer to a window object
     * @param dist the distance to scroll (< 0: scroll right; > 0 scroll left)
     */
    void scrollHor(LVCoord dist)
    {
        lv_win_scroll_hor(this, dist);
    }

    /**
     * Scroll the window vertically
     * @param win pointer to a window object
     * @param dist the distance to scroll (< 0: scroll down; > 0 scroll up)
     */
    void scrollVer(LVCoord dist)
    {
        lv_win_scroll_ver(this, dist);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_WIN*/

#endif /*LVWINDOW_H*/
