/**
 * @file lv_cont.h
 *
 */

#ifndef LVCONTAINER_H
#define LVCONTAINER_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_cont.h>

#if LV_USE_CONT != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
class LVContainer
        : public LVObject
        , public LVFakeMemHeader<lv_cont_ext_t>
        , public lv_cont_ext_t
{
    LV_OBJECT(LVContainer,lv_cont_create,lv_cont_ext_t)
public:

    /*Styles*/
    enum Styles : lv_cont_style_t
    {
        STYLE_MAIN = LV_CONT_STYLE_MAIN,
    };

    /** Container layout options*/
    enum Layouts :lv_layout_t
    {
        LAYOUT_OFF    = LV_LAYOUT_OFF , /**< No layout */
        LAYOUT_CENTER = LV_LAYOUT_CENTER, /**< Center objects */
        LAYOUT_COL_L  = LV_LAYOUT_COL_L,  /**< Column left align*/
        LAYOUT_COL_M  = LV_LAYOUT_COL_M,  /**< Column middle align*/
        LAYOUT_COL_R  = LV_LAYOUT_COL_R,  /**< Column right align*/
        LAYOUT_ROW_T  = LV_LAYOUT_ROW_T,  /**< Row top align*/
        LAYOUT_ROW_M  = LV_LAYOUT_ROW_M,  /**< Row middle align*/
        LAYOUT_ROW_B  = LV_LAYOUT_ROW_B,  /**< Row bottom align*/
        LAYOUT_PRETTY = LV_LAYOUT_PRETTY, /**< Put as many object as possible in row and begin a new row*/
        LAYOUT_GRID   = LV_LAYOUT_GRID,   /**< Align same-sized object into a grid*/
        _LAYOUT_NUM   = _LV_LAYOUT_NUM
    };

    /**
     * How to resize the container around the children.
     */
    enum Fits : lv_fit_t
    {
        FIT_NONE  = LV_FIT_NONE,  /**< Do not change the size automatically*/
        FIT_TIGHT = LV_FIT_TIGHT, /**< Shrink wrap around the children */
        FIT_FLOOD = LV_FIT_FLOOD, /**< Align the size to the parent's edge*/
        FIT_FILL  = LV_FIT_FILL,  /**< Align the size to the parent's edge first but if there is an object out of it
                                       then get larger */
        _FIT_NUM   = _LV_FIT_NUM
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a container objects
     * @param par pointer to an object, it will be the parent of the new container
     * @param copy pointer to a container object, if not NULL then the new object will be copied from it
     * @return pointer to the created container
     */
    //LVContainer(LVObject * parent, const LVContainer * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a layout on a container
     * @param cont pointer to a container object
     * @param layout a layout from 'lv_cont_layout_t'
     */
    void setLayout(Layouts layout)
    {
        lv_cont_set_layout(this,layout);
    }

    /**
     * Set the fit policy in all 4 directions separately.
     * It tell how to change the container's size automatically.
     * @param cont pointer to a container object
     * @param left left fit policy from `lv_fit_t`
     * @param right right fit policy from `lv_fit_t`
     * @param top bottom fit policy from `lv_fit_t`
     * @param bottom bottom fit policy from `lv_fit_t`
     */
    void setFit(Fits left, Fits right, Fits top, Fits bottom)
    {
        lv_cont_set_fit4(this,left,right,top,bottom);
    }

    /**
     * Set the fit policy horizontally and vertically separately.
     * It tell how to change the container's size automatically.
     * @param cont pointer to a container object
     * @param hot horizontal fit policy from `lv_fit_t`
     * @param ver vertical fit policy from `lv_fit_t`
     */
    void setFit(Fits hor, Fits ver)
    {
        lv_cont_set_fit4(this,hor,hor,ver,ver);
    }

    /**
     * Set the fit policyin all 4 direction at once.
     * It tell how to change the container's size automatically.
     * @param cont pointer to a container object
     * @param fit fit policy from `lv_fit_t`
     */
    void setFit(Fits fit)
    {
        lv_cont_set_fit4(this, fit, fit, fit, fit);
    }

    /**
     * Set the style of a container
     * @param cont pointer to a container object
     * @param type which style should be set (can be only `LV_CONT_STYLE_MAIN`)
     * @param style pointer to the new style
     */
    void setStyle(const LVStyle * style, Styles type = STYLE_MAIN)
    {
        lv_cont_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the layout of a container
     * @param cont pointer to container object
     * @return the layout from 'lv_cont_layout_t'
     */
    Layouts getLayout()
    {
        return (Layouts)lv_cont_get_layout(this);
    }

    /**
     * Get left fit mode of a container
     * @param cont pointer to a container object
     * @return an element of `lv_fit_t`
     */
    Fits getFitLeft()
    {
        return (Fits)lv_cont_get_fit_left(this);
    }

    /**
     * Get right fit mode of a container
     * @param cont pointer to a container object
     * @return an element of `lv_fit_t`
     */
    Fits getFitRight()
    {
        return (Fits)lv_cont_get_fit_right(this);
    }

    /**
     * Get top fit mode of a container
     * @param cont pointer to a container object
     * @return an element of `lv_fit_t`
     */
    Fits getFitTop()
    {
        return (Fits)lv_cont_get_fit_top(this);
    }

    /**
     * Get bottom fit mode of a container
     * @param cont pointer to a container object
     * @return an element of `lv_fit_t`
     */
    Fits getFitBottom()
    {
        return (Fits)lv_cont_get_fit_bottom(this);
    }

    /**
     * Get the style of a container
     * @param cont pointer to a container object
     * @param type which style should be get (can be only `LV_CONT_STYLE_MAIN`)
     * @return pointer to the container's style
     */
    const LVStyle * getStyle(Styles type = STYLE_MAIN)
    {
         return (const LVStyle *)lv_cont_get_style(this,type);
    }
};

using LVFits = LVContainer::Fits;
using LVLayouts = LVContainer::Layouts;

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CONT*/

#endif /*LVCONTAINER_H*/
