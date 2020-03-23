/**
 * @file lv_tabview.h
 *
 */

#ifndef LVTABVIEW_H
#define LVTABVIEW_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_tabview.h>

#if LV_USE_TABVIEW != 0

#include "../LVCore/LVObject.h"
#include "LVPage.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of tab*/
class LVTabView
        : public LVObject
        , public lv_tabview_ext_t
{
    LV_OBJECT(LVTabView,lv_tabview_create,lv_tabview_ext_t)
public:

    enum Styles : lv_tabview_style_t
    {
        STYLE_BG           = LV_TABVIEW_STYLE_BG,
        STYLE_INDIC        = LV_TABVIEW_STYLE_INDIC,
        STYLE_BTN_BG       = LV_TABVIEW_STYLE_BTN_BG,
        STYLE_BTN_REL      = LV_TABVIEW_STYLE_BTN_REL,
        STYLE_BTN_PR       = LV_TABVIEW_STYLE_BTN_PR,
        STYLE_BTN_TGL_REL  = LV_TABVIEW_STYLE_BTN_TGL_REL,
        STYLE_BTN_TGL_PR   = LV_TABVIEW_STYLE_BTN_TGL_PR,
    };

    /** Position of tabview buttons. */
    enum BtnsPos : lv_tabview_btns_pos_t
    {
        BTNS_POS_TOP     = LV_TABVIEW_BTNS_POS_TOP,
        BTNS_POS_BOTTOM  = LV_TABVIEW_BTNS_POS_BOTTOM,
        BTNS_POS_LEFT    = LV_TABVIEW_BTNS_POS_LEFT,
        BTNS_POS_RIGHT   = LV_TABVIEW_BTNS_POS_RIGHT
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a Tab view object
     * @param par pointer to an object, it will be the parent of the new tab
     * @param copy pointer to a tab object, if not NULL then the new object will be copied from it
     * @return pointer to the created tab
     */
    //LVTabView(LVObject * par, const LVTabView * copy);

    /**
     * Delete all children of the scrl object, without deleting scrl child.
     * @param obj pointer to an object
     */
    void clean()
    {
        lv_tabview_clean(this);
    }

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Add a new tab with the given name
     * @param tabview pointer to Tab view object where to ass the new tab
     * @param name the text on the tab button
     * @return pointer to the created page object (lv_page). You can create your content here
     */
    lv_obj_t * addTab(const char * name)
    {
        return lv_tabview_add_tab(this,name);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a new tab
     * @param tabview pointer to Tab view object
     * @param id index of a tab to load
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     */
    void setTabAct(uint16_t id, lv_anim_enable_t anim = LV_ANIM_OFF)
    {
        lv_tabview_set_tab_act(this,id,anim);
    }

    /**
     * Enable horizontal sliding with touch pad
     * @param tabview pointer to Tab view object
     * @param en true: enable sliding; false: disable sliding
     */
    void setSliding(bool en)
    {
        lv_tabview_set_sliding(this,en);
    }

    /**
     * Set the animation time of tab view when a new tab is loaded
     * @param tabview pointer to Tab view object
     * @param anim_time time of animation in milliseconds
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_tabview_set_anim_time(this,anim_time);
    }

    /**
     * Set the style of a tab view
     * @param tabview pointer to a tan view object
     * @param type which style should be set
     * @param style pointer to the new style
     */
    void setStyle(const lv_style_t * style,Styles type)
    {
        lv_tabview_set_style(this,type,style);
    }

    /**
     * Set the position of tab select buttons
     * @param tabview pointer to a tab view object
     * @param btns_pos which button position
     */
    void setBtnsPos(BtnsPos btns_pos)
    {
        lv_tabview_set_btns_pos(this,btns_pos);
    }

    /**
     * Set whether tab buttons are hidden
     * @param tabview pointer to a tab view object
     * @param en whether tab buttons are hidden
     */
    void setBtnsHidden(bool en)
    {
        lv_tabview_set_btns_hidden(this,en);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the index of the currently active tab
     * @param tabview pointer to Tab view object
     * @return the active tab index
     */
    uint16_t getTabAct()
    {
        return lv_tabview_get_tab_act(this);
    }

    /**
     * Get the number of tabs
     * @param tabview pointer to Tab view object
     * @return tab count
     */
    uint16_t getTabCount()
    {
        return lv_tabview_get_tab_count(this);
    }

    /**
     * Get the page (content area) of a tab
     * @param tabview pointer to Tab view object
     * @param id index of the tab (>= 0)
     * @return pointer to page (lv_page) object
     */
    lv_obj_t * getTab(uint16_t id)
    {
        return lv_tabview_get_tab(this,id);
    }

    /**
     * Get horizontal sliding is enabled or not
     * @param tabview pointer to Tab view object
     * @return true: enable sliding; false: disable sliding
     */
    bool getSliding()
    {
        return lv_tabview_get_sliding(this);
    }

    /**
     * Get the animation time of tab view when a new tab is loaded
     * @param tabview pointer to Tab view object
     * @return time of animation in milliseconds
     */
    uint16_t getAnimTime()
    {
        return lv_tabview_get_anim_time(this);
    }

    /**
     * Get a style of a tab view
     * @param tabview pointer to a ab view object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_tabview_get_style(this,type);
    }

    /**
     * Get position of tab select buttons
     * @param tabview pointer to a ab view object
     */
    BtnsPos getBtnsPos()
    {
        return (BtnsPos)lv_tabview_get_btns_pos(this);
    }

    /**
     * Get whether tab buttons are hidden
     * @param tabview pointer to a tab view object
     * @return whether tab buttons are hidden
     */
    bool getBtnsHidden()
    {
        return lv_tabview_get_btns_hidden(this);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TABVIEW*/

#endif /*LVTABVIEW_H*/
