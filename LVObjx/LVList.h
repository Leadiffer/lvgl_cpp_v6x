/**
 * @file lv_list.h
 *
 */

#ifndef LVLIST_H
#define LVLIST_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_list.h>

#if LV_USE_LIST != 0

#include "../LVCore/LVObject.h"
#include "LVButton.h"
#include "LVPage.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of list*/
class LVList
        : public LVObject
        , public LVFakeMemHeader<lv_list_ext_t>
        , public lv_list_ext_t
{
    LV_OBJECT(LVList,lv_list_create,lv_list_ext_t)
public:

    /** List styles. */
    enum Styles : lv_list_style_t
    {
        STYLE_BG           = LV_LIST_STYLE_BG,         /**< List background style */
        STYLE_SCRL         = LV_LIST_STYLE_SCRL,       /**< List scrollable area style. */
        STYLE_SB           = LV_LIST_STYLE_SB,         /**< List scrollbar style. */
        STYLE_EDGE_FLASH   = LV_LIST_STYLE_EDGE_FLASH, /**< List edge flash style. */
        STYLE_BTN_REL      = LV_LIST_STYLE_BTN_REL,    /**< Same meaning as the ordinary button styles. */
        STYLE_BTN_PR       = LV_LIST_STYLE_BTN_PR,
        STYLE_BTN_TGL_REL  = LV_LIST_STYLE_BTN_TGL_REL,
        STYLE_BTN_TGL_PR   = LV_LIST_STYLE_BTN_TGL_PR,
        STYLE_BTN_INA      = LV_LIST_STYLE_BTN_INA,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a list objects
     * @param par pointer to an object, it will be the parent of the new list
     * @param copy pointer to a list object, if not NULL then the new object will be copied from it
     * @return pointer to the created list
     */
    //LVList(LVObject * parent, const LVList * copy);

    /**
     * Delete all children of the scrl object, without deleting scrl child.
     * @param obj pointer to an object
     */
    void clean()
    {
        lv_list_clean(this);
    }

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Add a list element to the list
     * @param list pointer to list object
     * @param img_fn file name of an image before the text (NULL if unused)
     * @param txt text of the list element (NULL if unused)
     * @return pointer to the new list element which can be customized (a button)
     */
    lv_obj_t * addButton(const void * img_src, const char * txt)
    {
        return lv_list_add_btn(this,img_src,txt);
    }

    /**
     * Remove the index of the button in the list
     * @param list pointer to a list object
     * @param index pointer to a the button's index in the list, index must be 0 <= index <
     * lv_list_ext_t.size
     * @return true: successfully deleted
     */
    bool remove(uint16_t index)
    {
        return lv_list_remove(this,index);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set single button selected mode, only one button will be selected if enabled.
     * @param list pointer to the currently pressed list object
     * @param mode enable(true)/disable(false) single selected mode.
     */
    void setSingleMode(bool mode)
    {
        lv_list_set_single_mode(this,mode);
    }

    #if LV_USE_GROUP

    /**
     * Make a button selected
     * @param list pointer to a list object
     * @param btn pointer to a button to select
     *            NULL to not select any buttons
     */
    void setBtnSelected(lv_obj_t * btn)
    {
        lv_list_set_btn_selected(this,btn);
    }
    #endif

    /**
     * Set the scroll bar mode of a list
     * @param list pointer to a list object
     * @param sb_mode the new mode from 'lv_page_sb_mode_t' enum
     */
    void setScrollBarMode(LVPage::Modes mode)
    {
        lv_page_set_sb_mode(this, mode);
    }

    /**
     * Enable the scroll propagation feature. If enabled then the List will move its parent if there is
     * no more space to scroll.
     * @param list pointer to a List
     * @param en true or false to enable/disable scroll propagation
     */
    void setScrollPropagation(bool en)
    {
        lv_list_set_scroll_propagation(this, en);
    }

    /**
     * Enable the edge flash effect. (Show an arc when the an edge is reached)
     * @param list pointer to a List
     * @param en true or false to enable/disable end flash
     */
    void setEdgeFlash(bool en)
    {
        lv_list_set_edge_flash(this, en);
    }

    /**
     * Set scroll animation duration on 'list_up()' 'list_down()' 'list_focus()'
     * @param list pointer to a list object
     * @param anim_time duration of animation [ms]
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_list_set_anim_time(this, anim_time);
    }

    /**
     * Set a style of a list
     * @param list pointer to a list object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(Styles type, const LVStyle * style)
    {
        lv_list_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get single button selected mode.
     * @param list pointer to the currently pressed list object.
     */
    bool getSingleMode()
    {
        return lv_list_get_single_mode(this);
    }

    /**
     * Get the text of a list element
     * @param btn pointer to list element
     * @return pointer to the text
     */
    static const char * getBtnText(const lv_obj_t * btn)
    {
        return lv_list_get_btn_text(btn);
    }
    /**
     * Get the label object from a list element
     * @param btn pointer to a list element (button)
     * @return pointer to the label from the list element or NULL if not found
     */
    static lv_obj_t * getBtnLabel(const lv_obj_t * btn)
    {
        return lv_list_get_btn_label(btn);
    }

    /**
     * Get the image object from a list element
     * @param btn pointer to a list element (button)
     * @return pointer to the image from the list element or NULL if not found
     */
    static lv_obj_t * getBtnImg(const lv_obj_t * btn)
    {
        return lv_list_get_btn_img(btn);
    }

    /**
     * Get the next button from list. (Starts from the bottom button)
     * @param list pointer to a list object
     * @param prev_btn pointer to button. Search the next after it.
     * @return pointer to the next button or NULL when no more buttons
     */
    lv_obj_t * getPrevBtn(lv_obj_t * prev_btn)
    {
        return lv_list_get_prev_btn(this,prev_btn);
    }

    /**
     * Get the previous button from list. (Starts from the top button)
     * @param list pointer to a list object
     * @param prev_btn pointer to button. Search the previous before it.
     * @return pointer to the previous button or NULL when no more buttons
     */
    lv_obj_t * getNextBtn(lv_obj_t * prev_btn)
    {
        return lv_list_get_next_btn(this,prev_btn);
    }

    /**
     * Get the index of the button in the list
     * @param list pointer to a list object. If NULL, assumes btn is part of a list.
     * @param btn pointer to a list element (button)
     * @return the index of the button in the list, or -1 of the button not in this list
     */
    int32_t getBtnIndex(const lv_obj_t * btn)
    {
        return lv_list_get_btn_index(this,btn);
    }

    /**
     * Get the number of buttons in the list
     * @param list pointer to a list object
     * @return the number of buttons in the list
     */
    uint16_t getSize()
    {
        return lv_list_get_size(this);
    }

    #if LV_USE_GROUP
    /**
     * Get the currently selected button. Can be used while navigating in the list with a keypad.
     * @param list pointer to a list object
     * @return pointer to the selected button
     */
    lv_obj_t * getBtnSelected()
    {
        return lv_list_get_btn_selected(this);
    }
    #endif

    /**
     * Get the scroll bar mode of a list
     * @param list pointer to a list object
     * @return scrollbar mode from 'lv_page_sb_mode_t' enum
     */
    LVPage::Modes getScrollBarMode()
    {
        return (LVPage::Modes)lv_list_get_sb_mode(this);
    }

    /**
     * Get the scroll propagation property
     * @param list pointer to a List
     * @return true or false
     */
    bool getScrollPropagation()
    {
        return lv_list_get_scroll_propagation(this);
    }

    /**
     * Get the scroll propagation property
     * @param list pointer to a List
     * @return true or false
     */
    bool getEdgeFlash()
    {
        return lv_list_get_edge_flash(this);
    }

    /**
     * Get scroll animation duration
     * @param list pointer to a list object
     * @return duration of animation [ms]
     */
    uint16_t getAnimTime()
    {
        return lv_list_get_anim_time(this);
    }

    /**
     * Get a style of a list
     * @param list pointer to a list object
     * @param type which style should be get
     * @return style pointer to a style
     *  */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle*)lv_list_get_style(this,type);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Move the list elements up by one
     * @param list pointer a to list object
     */
    void up()
    {
        lv_list_up(this);
    }
    /**
     * Move the list elements down by one
     * @param list pointer to a list object
     */
    void down()
    {
        lv_list_down(this);
    }

    /**
     * Focus on a list button. It ensures that the button will be visible on the list.
     * @param btn pointer to a list button to focus
     * @param anim LV_ANOM_ON: scroll with animation, LV_ANIM_OFF: without animation
     */
    static void focus(const lv_obj_t * btn, lv_anim_enable_t anim)
    {
        lv_list_focus(btn,anim);
    }

    /**********************
     *      MACROS
     **********************/

};

#endif /*LV_USE_LIST*/

#endif /*LVLIST_H*/
