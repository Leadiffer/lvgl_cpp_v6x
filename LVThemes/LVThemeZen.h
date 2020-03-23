/**
 * @file lv_theme_zen.h
 *
 */

#ifndef LVTHEMEZEN_H
#define LVTHEMEZEN_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_zen.h>
#include "LVTheme.h"
#if LV_USE_THEME_ZEN

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

class LVThemeZen : public LVTheme
{
    LV_THEME
    LVThemeZen() {}
public:

    /**
     * Initialize the zen theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeZen * init(uint16_t hue, lv_font_t * font = nullptr)
    {
        return (LVThemeZen *)lv_theme_zen_init(hue,font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeZen * getInstance(void)
    {
        return (LVThemeZen *)lv_theme_get_zen();
    }
};



/**********************
 *      MACROS
 **********************/

#endif

#endif /*LVTHEMEZEN_H*/
