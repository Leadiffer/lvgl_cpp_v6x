/**
 * @file lv_btnm.h
 *
 */

#ifndef LVBUTTONMATRIX_H
#define LVBUTTONMATRIX_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_btnm.h>

#if LV_USE_BTNM != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of button matrix*/
class LVButtonMatrix
        : public LVObject
        , public lv_btnm_ext_t
{
    LV_OBJECT(LVButtonMatrix,lv_btnm_create,lv_btnm_ext_t)

public:

    /** Type to store button control bits (disabled, hidden etc.) */
    enum ControlBits : lv_btnm_ctrl_t
    {
        CTRL_HIDDEN     = LV_BTNM_CTRL_HIDDEN     , /**< Button hidden */
        CTRL_NO_REPEAT  = LV_BTNM_CTRL_NO_REPEAT  , /**< Do not repeat press this button. */
        CTRL_INACTIVE   = LV_BTNM_CTRL_INACTIVE   , /**< Disable this button. */
        CTRL_TGL_ENABLE = LV_BTNM_CTRL_TGL_ENABLE , /**< Button *can* be toggled. */
        CTRL_TGL_STATE  = LV_BTNM_CTRL_TGL_STATE  , /**< Button is currently toggled (e.g. checked). */
        CTRL_CLICK_TRIG = LV_BTNM_CTRL_CLICK_TRIG , /**< 1: Send LV_EVENT_SELECTED on CLICK, 0: Send LV_EVENT_SELECTED on PRESS*/
    };

    enum Styles: lv_btnm_style_t
    {
        STYLE_BG          = LV_BTNM_STYLE_BG,
        STYLE_BTN_REL     = LV_BTNM_STYLE_BTN_REL,
        STYLE_BTN_PR      = LV_BTNM_STYLE_BTN_PR,
        STYLE_BTN_TGL_REL = LV_BTNM_STYLE_BTN_TGL_REL,
        STYLE_BTN_TGL_PR  = LV_BTNM_STYLE_BTN_TGL_PR,
        STYLE_BTN_INA     = LV_BTNM_STYLE_BTN_INA,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a button matrix objects
     * @param par pointer to an object, it will be the parent of the new button matrix
     * @param copy pointer to a button matrix object, if not NULL then the new object will be copied
     * from it
     * @return pointer to the created button matrix
     */
    //LVButtonMatrix(LVObject * parent, const LVButtonMatrix * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a new map. Buttons will be created/deleted according to the map. The
     * button matrix keeps a reference to the map and so the string array must not
     * be deallocated during the life of the matrix.
     * @param btnm pointer to a button matrix object
     * @param map pointer a string array. The last string has to be: "". Use "\n" to make a line break.
     */
    void setMap(const char * map[])
    {
        lv_btnm_set_map(this,map);
    }

    /**
     * Set the button control map (hidden, disabled etc.) for a button matrix. The
     * control map array will be copied and so may be deallocated after this
     * function returns.
     * @param btnm pointer to a button matrix object
     * @param ctrl_map pointer to an array of `lv_btn_ctrl_t` control bytes. The
     *                 length of the array and position of the elements must match
     *                 the number and order of the individual buttons (i.e. excludes
     *                 newline entries).
     *                 An element of the map should look like e.g.:
     *                 `ctrl_map[0] = width | LV_BTNM_CTRL_NO_REPEAT |  LV_BTNM_CTRL_TGL_ENABLE`
     */
    void setCtrlMap(const lv_btnm_ctrl_t ctrl_map[])
    {
        lv_btnm_set_ctrl_map(this,ctrl_map);
    }

    /**
     * Set the pressed button i.e. visually highlight it.
     * Mainly used a when the btnm is in a group to show the selected button
     * @param btnm pointer to button matrix object
     * @param id index of the currently pressed button (`LV_BTNM_BTN_NONE` to unpress)
     */
    void setPressed(uint16_t id)
    {
        lv_btnm_set_pressed(this,id);
    }

    /**
     * Set a style of a button matrix
     * @param btnm pointer to a button matrix object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_btnm_set_style(this,type,style);
    }

    /**
     * Enable recoloring of button's texts
     * @param btnm pointer to button matrix object
     * @param en true: enable recoloring; false: disable
     */
    void setRecolor(bool en)
    {
        lv_btnm_set_recolor(this,en);
    }

    /**
     * Set the attributes of a button of the button matrix
     * @param btnm pointer to button matrix object
     * @param btn_id 0 based index of the button to modify. (Not counting new lines)
     */
    void setButtonCtrl(uint16_t btn_id, lv_btnm_ctrl_t ctrl)
    {
        lv_btnm_set_btn_ctrl(this,btn_id,ctrl);
    }

    /**
     * Clear the attributes of a button of the button matrix
     * @param btnm pointer to button matrix object
     * @param btn_id 0 based index of the button to modify. (Not counting new lines)
     */
    void clearButtonCtrl(uint16_t btn_id, lv_btnm_ctrl_t ctrl)
    {
        lv_btnm_clear_btn_ctrl(this,btn_id,ctrl);
    }

    /**
     * Set the attributes of all buttons of a button matrix
     * @param btnm pointer to a button matrix object
     * @param ctrl attribute(s) to set from `lv_btnm_ctrl_t`. Values can be ORed.
     */
    void setButtonCtrlAll(lv_btnm_ctrl_t ctrl)
    {
        lv_btnm_set_btn_ctrl_all(this,ctrl);
    }

    /**
     * Clear the attributes of all buttons of a button matrix
     * @param btnm pointer to a button matrix object
     * @param ctrl attribute(s) to set from `lv_btnm_ctrl_t`. Values can be ORed.
     * @param en true: set the attributes; false: clear the attributes
     */
    void clearButtonCtrlAll(lv_btnm_ctrl_t ctrl)
    {
        lv_btnm_clear_btn_ctrl_all(this,ctrl);
    }

    /**
     * Set a single buttons relative width.
     * this method will cause the matrix be regenerated and is a relatively
     * expensive operation. It is recommended that initial width be specified using
     * `lv_btnm_set_ctrl_map` and this method only be used for dynamic changes.
     * @param btnm pointer to button matrix object
     * @param btn_id 0 based index of the button to modify.
     * @param width Relative width compared to the buttons in the same row. [1..7]
     */
    void setButtonWidth(uint16_t btn_id, uint8_t width)
    {
        lv_btnm_set_btn_width(this,btn_id,width);
    }

    /**
     * Make the button matrix like a selector widget (only one button may be toggled at a time).
     *
     * Toggling must be enabled on the buttons you want to be selected with `lv_btnm_set_ctrl` or
     * `lv_btnm_set_btn_ctrl_all`.
     *
     * @param btnm Button matrix object
     * @param one_toggle Whether "one toggle" mode is enabled
     */
    void setOneToggle(bool one_toggle)
    {
        lv_btnm_set_one_toggle(this , one_toggle);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the current map of a button matrix
     * @param btnm pointer to a button matrix object
     * @return the current map
     */
    const char ** getMapArray()
    {
        return lv_btnm_get_map_array(this);
    }

    /**
     * Check whether the button's text can use recolor or not
     * @param btnm pointer to button matrix object
     * @return true: text recolor enable; false: disabled
     */
    bool getRecolor()
    {
        return lv_btnm_get_recolor(this);
    }

    /**
     * Get the index of the lastly "activated" button by the user (pressed, released etc)
     * Useful in the the `event_cb` to get the text of the button, check if hidden etc.
     * @param btnm pointer to button matrix object
     * @return  index of the last released button (LV_BTNM_BTN_NONE: if unset)
     */
    uint16_t getActiveButton()
    {
        return lv_btnm_get_active_btn(this);
    }

    /**
     * Get the text of the lastly "activated" button by the user (pressed, released etc)
     * Useful in the the `event_cb`
     * @param btnm pointer to button matrix object
     * @return text of the last released button (NULL: if unset)
     */
    const char * getActiveButtonText()
    {
        return lv_btnm_get_active_btn_text(this);
    }

    /**
     * Get the pressed button's index.
     * The button be really pressed by the user or manually set to pressed with `lv_btnm_set_pressed`
     * @param btnm pointer to button matrix object
     * @return  index of the pressed button (LV_BTNM_BTN_NONE: if unset)
     */
    uint16_t getPressedButton()
    {
        return lv_btnm_get_pressed_btn(this);
    }

    /**
     * Get the button's text
     * @param btnm pointer to button matrix object
     * @param btn_id the index a button not counting new line characters. (The return value of
     * lv_btnm_get_pressed/released)
     * @return  text of btn_index` button
     */
    const char * getButtonText(uint16_t btn_id)
    {
        return lv_btnm_get_btn_text(this,btn_id);
    }

    /**
     * Get the whether a control value is enabled or disabled for button of a button matrix
     * @param btnm pointer to a button matrix object
     * @param btn_id the index a button not counting new line characters. (E.g. the return value of
     * lv_btnm_get_pressed/released)
     * @param ctrl control values to check (ORed value can be used)
     * @return true: long press repeat is disabled; false: long press repeat enabled
     */
    bool getButtonCtrl(uint16_t btn_id, lv_btnm_ctrl_t ctrl)
    {
        return lv_btnm_get_btn_ctrl(this,btn_id,ctrl);
    }

    /**
     * Get a style of a button matrix
     * @param btnm pointer to a button matrix object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(lv_btnm_style_t type)
    {
        return (const LVStyle *)lv_btnm_get_style(this,type);
    }

    /**
     * Find whether "one toggle" mode is enabled.
     * @param btnm Button matrix object
     * @return whether "one toggle" mode is enabled
     */
    bool getOneToggle()
    {
        return lv_btnm_get_one_toggle(this);
    }
    /**********************
     *      MACROS
     **********************/
};

#endif /*LV_USE_BTNM*/

#endif /*LVBUTTONMATRIX_H*/
