/**
 * @file lv_imgbtn.h
 *
 */

#ifndef LV_IMAGEBUTTON_H
#define LV_IMAGEBUTTON_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_imgbtn.h>

#if LV_USE_IMGBTN != 0

#include "../LVCore/LVObject.h"
#include "LVButton.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of image button*/
class LVImageButton
        : public LVObject
        , public LVFakeMemHeader<lv_imgbtn_ext_t>
        , public lv_imgbtn_ext_t
{
    LV_OBJECT(LVImageButton,lv_imgbtn_create,lv_imgbtn_ext_t)
public:

    /*Styles*/
    enum Styles : lv_imgbtn_style_t
    {
        STYLE_REL      = LV_IMGBTN_STYLE_REL, /**< Same meaning as ordinary button styles. */
        STYLE_PR       = LV_IMGBTN_STYLE_PR,
        STYLE_TGL_REL  = LV_IMGBTN_STYLE_TGL_REL,
        STYLE_TGL_PR   = LV_IMGBTN_STYLE_TGL_PR,
        STYLE_INA      = LV_IMGBTN_STYLE_INA,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a image button objects
     * @param par pointer to an object, it will be the parent of the new image button
     * @param copy pointer to a image button object, if not NULL then the new object will be copied from
     * it
     * @return pointer to the created image button
     */
    //LVImageButton(LVObject * parent, const LVImageButton * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /*=====================
     * Setter functions
     *====================*/

    #if LV_IMGBTN_TILED == 0
    /**
     * Set images for a state of the image button
     * @param imgbtn pointer to an image button object
     * @param state for which state set the new image (from `lv_btn_state_t`) `
     * @param src pointer to an image source (a C array or path to a file)
     */
    void setSrc(LVButton::States state, const void * src)
    {
        lv_imgbtn_set_src(this,state,src)
    }
    #else
    /**
     * Set images for a state of the image button
     * @param imgbtn pointer to an image button object
     * @param state for which state set the new image (from `lv_btn_state_t`) `
     * @param src_left pointer to an image source for the left side of the button (a C array or path to
     * a file)
     * @param src_mid pointer to an image source for the middle of the button (ideally 1px wide) (a C
     * array or path to a file)
     * @param src_right pointer to an image source for the right side of the button (a C array or path
     * to a file)
     */
    void setSrc(LVButton::States state, const void * src_left, const void * src_mid,
                           const void * src_right)
    {
        lv_imgbtn_set_src(this,state,src_left,src_mid,src_right);
    }

    #endif

    /**
     * Enable the toggled states. On release the button will change from/to toggled state.
     * @param imgbtn pointer to an image button object
     * @param tgl true: enable toggled states, false: disable
     */
    void setToggle(bool tgl)
    {
        lv_imgbtn_set_toggle(this, tgl);
    }

    /**
     * Set the state of the image button
     * @param imgbtn pointer to an image button object
     * @param state the new state of the button (from lv_btn_state_t enum)
     */
    void setState(LVButton::States state)
    {
        lv_imgbtn_set_state(this, state);
    }

    /**
     * Toggle the state of the image button (ON->OFF, OFF->ON)
     * @param imgbtn pointer to a image button object
     */
    void toggle()
    {
        lv_imgbtn_toggle(this);
    }

    /**
     * Set a style of a image button.
     * @param imgbtn pointer to image button object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(lv_imgbtn_style_t type, const lv_style_t * style)
    {
        lv_imgbtn_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    #if LV_IMGBTN_TILED == 0
    /**
     * Get the images in a  given state
     * @param imgbtn pointer to an image button object
     * @param state the state where to get the image (from `lv_btn_state_t`) `
     * @return pointer to an image source (a C array or path to a file)
     */
    const void * getSrc(LVButton::States state)
    {
        return lv_imgbtn_get_src(this,state);
    }

    #else

    /**
     * Get the left image in a given state
     * @param imgbtn pointer to an image button object
     * @param state the state where to get the image (from `lv_btn_state_t`) `
     * @return pointer to the left image source (a C array or path to a file)
     */
    const void * getSrcLeft(lv_btn_state_t state)
    {
        return lv_imgbtn_get_src_left(this,state);
    }

    /**
     * Get the middle image in a given state
     * @param imgbtn pointer to an image button object
     * @param state the state where to get the image (from `lv_btn_state_t`) `
     * @return pointer to the middle image source (a C array or path to a file)
     */
    const void * getSrcMiddle(lv_btn_state_t state)
    {
        return lv_imgbtn_get_src_middle(this,state);
    }

    /**
     * Get the right image in a given state
     * @param imgbtn pointer to an image button object
     * @param state the state where to get the image (from `lv_btn_state_t`) `
     * @return pointer to the left image source (a C array or path to a file)
     */
    const void * getSrcRight(lv_btn_state_t state)
    {
        return lv_imgbtn_get_src_right(this,state);
    }

    #endif
    /**
     * Get the current state of the image button
     * @param imgbtn pointer to a image button object
     * @return the state of the button (from lv_btn_state_t enum)
     */
    LVButton::States getState()
    {
        return (LVButton::States)lv_imgbtn_get_state(this);
    }

    /**
     * Get the toggle enable attribute of the image button
     * @param imgbtn pointer to a image button object
     * @return ture: toggle enabled, false: disabled
     */
    bool getToggle()
    {
        return lv_imgbtn_get_toggle(this);
    }

    /**
     * Get style of a image button.
     * @param imgbtn pointer to image button object
     * @param type which style should be get
     * @return style pointer to the style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_imgbtn_get_style(this,type);
    }

};

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_IMGBTN*/

#endif /*LV_IMAGEBUTTON_H*/
