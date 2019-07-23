/**
 * @file lv_style.h
 *
 */

#ifndef LVSTYLE_H
#define LVSTYLE_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_core/lv_style.h>
#include "../LVMisc/LVArea.h"
#include "../LVMisc/LVColor.h"
#include "../LVMisc/LVMemory.h"
#include "../LVMisc/LVAnimation.h"
#include "../LVFonts/LVFont.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Border types (Use 'OR'ed values)*/
enum BorderPart : lv_border_part_t
{
    BORDER_NONE     = LV_BORDER_NONE    ,
    BORDER_BOTTOM   = LV_BORDER_BOTTOM  ,
    BORDER_TOP      = LV_BORDER_TOP     ,
    BORDER_LEFT     = LV_BORDER_LEFT    ,
    BORDER_RIGHT    = LV_BORDER_RIGHT   ,
    BORDER_FULL     = LV_BORDER_FULL    ,
    BORDER_INTERNAL = LV_BORDER_INTERNAL, /*FOR matrix-like objects (e.g. Button matrix)*/
};

/*Shadow types*/
enum ShadowType : lv_shadow_type_t
{
    SHADOW_BOTTOM = LV_SHADOW_BOTTOM,
    SHADOW_FULL   = LV_SHADOW_FULL,
};

class LVStyle : public lv_style_t
{
    LV_MEMORY

    struct Private
    {
        uint8_t glass : 1; /**< 1: Do not inherit this style*/

        /** Object background. */
        struct
        {
            LVColor main_color; /**< Object's main background color. */
            LVColor grad_color; /**< Second color. If not equal to `main_color` a gradient will be drawn for the background. */
            LVCoord radius; /**< Object's corner radius. You can use #LV_RADIUS_CIRCLE if you want to draw a circle. */
            LVOpacity opa; /**< Object's LVOpacity (0-255). */

            struct
            {
                LVColor color; /**< Border color */
                LVCoord width; /**< Border width */
                BorderPart part; /**< Which borders to draw */
                LVOpacity opa; /**< Border LVOpacity. */
            } border;


            struct
            {
                LVColor color;
                LVCoord width;
                ShadowType type; /**< Which parts of the shadow to draw */
            } shadow;

            struct
            {
                LVCoord top;
                LVCoord bottom;
                LVCoord left;
                LVCoord right;
                LVCoord inner;
            } padding;
        } body;

        /** Style for text drawn by this object. */
        struct
        {
            LVColor color; /**< Text color */
            LVColor sel_color; /**< Text selection background color. */
            const LVFont * font;
            LVCoord letter_space; /**< Space between letters */
            LVCoord line_space; /**< Space between lines (vertical) */
            LVOpacity opa; /**< Text LVOpacity */
        } text;

        /**< Style of images. */
        struct
        {
            LVColor color; /**< Color to recolor the image with */
            LVOpacity intense; /**< LVOpacity of recoloring (0 means no recoloring) */
            LVOpacity opa; /**< LVOpacity of whole image */
        } image;

        /**< Style of lines (not borders). */
        struct
        {
            LVColor color;
            LVCoord width;
            LVOpacity opa;
            uint8_t rounded : 1; /**< 1: rounded line endings*/
        } line;
    };

public:

    static const LVStyle &scr;
    static const LVStyle &transp;
    static const LVStyle &transp_fit;
    static const LVStyle &transp_tight;
    static const LVStyle &plain;
    static const LVStyle &plain_color;
    static const LVStyle &pretty;
    static const LVStyle &pretty_color;
    static const LVStyle &btn_rel;
    static const LVStyle &btn_pr;
    static const LVStyle &btn_tgl_rel;
    static const LVStyle &btn_tgl_pr;
    static const LVStyle &btn_ina;

    LVStyle()
    {}

    LVStyle(const LVStyle& other)
    {
        *this = other;
    }

    LVStyle(const lv_style_t& other)
    {
        *this = other;
    }

    Private* operator ->(){ return (Private*)this; }

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    LVStyle& operator=(const LVStyle& other)
    {
        memcpy(this,&other,sizeof(LVStyle));
        return *this;
    }

    LVStyle& operator=(const lv_style_t& other)
    {
        memcpy(this,&other,sizeof(lv_style_t));
        return *this;
    }

    /**
     *  Init the basic styles
     */
    static void init(void)
    {
        lv_style_init();
    }

    /**
     * Copy a style to an other
     * @param dest pointer to the destination style
     * @param src pointer to the source style
     */
    static void copy(LVStyle * dest, const LVStyle * src)
    {
        lv_style_copy(dest,src);
    }

    void copy(const LVStyle * src)
    {
        lv_style_copy(this,src);
    }

    /**
     * Mix two styles according to a given ratio
     * @param start start style
     * @param end end style
     * @param res store the result style here
     * @param ratio the ratio of mix [0..256]; 0: `start` style; 256: `end` style
     */
    static void mix(const LVStyle * start, const LVStyle * end, LVStyle * res,
                      uint16_t ratio)
    {
        lv_style_mix(start,end,res,ratio);
    }

    void mix(const LVStyle * start, const LVStyle * end, uint16_t ratio)
    {
        lv_style_mix(start,end,this,ratio);
    }
};

