/**
 * @file lv_cb.h
 *
 */

#ifndef LVCHECKBOX_H
#define LVCHECKBOX_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_cb.h>

#if LV_USE_CB != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of check box*/
class LVCheckBox
        : public LVObject
        , public lv_cb_ext_t
{
    LV_OBJECT(LVCheckBox,lv_cb_create,lv_cb_ext_t)
public:

    /** Checkbox styles. */
    enum Styles : lv_cb_style_t
    {
        STYLE_BG          = LV_CB_STYLE_BG,         /**< Style of object background. */
        STYLE_BOX_REL     = LV_CB_STYLE_BOX_REL,    /**< Style of box (released). */
        STYLE_BOX_PR      = LV_CB_STYLE_BOX_PR,     /**< Style of box (pressed). */
        STYLE_BOX_TGL_REL = LV_CB_STYLE_BOX_TGL_REL,/**< Style of box (released but checked). */
        STYLE_BOX_TGL_PR  = LV_CB_STYLE_BOX_TGL_PR, /**< Style of box (pressed and checked). */
        STYLE_BOX_INA     = LV_CB_STYLE_BOX_INA,    /**< Style of disabled box */
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a check box objects
     * @param par pointer to an object, it will be the parent of the new check box
     * @param copy pointer to a check box object, if not NULL then the new object will be copied from it
     * @return pointer to the created check box
     */
    //LVCheckBox(LVObject * parent, const LVCheckBox * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the text of a check box. `txt` will be copied and may be deallocated
     * after this function returns.
     * @param cb pointer to a check box
     * @param txt the text of the check box. NULL to refresh with the current text.
     */
    void setText(const char * txt)
    {
        lv_cb_set_text(this,txt);
    }

    /**
     * Set the text of a check box. `txt` must not be deallocated during the life
     * of this checkbox.
     * @param cb pointer to a check box
     * @param txt the text of the check box. NULL to refresh with the current text.
     */
    void setStaticText(const char * txt)
    {
        lv_cb_set_static_text(this,txt);
    }

    /**
     * Set the state of the check box
     * @param cb pointer to a check box object
     * @param checked true: make the check box checked; false: make it unchecked
     */
    void setChecked(bool checked)
    {
        lv_cb_set_checked(this, checked);
    }

    /**
     * Make the check box inactive (disabled)
     * @param cb pointer to a check box object
     */
    void setInactive()
    {
        lv_cb_set_inactive(this);
    }

    /**
     * Set a style of a check box
     * @param cb pointer to check box object
     * @param type which style should be set
     * @param style pointer to a style
     *  */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_cb_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the text of a check box
     * @param cb pointer to check box object
     * @return pointer to the text of the check box
     */
    const char * getText()
    {
        return lv_cb_get_text(this);
    }

    /**
     * Get the current state of the check box
     * @param cb pointer to a check box object
     * @return true: checked; false: not checked
     */
    bool is_checked()
    {
        return lv_cb_is_checked(this);
    }

    /**
     * Get whether the check box is inactive or not.
     * @param cb pointer to a check box object
     * @return true: inactive; false: not inactive
     */
    bool isInactive()
    {
        return lv_cb_is_inactive(this);
    }

    /**
     * Get a style of a button
     * @param cb pointer to check box object
     * @param type which style should be get
     * @return style pointer to the style
     *  */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_cb_get_style(this,type);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CB*/

#endif /*LVCHECKBOX_H*/
