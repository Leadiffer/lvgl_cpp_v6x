/**
 * @file lv_page.h
 *
 */

#ifndef LVPAGE_H
#define LVPAGE_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_page.h>

#if LV_USE_PAGE != 0

#include "../LVCore/LVObject.h"
#include "LVContainer.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
class LVPage
        : public LVObject
        , public lv_page_ext_t
{
    LV_OBJECT(LVPage,lv_page_create,lv_page_ext_t)
public:

    /** Scrollbar modes: shows when should the scrollbars be visible*/
    enum SBModes : lv_sb_mode_t
    {
        SB_MODE_OFF    = LV_SB_MODE_OFF   , /**< Never show scrollbars*/
        SB_MODE_ON     = LV_SB_MODE_ON    , /**< Always show scrollbars*/
        SB_MODE_DRAG   = LV_SB_MODE_DRAG  , /**< Show scrollbars when page is being dragged*/
        SB_MODE_AUTO   = LV_SB_MODE_AUTO  , /**< Show scrollbars when the scrollable container is large enough to be scrolled*/
        SB_MODE_HIDE   = LV_SB_MODE_HIDE  , /**< Hide the scroll bar temporally*/
        SB_MODE_UNHIDE = LV_SB_MODE_UNHIDE, /**< Unhide the previously hidden scrollbar. Recover it's type too*/
    };

    /** Edges: describes the four edges of the page*/
    enum Edges : lv_page_edge_t
    {
        EDGE_LEFT   = LV_PAGE_EDGE_LEFT  ,
        EDGE_TOP    = LV_PAGE_EDGE_TOP   ,
        EDGE_RIGHT  = LV_PAGE_EDGE_RIGHT ,
        EDGE_BOTTOM = LV_PAGE_EDGE_BOTTOM
    };

    enum Styles : lv_page_style_t
    {
        STYLE_BG         = LV_PAGE_STYLE_BG,
        STYLE_SCRL       = LV_PAGE_STYLE_SCRL,
        STYLE_SB         = LV_PAGE_STYLE_SB,
        STYLE_EDGE_FLASH = LV_PAGE_STYLE_EDGE_FLASH,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a page objects
     * @param par pointer to an object, it will be the parent of the new page
     * @param copy pointer to a page object, if not NULL then the new object will be copied from it
     * @return pointer to the created page
     */
    //LVPage(LVObject * parent, const LVPage * copy);

    /**
     * Delete all children of the scrl object, without deleting scrl child.
     * @param obj pointer to an object
     */
    void clean()
    {
        lv_page_clean(this);
    }

    /**
     * Get the scrollable object of a page
     * @param page pointer to a page object
     * @return pointer to a container which is the scrollable part of the page
     */
    LVContainer * get_scrl()
    {
        return (LVContainer *)lv_page_get_scrl(this);
    }

    /**
     * Get the animation time
     * @param page pointer to a page object
     * @return the animation time in milliseconds
     */
    uint16_t getAnimTime()
    {
        return lv_page_get_anim_time(this);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the scroll bar mode on a page
     * @param page pointer to a page object
     * @param sb_mode the new mode from 'lv_page_sb.mode_t' enum
     */
    void setScrollBarMode(SBModes sb_mode)
    {
        lv_page_set_sb_mode(this,sb_mode);
    }

    /**
     * Set the animation time for the page
     * @param page pointer to a page object
     * @param anim_time animation time in milliseconds
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_page_set_anim_time(this,anim_time);
    }

    /**
     * Enable the scroll propagation feature. If enabled then the page will move its parent if there is
     * no more space to scroll.
     * @param page pointer to a Page
     * @param en true or false to enable/disable scroll propagation
     */
    void setScrollPropagation(bool en)
    {
        lv_page_set_scroll_propagation(this,en);
    }

    /**
     * Enable the edge flash effect. (Show an arc when the an edge is reached)
     * @param page pointer to a Page
     * @param en true or false to enable/disable end flash
     */
    void setEdgeFlash(bool en)
    {
        lv_page_set_edge_flash(this,en);
    }

    /**
     * Set the fit policy in all 4 directions separately.
     * It tell how to change the page size automatically.
     * @param page pointer to a page object
     * @param left left fit policy from `lv_fit_t`
     * @param right right fit policy from `lv_fit_t`
     * @param top bottom fit policy from `lv_fit_t`
     * @param bottom bottom fit policy from `lv_fit_t`
     */
    void setScrlFit(LVFits left, LVFits right, LVFits top, LVFits bottom)
    {
        lv_page_set_scrl_fit4(this, left, right, top, bottom);
    }

    /**
     * Set the fit policy horizontally and vertically separately.
     * It tell how to change the page size automatically.
     * @param page pointer to a page object
     * @param hot horizontal fit policy from `lv_fit_t`
     * @param ver vertical fit policy from `lv_fit_t`
     */
    void setScrlFit(LVFits hor, LVFits ver)
    {
        lv_page_set_scrl_fit2(this, hor, ver);
    }

    /**
     * Set the fit policyin all 4 direction at once.
     * It tell how to change the page size automatically.
     * @param page pointer to a button object
     * @param fit fit policy from `lv_fit_t`
     */
    void setScrlFit(LVFits fit)
    {
        lv_page_set_scrl_fit(this, fit);
    }

    /**
     * Set width of the scrollable part of a page
     * @param page pointer to a page object
     * @param w the new width of the scrollable (it ha no effect is horizontal fit is enabled)
     */
    void setScrlWidth(LVCoord w)
    {
        lv_page_set_scrl_width(this, w);
    }

    /**
     * Set height of the scrollable part of a page
     * @param page pointer to a page object
     * @param h the new height of the scrollable (it ha no effect is vertical fit is enabled)
     */
    void setScrlHeight(LVCoord h)
    {
        lv_page_set_scrl_height(this, h);
    }

    /**
     * Set the layout of the scrollable part of the page
     * @param page pointer to a page object
     * @param layout a layout from 'lv_cont_layout_t'
     */
    void setScrlLayout(LVLayouts layout)
    {
        lv_page_set_scrl_layout(this, layout);
    }

    /**
     * Set a style of a page
     * @param page pointer to a page object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_page_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Set the scroll bar mode on a page
     * @param page pointer to a page object
     * @return the mode from 'lv_page_sb.mode_t' enum
     */
    SBModes getScrollBarMode()
    {
        return (SBModes)lv_page_get_sb_mode(this);
    }

    /**
     * Get the scroll propagation property
     * @param page pointer to a Page
     * @return true or false
     */
    bool getScrollPropagation()
    {
        return lv_page_get_scroll_propagation(this);
    }

    /**
     * Get the edge flash effect property.
     * @param page pointer to a Page
     * return true or false
     */
    bool getEdgeFlash()
    {
        return lv_page_get_edge_flash(this);
    }

    /**
     * Get that width which can be set to the children to still not cause overflow (show scrollbars)
     * @param page pointer to a page object
     * @return the width which still fits into the page
     */
    LVCoord getFitWidth()
    {
        return lv_page_get_fit_width(this);
    }

    /**
     * Get that height which can be set to the children to still not cause overflow (show scrollbars)
     * @param page pointer to a page object
     * @return the height which still fits into the page
     */
    LVCoord getFitHeight()
    {
        return lv_page_get_fit_height(this);
    }

    /**
     * Get width of the scrollable part of a page
     * @param page pointer to a page object
     * @return the width of the scrollable
     */
    LVCoord getScrlWidth()
    {
        return lv_page_get_scrl_width(this);
    }

    /**
     * Get height of the scrollable part of a page
     * @param page pointer to a page object
     * @return the height of the scrollable
     */
    LVCoord getScrlHeight()
    {
        return lv_page_get_scrl_height(this);
    }

    /**
     * Get the layout of the scrollable part of a page
     * @param page pointer to page object
     * @return the layout from 'lv_cont_layout_t'
     */
    LVLayouts getScrlLayout()
    {
        return (LVLayouts)lv_page_get_scrl_layout(this);
    }

    /**
     * Get the left fit mode
     * @param page pointer to a page object
     * @return an element of `lv_fit_t`
     */
    LVFits getScrlFitLeft()
    {
        return (LVFits)lv_page_get_scrl_fit_left(this);
    }

    /**
     * Get the right fit mode
     * @param page pointer to a page object
     * @return an element of `lv_fit_t`
     */
    LVFits getScrlFitRight()
    {
        return (LVFits)lv_page_get_scrl_fit_right(this);
    }

    /**
     * Get the top fit mode
     * @param page pointer to a page object
     * @return an element of `lv_fit_t`
     */
    LVFits getScrlFitTop()
    {
        return (LVFits)lv_page_get_scrl_fit_top(this);
    }

    /**
     * Get the bottom fit mode
     * @param page pointer to a page object
     * @return an element of `lv_fit_t`
     */
    LVFits getScrlFitBottom()
    {
        return (LVFits)lv_page_get_scrl_fit_bottom(this);
    }

    /**
     * Get a style of a page
     * @param page pointer to page object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_page_get_style(this,type);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Find whether the page has been scrolled to a certain edge.
     * @param page Page object
     * @param edge Edge to check
     * @return true if the page is on the specified edge
     */
    bool onEdge(Edges edge)
    {
        return lv_page_on_edge(this,edge);
    }

    /**
     * Glue the object to the page. After it the page can be moved (dragged) with this object too.
     * @param obj pointer to an object on a page
     * @param glue true: enable glue, false: disable glue
     */
    void glueObject(bool glue)
    {
        lv_page_glue_obj(this,glue);
    }

    /**
     * Focus on an object. It ensures that the object will be visible on the page.
     * @param page pointer to a page object
     * @param obj pointer to an object to focus (must be on the page)
     * @param anim_en LV_ANIM_ON to focus with animation; LV_ANIM_OFF to focus without animation
     */
    void focus(const lv_obj_t * obj, lv_anim_enable_t anim_en = LV_ANIM_OFF)
    {
        lv_page_focus(this,obj,anim_en);
    }

    /**
     * Scroll the page horizontally
     * @param page pointer to a page object
     * @param dist the distance to scroll (< 0: scroll left; > 0 scroll right)
     */
    void scrollHorizontally(LVCoord dist)
    {
        lv_page_scroll_hor(this,dist);
    }

    /**
     * Scroll the page vertically
     * @param page pointer to a page object
     * @param dist the distance to scroll (< 0: scroll down; > 0 scroll up)
     */
    void scrollVer(LVCoord dist)
    {
        lv_page_scroll_ver(this,dist);
    }

    /**
     * Not intended to use directly by the user but by other object types internally.
     * Start an edge flash animation. Exactly one `ext->edge_flash.xxx_ip` should be set
     * @param page
     */
    void startEdgeFlash()
    {
        lv_page_start_edge_flash(this);
    }

};
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_PAGE*/

#endif /*LVPAGE_H*/
