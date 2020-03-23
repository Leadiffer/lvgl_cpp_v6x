/**
 * @file lv_btn.h
 *
 */

#ifndef LVBTN_H
#define LVBTN_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_btn.h>

#if LV_USE_BTN != 0

#include "../LVCore/LVObject.h"
#include "LVContainer.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVButton
        : public LVObject
        , public lv_btn_ext_t
{
    LV_OBJECT(LVButton,lv_btn_create,lv_btn_ext_t)
public:

    /** Possible states of a button.
     * It can be used not only by buttons but other button-like objects too*/
    enum States : lv_btn_state_t
    {
        /**Released*/
        STATE_REL      = LV_BTN_STATE_REL,

        /**Pressed*/
        STATE_PR       = LV_BTN_STATE_PR,

        /**Toggled released*/
        STATE_TGL_REL  = LV_BTN_STATE_TGL_REL,

        /**Toggled pressed*/
        STATE_TGL_PR   = LV_BTN_STATE_TGL_PR,

        /**Inactive*/
        STATE_INA      = LV_BTN_STATE_INA,

        /**Number of states*/
        _STATE_NUM     = _LV_BTN_STATE_NUM,
    };


    /**Styles*/
    enum Styles : lv_btn_style_t
    {
        /** Release style */
        STYLE_REL           = LV_BTN_STYLE_REL,

        /**Pressed style*/
        STYLE_PR            = LV_BTN_STYLE_PR,

        /** Toggle released style*/
        STYLE_TGL_REL       = LV_BTN_STYLE_TGL_REL,

        /** Toggle pressed style */
        STYLE_TGL_PR        = LV_BTN_STYLE_TGL_PR,

        /** Inactive style*/
        STYLE_INA           = LV_BTN_STYLE_INA,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a button objects
     * @param par pointer to an object, it will be the parent of the new button
     * @param copy pointer to a button object, if not NULL then the new object will be copied from it
     * @return pointer to the created button
     */
    //LVButton(LVObject * parent, const LVButton * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Enable the toggled states. On release the button will change from/to toggled state.
     * @param btn pointer to a button object
     * @param tgl true: enable toggled states, false: disable
     */
    void setToggleEnable(bool tgl)
    {
        lv_btn_set_toggle(this,tgl);
    }

    /**
     * Set the state of the button
     * @param btn pointer to a button object
     * @param state the new state of the button (from lv_btn_state_t enum)
     */
    void setState(States state)
    {
        lv_btn_set_state(this,state);
    }

    /**
     * Toggle the state of the button (ON->OFF, OFF->ON)
     * @param btn pointer to a button object
     */
    void toggle()
    {
        lv_btn_toggle(this);
    }

    /**
     * Set the layout on a button
     * @param btn pointer to a button object
     * @param layout a layout from 'lv_cont_layout_t'
     */
    void setLayout( LVLayouts layout)
    {
        lv_btn_set_layout(this, layout);
    }

    /**
     * Set the fit policy in all 4 directions separately.
     * It tell how to change the button size automatically.
     * @param btn pointer to a button object
     * @param left left fit policy from `lv_fit_t`
     * @param right right fit policy from `lv_fit_t`
     * @param top bottom fit policy from `lv_fit_t`
     * @param bottom bottom fit policy from `lv_fit_t`
     */
    void setFit(LVFits left, LVFits right, LVFits top, LVFits bottom)
    {
        lv_cont_set_fit4(this, left, right, top, bottom);
    }

    /**
     * Set the fit policy horizontally and vertically separately.
     * It tell how to change the button size automatically.
     * @param btn pointer to a button object
     * @param hot horizontal fit policy from `lv_fit_t`
     * @param ver vertical fit policy from `lv_fit_t`
     */
    void setFit(LVFits hor, LVFits ver)
    {
        lv_cont_set_fit2(this, hor, ver);
    }

    /**
     * Set the fit policy in all 4 direction at once.
     * It tell how to change the button size automatically.
     * @param btn pointer to a button object
     * @param fit fit policy from `lv_fit_t`
     */
    void setFit(LVFits fit)
    {
        lv_cont_set_fit(this, fit);
    }

    /**
     * Set time of the ink effect (draw a circle on click to animate in the new state)
     * @param btn pointer to a button object
     * @param time the time of the ink animation
     */
    void setInkInTime(uint16_t time)
    {
        lv_btn_set_ink_in_time(this,time);
    }

    /**
     * Set the wait time before the ink disappears
     * @param btn pointer to a button object
     * @param time the time of the ink animation
     */
    void setInkWaitTime(uint16_t time)
    {
        lv_btn_set_ink_wait_time(this,time);
    }

    /**
     * Set time of the ink out effect (animate to the released state)
     * @param btn pointer to a button object
     * @param time the time of the ink animation
     */
    void setInkOutTime(uint16_t time)
    {
        lv_btn_set_ink_out_time(this,time);
    }

    /**
     * Set a style of a button.
     * @param btn pointer to button object
     * @param type which style should be set
     * @param style pointer to a style
     *  */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_btn_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the current state of the button
     * @param btn pointer to a button object
     * @return the state of the button (from lv_btn_state_t enum)
     */
    States getState()
    {
        return (States)lv_btn_get_state(this);
    }

    /**
     * Get the toggle enable attribute of the button
     * @param btn pointer to a button object
     * @return ture: toggle enabled, false: disabled
     */
    bool getToggle()
    {
        return lv_btn_get_toggle(this);
    }

    /**
     * Get the layout of a button
     * @param btn pointer to button object
     * @return the layout from 'lv_cont_layout_t'
     */
    LVLayouts getLayout()
    {
        return (LVLayouts)lv_cont_get_layout(this);
    }

    /**
     * Get the left fit mode
     * @param btn pointer to a button object
     * @return an element of `lv_fit_t`
     */
    LVFits getFitLeft()
    {
        return (LVFits)lv_cont_get_fit_left(this);
    }

    /**
     * Get the right fit mode
     * @param btn pointer to a button object
     * @return an element of `lv_fit_t`
     */
    LVFits getFitRight()
    {
        return (LVFits)lv_cont_get_fit_right(this);
    }

    /**
     * Get the top fit mode
     * @param btn pointer to a button object
     * @return an element of `lv_fit_t`
     */
    LVFits getFitTop()
    {
        return (LVFits)lv_cont_get_fit_top(this);
    }

    /**
     * Get the bottom fit mode
     * @param btn pointer to a button object
     * @return an element of `lv_fit_t`
     */
    LVFits getFitBottom()
    {
        return (LVFits)lv_cont_get_fit_bottom(this);
    }

    /**
     * Get time of the ink in effect (draw a circle on click to animate in the new state)
     * @param btn pointer to a button object
     * @return the time of the ink animation
     */
    uint16_t getInkInTime()
    {
        return lv_btn_get_ink_in_time(this);
    }

    /**
     * Get the wait time before the ink disappears
     * @param btn pointer to a button object
     * @return the time of the ink animation
     */
    uint16_t getInkWaitTime()
    {
        return lv_btn_get_ink_wait_time(this);
    }

    /**
     * Get time of the ink out effect (animate to the releases state)
     * @param btn pointer to a button object
     * @return the time of the ink animation
     */
    uint16_t getInkOutTime()
    {
        return lv_btn_get_ink_out_time(this);
    }

    /**
     * Get style of a button.
     * @param btn pointer to button object
     * @param type which style should be get
     * @return style pointer to the style
     *  */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_btn_get_style(this,type);
    }
};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_BUTTON*/

#endif /*LVBTN_H*/
