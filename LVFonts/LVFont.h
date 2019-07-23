/**
 * @file lv_font.h
 *
 */

#ifndef LVFONT_H
#define LVFONT_H


#include <lv_font/lv_font.h>
#include "../LVMisc/LVMemory.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*------------------
 * General types
 *-----------------*/

/** Describes the properties of a glyph. */
class LVFontGlyphDsc : public lv_font_glyph_dsc_t
{
    LV_MEMORY

//    uint16_t adv_w; /**< The glyph needs this space. Draw the next glyph after this width. 8 bit integer, 4 bit fractional */
//    uint8_t box_w;  /**< Width of the glyph's bounding box*/
//    uint8_t box_h;  /**< Height of the glyph's bounding box*/
//    int8_t ofs_x;   /**< x offset of the bounding box*/
//    int8_t ofs_y;  /**< y offset of the bounding box*/
//    uint8_t bpp;   /**< Bit-per-pixel: 1, 2, 4, 8*/
public:
    LVFontGlyphDsc() {}
};

/*Describe the properties of a font*/
//typedef struct _lv_font_struct
//{
//    /** Get a glyph's  descriptor from a font*/
//    bool (*get_glyph_dsc)(const struct _lv_font_struct *, lv_font_glyph_dsc_t *, uint32_t letter, uint32_t letter_next);

//    /** Get a glyph's bitmap from a font*/
//    const uint8_t * (*get_glyph_bitmap)(const struct _lv_font_struct *, uint32_t);

//    /*Pointer to the font in a font pack (must have the same line height)*/
//    uint8_t line_height;      /**< The real line height where any text fits*/
//    uint8_t base_line;        /**< Base line measured from the top of the line_height*/
//    void * dsc;               /**< Store implementation specific data here*/
//#if LV_USE_USER_DATA
//    lv_font_user_data_t user_data; /**< Custom user data for font. */
//#endif
//} lv_font_t;

class LVFont : public lv_font_t
{
    LV_MEMORY

    LVFont() {}
public:


    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Return with the bitmap of a font.
     * @param font_p pointer to a font
     * @param letter an UNICODE character code
     * @return  pointer to the bitmap of the letter
     */
    const uint8_t * getGlyphBitmap(uint32_t letter) const
    {
        return  lv_font_get_glyph_bitmap(this,letter);
    }

    /**
     * Get the descriptor of a glyph
     * @param font_p pointer to font
     * @param dsc_out store the result descriptor here
     * @param letter an UNICODE letter code
     * @return true: descriptor is successfully loaded into `dsc_out`.
     *         false: the letter was not found, no data is loaded to `dsc_out`
     */
    bool getGlyphDsc(LVFontGlyphDsc * dsc_out, uint32_t letter, uint32_t letter_next) const
    {
        return lv_font_get_glyph_dsc(this,dsc_out,letter,letter_next);
    }

    /**
     * Get the width of a glyph with kerning
     * @param font pointer to a font
     * @param letter an UNICODE letter
     * @param letter_next the next letter after `letter`. Used for kerning
     * @return the width of the glyph
     */
    uint16_t getGlyphWidth(uint32_t letter, uint32_t letter_next)
    {
        return lv_font_get_glyph_width(this,letter,letter_next);
    }

    /**
     * Get the line height of a font. All characters fit into this height
     * @param font_p pointer to a font
     * @return the height of a font
     */
    uint8_t getLineHeight()
    {
        return lv_font_get_line_height(this);
    }

};

/**********************
 *      MACROS
 **********************/


#endif /*LVFONT_H*/
