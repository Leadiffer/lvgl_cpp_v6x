/**
 * @file lv_color.h
 *
 */

#ifndef LVCOLOR_H
#define LVCOLOR_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_misc/lv_color.h>
#include "LVMemory.h"

/*********************
 *      DEFINES
 *********************/

using LVOpacity = uint8_t;

enum OpacityLevel : uint8_t
{
    OPA_TRANSP = LV_OPA_TRANSP,
    OPA_0      = LV_OPA_0     ,
    OPA_10     = LV_OPA_10    ,
    OPA_20     = LV_OPA_20    ,
    OPA_30     = LV_OPA_30    ,
    OPA_40     = LV_OPA_40    ,
    OPA_50     = LV_OPA_50    ,
    OPA_60     = LV_OPA_60    ,
    OPA_70     = LV_OPA_70    ,
    OPA_80     = LV_OPA_80    ,
    OPA_90     = LV_OPA_90    ,
    OPA_100    = LV_OPA_100   ,
    OPA_COVER  = LV_OPA_COVER ,
};


class LVColorHSV:public lv_color_hsv_t
{
    //代价太大,不参与LV内存管理
    //LV_MEMORY

public:
    LVColorHSV() {}
    LVColorHSV(uint16_t h, uint8_t s, uint8_t v)
    {
        this->h = h;
        this->s = s;
        this->v = v;
    }

    LVColorHSV(lv_color_hsv_t hsv)
    {
        this->h = hsv.h;
        this->s = hsv.s;
        this->v = hsv.v;
    }

    //operator lv_color_hsv_t()
    //{
    //    return *((lv_color_hsv_t*)this);
    //}

    operator uint32_t()
    {
        return *((uint32_t*)this);
    }

    LVColorHSV& operator =(const lv_color_hsv_t& hsv)
    {
        this->h = hsv.h;
        this->s = hsv.s;
        this->v = hsv.v;
        return *this;
    }

    LVColorHSV& operator =(const LVColorHSV& hsv)
    {
        this->h = hsv.h;
        this->s = hsv.s;
        this->v = hsv.v;
        return *this;
    }
};


/**********************
 *      TYPEDEFS
 **********************/
