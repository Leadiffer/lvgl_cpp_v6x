/**
 * @file lv_arc.h
 *
 */

#ifndef LVARC_H
#define LVARC_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_arc.h>

#if LV_USE_ARC != 0

#include "../LVCore/LVObject.h"
#include "../LVMisc/LVMemory.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of arc*/
class LVArc
        : public LVObject
        , public LVFakeMemHeader<lv_arc_ext_t>
        , public lv_arc_ext_t
{
    LV_OBJECT(LVArc,lv_arc_create,lv_arc_ext_t)

public:

    /*Styles*/
    enum Styles : lv_arc_style_t
    {
        STYLE_MAIN = LV_ARC_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a arc objects
     * @param par pointer to an object, it will be the parent of the new arc
     * @param copy pointer to a arc object, if not NULL then the new object will be copied from it
     * @return pointer to the created arc
     */
    //LVArc(LVObject * parent, LVArc * copy)


    /*======================
     * Add/remove functions
     *=====================*/

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the start and end angles of an arc. 0 deg: bottom, 90 deg: right etc.
     * @param arc pointer to an arc object
     * @param start the start angle [0..360]
     * @param end the end angle [0..360]
     */
    void setAngles(uint16_t start, uint16_t end)
    {
        lv_arc_set_angles(this,start,end);
    }

    /**
     * Set a style of a arc.
     * @param arc pointer to arc object
     * @param type which style should be set
     * @param style pointer to a style
     *  */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_arc_set_style(this, type, style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the start angle of an arc.
     * @param arc pointer to an arc object
     * @return the start angle [0..360]
     */
    uint16_t getAngleStart()
    {
        return lv_arc_get_angle_start(this);
    }

    /**
     * Get the end angle of an arc.
     * @param arc pointer to an arc object
     * @return the end angle [0..360]
     */
    uint16_t getAngleEnd()
    {
        return lv_arc_get_angle_end(this);
    }

    /**
     * Get style of a arc.
     * @param arc pointer to arc object
     * @param type which style should be get
     * @return style pointer to the style
     *  */
    const LVStyle * getStyle(Styles type = STYLE_MAIN)
    {
        return (const LVStyle*) lv_arc_get_style(this,type);
    }

};
/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ARC*/

#endif /*LVARC_H*/
