/**
 * @file lv_kb.h
 *
 */

#ifndef LVKEYBOARD_H
#define LVKEYBOARD_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_kb.h>

#if LV_USE_KB != 0

#include "../LVCore/LVObject.h"
#include "LVTextArea.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/



/*Data of keyboard*/
class LVKeyBoard
        : public LVObject
        , public lv_kb_ext_t
{
    LV_OBJECT(LVKeyBoard,lv_kb_create,lv_kb_ext_t)
public:

    enum Styles : lv_kb_style_t
    {
        STYLE_BG          = LV_KB_STYLE_BG,
        STYLE_BTN_REL     = LV_KB_STYLE_BTN_REL,
        STYLE_BTN_PR      = LV_KB_STYLE_BTN_PR,
        STYLE_BTN_TGL_REL = LV_KB_STYLE_BTN_TGL_REL,
        STYLE_BTN_TGL_PR  = LV_KB_STYLE_BTN_TGL_PR,
        STYLE_BTN_INA     = LV_KB_STYLE_BTN_INA,
    };

    /** Current keyboard mode. */
    enum Modes : lv_kb_mode_t
    {
        MODE_TEXT = LV_KB_MODE_TEXT,
        MODE_NUM  = LV_KB_MODE_NUM,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a keyboard objects
     * @param par pointer to an object, it will be the parent of the new keyboard
     * @param copy pointer to a keyboard object, if not NULL then the new object will be copied from it
     * @return pointer to the created keyboard
     */
    //LVKeyBoard(LVObject * parent, const LVKeyBoard * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Assign a Text Area to the Keyboard. The pressed characters will be put there.
     * @param kb pointer to a Keyboard object
     * @param ta pointer to a Text Area object to write there
     */
    void setTextArea(LVTextArea * ta)
    {
        lv_kb_set_ta(this,ta);
    }

    /**
     * Set a new a mode (text or number map)
     * @param kb pointer to a Keyboard object
     * @param mode the mode from 'lv_kb_mode_t'
     */
    void setMode(Modes mode)
    {
        lv_kb_set_mode(this,mode);
    }

    /**
     * Automatically hide or show the cursor of the current Text Area
     * @param kb pointer to a Keyboard object
     * @param en true: show cursor on the current text area, false: hide cursor
     */
    void setCursorManage(bool en)
    {
        lv_kb_set_cursor_manage(this,en);
    }

    /**
     * Set a new map for the keyboard
     * @param kb pointer to a Keyboard object
     * @param map pointer to a string array to describe the map.
     *            See 'lv_btnm_set_map()' for more info.
     */
    void setMap(const char * map[])
    {
        lv_kb_set_map(this, map);
    }

    /**
     * Set the button control map (hidden, disabled etc.) for the keyboard. The
     * control map array will be copied and so may be deallocated after this
     * function returns.
     * @param kb pointer to a keyboard object
     * @param ctrl_map pointer to an array of `lv_btn_ctrl_t` control bytes.
     *                 See: `lv_btnm_set_ctrl_map` for more details.
     */
    void setCtrlMap(const lv_btnm_ctrl_t ctrl_map[])
    {
        lv_kb_set_ctrl_map(this, ctrl_map);
    }

    /**
     * Set a style of a keyboard
     * @param kb pointer to a keyboard object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_kb_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Assign a Text Area to the Keyboard. The pressed characters will be put there.
     * @param kb pointer to a Keyboard object
     * @return pointer to the assigned Text Area object
     */
    LVTextArea * getTextArea()
    {
        return (LVTextArea *)lv_kb_get_ta(this);
    }

    /**
     * Set a new a mode (text or number map)
     * @param kb pointer to a Keyboard object
     * @return the current mode from 'lv_kb_mode_t'
     */
    Modes getMode()
    {
        return (Modes)lv_kb_get_mode(this);
    }

    /**
     * Get the current cursor manage mode.
     * @param kb pointer to a Keyboard object
     * @return true: show cursor on the current text area, false: hide cursor
     */
    bool getCursorManage()
    {
        return lv_kb_get_cursor_manage(this);
    }

    /**
     * Get the current map of a keyboard
     * @param kb pointer to a keyboard object
     * @return the current map
     */
    const char ** getMapArray()
    {
        return lv_kb_get_map_array(this);
    }

    /**
     * Get a style of a keyboard
     * @param kb pointer to a keyboard object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_kb_get_style(this,type);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Default keyboard event to add characters to the Text area and change the map.
     * If a custom `event_cb` is added to the keyboard this function be called from it to handle the
     * button clicks
     * @param kb pointer to a  keyboard
     * @param event the triggering event
     */
    void defaultEventCallBack(EventType event)
    {
        lv_kb_def_event_cb(this,event);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_KB*/

#endif /*LVKEYBOARD_H*/
