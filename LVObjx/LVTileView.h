/**
 * @file lv_tileview.h
 *
 */

#ifndef LVTILEVIEW_H
#define LVTILEVIEW_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_tileview.h>

#if LV_USE_TILEVIEW != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Data of tileview*/

class LVTileView
        : public LVObject
        , public LVFakeMemHeader<lv_tileview_ext_t>
        , public lv_tileview_ext_t
{
    LV_OBJECT(LVTileView,lv_tileview_create,lv_tileview_ext_t)
public:

    /*Styles*/
    enum Styles : lv_tileview_style_t
    {
        LV_TILEVIEW_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a tileview objects
     * @param par pointer to an object, it will be the parent of the new tileview
     * @param copy pointer to a tileview object, if not NULL then the new object will be copied from it
     * @return pointer to the created tileview
     */
    //LVTileView(LVObject * parent, const LVTileView * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Register an object on the tileview. The register object will able to slide the tileview
     * @param tileview pointer to a Tileview object
     * @param element pointer to an object
     */
    void addElement(lv_obj_t * element)
    {
        lv_tileview_add_element(this,element);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the valid position's indices. The scrolling will be possible only to these positions.
     * @param tileview pointer to a Tileview object
     * @param valid_pos array width the indices. E.g. `lv_point_t p[] = {{0,0}, {1,0}, {1,1}`. Only the
     * pointer is saved so can't be a local variable.
     * @param valid_pos_cnt numner of elements in `valid_pos` array
     */
    void setValidPositions(const LVPoint * valid_pos, uint16_t valid_pos_cnt)
    {
        lv_tileview_set_valid_positions(this,valid_pos,valid_pos_cnt);
    }

    /**
     * Set the tile to be shown
     * @param tileview pointer to a tileview object
     * @param x column id (0, 1, 2...)
     * @param y line id (0, 1, 2...)
     * @param anim LV_ANIM_ON: set the value with an animation; LV_ANIM_OFF: change the value immediately
     */
    void setTileAct(lv_coord_t x, lv_coord_t y, lv_anim_enable_t anim)
    {
        lv_tileview_set_tile_act(this,x,y,anim);
    }

    /**
     * Enable the edge flash effect. (Show an arc when the an edge is reached)
     * @param tileview pointer to a Tileview
     * @param en true or false to enable/disable end flash
     */
    void setEdgeFlash(bool en)
    {
        lv_tileview_set_edge_flash(this, en);
    }

    /**
     * Set the animation time for the Tile view
     * @param tileview pointer to a page object
     * @param anim_time animation time in milliseconds
     */
    void setAnimTime(uint16_t anim_time)
    {
        lv_tileview_set_anim_time(this, anim_time);
    }

    /**
     * Set a style of a tileview.
     * @param tileview pointer to tileview object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(Styles type, const LVStyle * style)
    {
        lv_tileview_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the scroll propagation property
     * @param tileview pointer to a Tileview
     * @return true or false
     */
    bool getEdgeFlash()
    {
        return lv_tileview_get_edge_flash(this);
    }

    /**
     * Get the animation time for the Tile view
     * @param tileview pointer to a page object
     * @return animation time in milliseconds
     */
    uint16_t getAnimTime()
    {
        return lv_tileview_get_anim_time(this);
    }

    /**
     * Get style of a tileview.
     * @param tileview pointer to tileview object
     * @param type which style should be get
     * @return style pointer to the style
     */
    const LVStyle * getStyle(lv_tileview_style_t type)
    {
        return (const LVStyle *)lv_tileview_get_style(this,type);
    }

};

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TILEVIEW*/

#endif /*LVTILEVIEW_H*/
