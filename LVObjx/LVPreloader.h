/**
 * @file lv_preload.h
 *
 */

#ifndef LVPRELOAD_H
#define LVPRELOAD_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_preload.h>

#if LV_USE_PRELOAD != 0

#include "../LVCore/LVObject.h"
#include "../LVMisc/LVAnimation.h"
#include "LVArc.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Type of preloader.
 */
enum Types : lv_preload_type_t
{
    TYPE_SPINNING_ARC = LV_PRELOAD_TYPE_SPINNING_ARC,
    TYPE_FILLSPIN_ARC = LV_PRELOAD_TYPE_FILLSPIN_ARC,
};

/**
 * Direction the preloader should spin.
 */
enum Direction : lv_preload_dir_t
{
    DIR_FORWARD  = LV_PRELOAD_DIR_FORWARD,
    DIR_BACKWARD = LV_PRELOAD_DIR_BACKWARD,
};

/*Data of pre loader*/
class LVPreloader
        : public LVObject
        , public lv_preload_ext_t
{
    LV_OBJECT(LVPreloader,lv_preload_create,lv_preload_ext_t)
public:

    /*Styles*/
    enum Styles : lv_preload_style_t
    {
        STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a pre loader objects
     * @param par pointer to an object, it will be the parent of the new pre loader
     * @param copy pointer to a pre loader object, if not NULL then the new object will be copied from
     * it
     * @return pointer to the created pre loader
     */
    //LVPreloader(LVObject * par, const LVPreloader * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Set the length of the spinning  arc in degrees
     * @param preload pointer to a preload object
     * @param deg length of the arc
     */
    void setArcLength(lv_anim_value_t deg)
    {
        lv_preload_set_arc_length(this,deg);
    }

    /**
     * Set the spin time of the arc
     * @param preload pointer to a preload object
     * @param time time of one round in milliseconds
     */
    void setSpinTime(uint16_t time)
    {
        lv_preload_set_spin_time(this,time);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a style of a pre loader.
     * @param preload pointer to pre loader object
     * @param type which style should be set
     * @param style pointer to a style
     *  */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_preload_set_style(this,type,style);
    }

    /**
     * Set the animation type of a preloader.
     * @param preload pointer to pre loader object
     * @param type animation type of the preload
     *  */
    void setType(lv_preload_type_t type)
    {
        lv_preload_set_type(this,type);
    }

    /**
     * Set the animation direction of a preloader
     * @param preload pointer to pre loader object
     * @param direction animation direction of the preload
     */
    void setDir(lv_preload_dir_t dir)
    {
        lv_preload_set_dir(this,dir);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the arc length [degree] of the a pre loader
     * @param preload pointer to a pre loader object
     */
    lv_anim_value_t getArcLength()
    {
        return lv_preload_get_arc_length(this);
    }

    /**
     * Get the spin time of the arc
     * @param preload pointer to a pre loader object [milliseconds]
     */
    uint16_t getSpinTime()
    {
        return lv_preload_get_spin_time(this);
    }

    /**
     * Get style of a pre loader.
     * @param preload pointer to pre loader object
     * @param type which style should be get
     * @return style pointer to the style
     *  */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_preload_get_style(this,type);
    }

    /**
     * Get the animation type of a preloader.
     * @param preload pointer to pre loader object
     * @return animation type
     *  */
    Types getType()
    {
        return (Types)lv_preload_get_type(this);
    }

    /**
     * Get the animation direction of a preloader
     * @param preload pointer to pre loader object
     * @return animation direction
     */
    Direction getDir()
    {
        return (Direction)lv_preload_get_dir(this);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Animator function  (exec_cb) to rotate the arc of spinner.
     * @param ptr pointer to preloader
     * @param val the current desired value [0..360]
     */
    static void spinnerAnim(LVPreloader * ptr, lv_anim_value_t val)
    {
        lv_preload_spinner_anim(ptr,val);
    }
};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_PRELOAD*/

#endif /*LVPRELOAD_H*/