//const LVStyle & LVStyle::scr          = *((LVStyle*)&lv_style_scr         ) ;
//const LVStyle & LVStyle::transp       = *((LVStyle*)&lv_style_transp      ) ;
//const LVStyle & LVStyle::transp_fit   = *((LVStyle*)&lv_style_transp_fit  ) ;
//const LVStyle & LVStyle::transp_tight = *((LVStyle*)&lv_style_transp_tight) ;
//const LVStyle & LVStyle::plain        = *((LVStyle*)&lv_style_plain       ) ;
//const LVStyle & LVStyle::plain_color  = *((LVStyle*)&lv_style_plain_color ) ;
//const LVStyle & LVStyle::pretty       = *((LVStyle*)&lv_style_pretty      ) ;
//const LVStyle & LVStyle::pretty_color = *((LVStyle*)&lv_style_pretty_color) ;
//const LVStyle & LVStyle::btn_rel      = *((LVStyle*)&lv_style_btn_rel     ) ;
//const LVStyle & LVStyle::btn_pr       = *((LVStyle*)&lv_style_btn_pr      ) ;
//const LVStyle & LVStyle::btn_tgl_rel  = *((LVStyle*)&lv_style_btn_tgl_rel ) ;
//const LVStyle & LVStyle::btn_tgl_pr   = *((LVStyle*)&lv_style_btn_tgl_pr  ) ;
//const LVStyle & LVStyle::btn_ina      = *((LVStyle*)&lv_style_btn_ina     ) ;

#if LV_USE_ANIMATION




class LVStyleAnimation
        : public LVAnimation
        , private LVMemoryHeader // fake Memory Header for lv_style_anim_dsc_t
        , public lv_style_anim_dsc_t
{
    LV_MEMORY

protected:
    //LVAnimation m_anim;
public:

    /**
     * Initialize an animation variable.
     * E.g.:
     * lv_anim_t a;
     * lv_style_anim__init(&a);
     * lv_style_anim_set_...(&a);
     * lv_style_anim_create(&a);
     * @param a pointer to an `lv_anim_t` variable to initialize
     */
    LVStyleAnimation()
        :LVMemoryHeader(0,false)// mark mem ont used
    {
        LVMemory::placementAlloc((lv_style_anim_dsc_t*)this);
        lv_style_anim_init(this);
        LVMemory::resetPlacementAlloc();
    }

    /**
     *
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param to_anim pointer to the style to animate
     * @param start pointer to a style to animate from (start value)
     * @param end pointer to a style to animate to (end value)
     */
    void setStyles(LVStyle * to_anim, const LVStyle * start, const LVStyle * end)
    {
        lv_style_anim_set_styles(this,to_anim,start,end);
    }

    /**
     * Set the duration and delay of an animation
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param duration duration of the animation in milliseconds
     * @param delay delay before the animation in milliseconds
     */
    void setTime(uint16_t duration, uint16_t delay)
    {
        lv_style_anim_set_time(this, duration, delay);
    }

    /**
     * Set a function call when the animation is ready
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param ready_cb a function call when the animation is ready
     */
    void setReadyCallBack(LVAnimReadyCallBack ready_cb)
    {
        if(ready_cb.isStdFunc())
        {
            m_ready_cb = ready_cb;
            lv_style_anim_set_ready_cb(this,(lv_anim_ready_cb_t)lvAnimationReadyCallBackAgent);
        }
        else
        {
            lv_style_anim_set_ready_cb(this,(lv_anim_ready_cb_t)ready_cb.getFuncPtr());
        }
    }

    /**
     * Make the animation to play back to when the forward direction is ready
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param wait_time time in milliseconds to wait before starting the back direction
     */
    void setPlayback(uint16_t wait_time)
    {
        lv_style_anim_set_playback(this, wait_time);
    }

    /**
     * Disable playback. (Disabled after `lv_anim_init()`)
     * @param a pointer to an initialized `lv_anim_t` variable
     */
    void clearPlayback()
    {
        lv_style_anim_clear_playback(this);
    }

    /**
     * Make the animation to start again when ready.
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param wait_time time in milliseconds to wait before starting the animation again
     */
    void setRepeat(uint16_t wait_time)
    {
        lv_style_anim_set_repeat(this, wait_time);
    }

    /**
     * Disable repeat. (Disabled after `lv_anim_init()`)
     * @param a pointer to an initialized `lv_anim_t` variable
     */
    void clearRepeat()
    {
        lv_style_anim_clear_repeat(this);
    }

    /**
     * Set a user specific data for the animation
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param user_data the user data
     */
    void setUserData(lv_anim_user_data_t user_data)
    {
        lv_style_anim_set_user_data(this, user_data);
    }

    /**
     * Get the user data
     * @param a pointer to an initialized `lv_anim_t` variable
     * @return the user data
     */
    lv_anim_user_data_t getUserData()
    {
        return lv_style_anim_get_user_data(this);
    }

    /**
     * Get pointer to the user data
     * @param a pointer to an initialized `lv_anim_t` variable
     * @return pointer to the user data
     */
    lv_anim_user_data_t * getUserDataPtr()
    {
        return lv_style_anim_get_user_data_ptr(this);
    }

    /**
     * Create an animation
     * @param a an initialized 'anim_t' variable. Not required after call.
     */
    void animationCreate()
    {
        lv_style_anim_create(this);
    }

    /*******************
     *     ENHANCE
     *******************/
};
#endif

/*************************
 *    GLOBAL VARIABLES
 *************************/

/**********************
 *      MACROS
 **********************/

#endif /*LV_STYLE_H*/
