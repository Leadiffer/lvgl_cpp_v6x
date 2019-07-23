/**
 * @file lv_theme_nemo.h
 *
 */

#ifndef LVTHEMENEMO_H
#define LVTHEMENEMO_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_nemo.h>
#include "LVTheme.h"

#if LV_USE_THEME_NEMO

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
class LVThemeNemo : public LVTheme
{
    LV_THEME
    LVThemeNemo() {}
public:

    /**
     * Initialize the material theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeNemo * init(uint16_t hue, lv_font_t * font)
    {
        return (LVThemeNemo *)lv_theme_nemo_init(hue,font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeNemo * getInstance(void)
    {
        return (LVThemeNemo *)lv_theme_get_nemo();
    }

};

/**********************
 *      MACROS
 **********************/

#endif

#endif /*LVTHEMENEMO_H*/