class LVColor
        : public lv_color_t
{
    //代价太大,不参与LV内存管理
    //LV_MEMORY

    enum Name : uint8_t
    {
        WHITE  ,
        SILVER ,
        GRAY   ,
        BLACK  ,
        RED    ,
        MAROON ,
        YELLOW ,
        OLIVE  ,
        LIME   ,
        GREEN  ,
        CYAN   ,
        AQUA   ,
        TEAL   ,
        BLUE   ,
        NAVY   ,
        MAGENTA,
        PURPLE ,
        ORANGE ,
    };

public:

    LVColor() {}

    LVColor(Name color)
    {
        switch (color)
        {
            case Name::WHITE   : this->full = lv_color_make(0xFF, 0xFF, 0xFF).full ; break;
            case Name::SILVER  : this->full = lv_color_make(0xC0, 0xC0, 0xC0).full ; break;
            case Name::GRAY    : this->full = lv_color_make(0x80, 0x80, 0x80).full ; break;
            case Name::BLACK   : this->full = lv_color_make(0x00, 0x00, 0x00).full ; break;
            case Name::RED     : this->full = lv_color_make(0xFF, 0x00, 0x00).full ; break;
            case Name::MAROON  : this->full = lv_color_make(0x80, 0x00, 0x00).full ; break;
            case Name::YELLOW  : this->full = lv_color_make(0xFF, 0xFF, 0x00).full ; break;
            case Name::OLIVE   : this->full = lv_color_make(0x80, 0x80, 0x00).full ; break;
            case Name::LIME    : this->full = lv_color_make(0x00, 0xFF, 0x00).full ; break;
            case Name::GREEN   : this->full = lv_color_make(0x00, 0x80, 0x00).full ; break;
            case Name::CYAN    :
            case Name::AQUA    : this->full = lv_color_make(0x00, 0xFF, 0xFF).full ; break;
            case Name::TEAL    : this->full = lv_color_make(0x00, 0x80, 0x80).full ; break;
            case Name::BLUE    : this->full = lv_color_make(0x00, 0x00, 0xFF).full ; break;
            case Name::NAVY    : this->full = lv_color_make(0x00, 0x00, 0x80).full ; break;
            case Name::MAGENTA : this->full = lv_color_make(0xFF, 0x00, 0xFF).full ; break;
            case Name::PURPLE  : this->full = lv_color_make(0x80, 0x00, 0x80).full ; break;
            case Name::ORANGE  : this->full = lv_color_make(0xFF, 0xA5, 0x00).full ; break;
            default:this->full = 0;break;
        }
    }

    /* create a color from R,G and B values */
    LVColor(uint8_t r, uint8_t g, uint8_t b)
    {
        this->full = lv_color_make(r,g,b).full;
    }

    LVColor(uint32_t c)
    {
        full = lv_color_hex(c).full;
    }

    LVColor(const lv_color_t & color)
    {
        this->full = color.full;
    }

    LVColor(const LVColor& color)
    {
        this->full = color.full;
    }

    static inline LVColor make(uint8_t r, uint8_t g, uint8_t b)
    {
        LVColor color;
        color.full = lv_color_make(r,g,b).full;
        return color;
    }

    static inline LVColor make(uint32_t rgb)
    {
        LVColor color;
        color.full = lv_color_make(rgb&0xff0000,rgb&0xff00,rgb&0xff).full;
        return color;
    }

    static inline LVColor fromRGB(uint8_t r, uint8_t g, uint8_t b)
    {
        LVColor color;
        color.full = lv_color_make(r,g,b).full;
        return color;
    }

    static inline LVColor fromHEX(uint32_t c)
    {
        LVColor color;
        color.full = lv_color_hex(c).full;
        return color;
    }

    static inline LVColor fromHEX3(uint32_t c)
    {
        LVColor color;
        color.full = lv_color_hex3(c).full;
        return color;
    }

    static inline LVColor fromHSV(uint16_t h, uint8_t s, uint8_t v)
    {
        LVColor color;
        color.full = lv_color_hsv_to_rgb(h,s,v).full;
        return color;
    }

    //operator lv_color_t()
    //{
    //    return *((lv_color_t*)this);
    //}

    LVColor& operator=(lv_color_t c)
    {
        this->full = c.full;
        return *this;
    }

    LVColor& operator=(LVColor c)
    {
        this->full = c.full;
        return *this;
    }

    LVColor& operator=(uint16_t c)
    {
        this->full = c;
        return *this;
    }
#if LV_COLOR_16_SWAP == 0
    LVColor& operator=(int32_t c)
    {
        this->ch.red   = (uint16_t)((c>>16 & 0xff) >> 3);
        this->ch.green = (uint16_t)((c>>8  & 0xff) >> 2);
        this->ch.blue  = (uint16_t)((c     & 0xff) >> 3);
        return *this;
    }
#endif

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /*In color conversations:
     * - When converting to bigger color type the LSB weight of 1 LSB is calculated
     *   E.g. 16 bit Red has 5 bits
     *         8 bit Red has 2 bits
     *        ----------------------
     *        8 bit red LSB = (2^5 - 1) / (2^2 - 1) = 31 / 3 = 10
     *
     * - When calculating to smaller color type simply shift out the LSBs
     *   E.g.  8 bit Red has 2 bits
     *        16 bit Red has 5 bits
     *        ----------------------
     *         Shift right with 5 - 3 = 2
     */

    inline uint8_t toColor1()
    {
        return lv_color_to1(*this);
    }

    inline uint8_t toColor8()
    {
        return lv_color_to8(*this);
    }

    inline uint16_t toColor16()
    {
        return lv_color_to16(*this);
    }

    inline uint32_t toColor32()
    {
        return lv_color_to32(*this);
    }

    inline LVColor mix(LVColor c2, uint8_t mix)
    {
        return lv_color_mix(*this, c2, mix);
    }

    /**
     * Get the brightness of a color
     * @param color a color
     * @return the brightness [0..255]
     */
    inline uint8_t brightness()
    {
        return lv_color_brightness(*this);
    }

    /**
     * Convert a HSV color to RGB
     * @param h hue [0..359]
     * @param s saturation [0..100]
     * @param v value [0..100]
     * @return the given RGB color in RGB (with LV_COLOR_DEPTH depth)
     */
    static inline LVColor hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
    {
        LVColor color;
        color.full =  lv_color_hsv_to_rgb(h, s, v).full;
        return color;
    }

    /**
     * Convert an RGB color to HSV
     * @param r red
     * @param g green
     * @param b blue
     * @return the given RGB color n HSV
     */
    static inline LVColorHSV rgbToHsv(uint8_t r, uint8_t g, uint8_t b)
    {
        return lv_color_rgb_to_hsv(r,g,b);
    }

#if LV_COLOR_16_SWAP == 0
    inline LVColorHSV toHsv()
    {
        return rgbToHsv(this->ch.red,this->ch.green,this->ch.blue);
    }
#endif

};

/**********************
 *      MACROS
 **********************/

#endif /*USE_COLOR*/
