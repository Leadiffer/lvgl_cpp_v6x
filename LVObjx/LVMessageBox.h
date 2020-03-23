/**
 * @file lv_mbox.h
 *
 */

#ifndef LVMESSAGEBOX_H
#define LVMESSAGEBOX_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_mbox.h>

#if LV_USE_MBOX != 0

#include "../LVCore/LVObject.h"
#include "LVContainer.h"
#include "LVButtonMatrix.h"
#include "LVLabel.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of message box*/
class LVMessageBox
        : public LVObject
        , public lv_mbox_ext_t
{
    LV_OBJECT(LVMessageBox,lv_mbox_create,lv_mbox_ext_t)
public:

    /** Message box styles. */
    enum Styles : lv_mbox_style_t
    {
        STYLE_BG           = LV_MBOX_STYLE_BG,
        STYLE_BTN_BG       = LV_MBOX_STYLE_BTN_BG,      /**< Same meaning as ordinary button styles. */
        STYLE_BTN_REL      = LV_MBOX_STYLE_BTN_REL,
        STYLE_BTN_PR       = LV_MBOX_STYLE_BTN_PR,
        STYLE_BTN_TGL_REL  = LV_MBOX_STYLE_BTN_TGL_REL,
        STYLE_BTN_TGL_PR   = LV_MBOX_STYLE_BTN_TGL_PR,
        STYLE_BTN_INA      = LV_MBOX_STYLE_BTN_INA,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a message box objects
     * @param par pointer to an object, it will be the parent of the new message box
     * @param copy pointer to a message box object, if not NULL then the new object will be copied from
     * it
     * @return pointer to the created message box
     */
    //LVMessageBox(LVObject * parent, const LVMessageBox * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Add button to the message box
     * @param mbox pointer to message box object
     * @param btn_map button descriptor (button matrix map).
     *                E.g.  a const char *txt[] = {"ok", "close", ""} (Can not be local variable)
     */
    void addButtons(const char ** btn_mapaction)
    {
        lv_mbox_add_btns(this,btn_mapaction);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the text of the message box
     * @param mbox pointer to a message box
     * @param txt a '\0' terminated character string which will be the message box text
     */
    void setText(const char * txt)
    {
        lv_mbox_set_text(this,txt);
    }

    /**
     * Set animation duration
     * @param mbox pointer to a message box object
     * @param anim_time animation length in  milliseconds (0: no animation)
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_mbox_set_anim_time(this,anim_time);
    }

    /**
     * Automatically delete the message box after a given time
     * @param mbox pointer to a message box object
     * @param delay a time (in milliseconds) to wait before delete the message box
     */
    void startAutoClose(uint16_t delay)
    {
        lv_mbox_start_auto_close(this,delay);
    }

    /**
     * Stop the auto. closing of message box
     * @param mbox pointer to a message box object
     */
    void stopAutoClose()
    {
        lv_mbox_stop_auto_close(this);
    }

    /**
     * Set a style of a message box
     * @param mbox pointer to a message box object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_mbox_set_style(this,type,style);
    }

    /**
     * Set whether recoloring is enabled. Must be called after `lv_mbox_add_btns`.
     * @param btnm pointer to button matrix object
     * @param en whether recoloring is enabled
     */
    void setRecolor(bool en)
    {
        lv_mbox_set_recolor(this,en);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the text of the message box
     * @param mbox pointer to a message box object
     * @return pointer to the text of the message box
     */
    const char * getText()
    {
        return lv_mbox_get_text(this);
    }

    /**
     * Get the index of the lastly "activated" button by the user (pressed, released etc)
     * Useful in the the `event_cb`.
     * @param btnm pointer to button matrix object
     * @return  index of the last released button (LV_BTNM_BTN_NONE: if unset)
     */
    uint16_t getActiveBtn()
    {
        return lv_mbox_get_active_btn(this);
    }

    /**
     * Get the text of the lastly "activated" button by the user (pressed, released etc)
     * Useful in the the `event_cb`.
     * @param btnm pointer to button matrix object
     * @return text of the last released button (NULL: if unset)
     */
    const char * getActiveBtnText()
    {
        return lv_mbox_get_active_btn_text(this);
    }

    /**
     * Get the animation duration (close animation time)
     * @param mbox pointer to a message box object
     * @return animation length in  milliseconds (0: no animation)
     */
    uint16_t getAnimTime()
    {
        return lv_mbox_get_anim_time(this);
    }

    /**
     * Get a style of a message box
     * @param mbox pointer to a message box object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_mbox_get_style(this,type);
    }

    /**
     * Get whether recoloring is enabled
     * @param mbox pointer to a message box object
     * @return whether recoloring is enabled
     */
    bool getRecolor()
    {
        return lv_mbox_get_recolor(this);
    }

    /**
     * Get message box button matrix
     * @param mbox pointer to a message box object
     * @return pointer to button matrix object
     * @remarks return value will be NULL unless `lv_mbox_add_btns` has been already called
     */
    lv_obj_t * getButtonMatrix()
    {
        return lv_mbox_get_btnm(this);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_MBOX*/

#endif /*LVMESSAGEBOX_H*/
