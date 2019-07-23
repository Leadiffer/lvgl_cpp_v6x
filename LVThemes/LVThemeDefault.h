/**
 * @file lv_theme_default.h
 *
 */

#ifndef LVTHEMEDEFAULT_H
#define LVTHEMEDEFAULT_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_default.h>
#include "LVTheme.h"

#if LV_USE_THEME_DEFAULT

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

class LVThemeDefault : public LVTheme
{
    LV_THEME
    LVThemeDefault() {}
public:

    /**
     * Initialize the default theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeDefault * init(uint16_t hue, lv_font_t * font)
    {
        return (LVThemeDefault *)lv_theme_default_init(hue, font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeDefault * getInstance(void)
    {
        return (LVThemeDefault *)lv_theme_get_default();
    }

};

/**********************
 *      MACROS
 **********************/

#endif

#endif /*LVTHEMETEMPL_H*/
