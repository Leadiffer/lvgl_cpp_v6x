/**
 * @file lv_theme_templ.h
 *
 */

#ifndef LVTHEMETEMPL_H
#define LVTHEMETEMPL_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_templ.h>
#include "LVTheme.h"

#if LV_USE_THEME_TEMPL

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
class LVThemeTempl : public LVTheme
{
    LV_THEME
    LVThemeTempl() {}
public:

    /**
     * Initialize the templ theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeTempl * init(uint16_t hue, lv_font_t * font = nullptr)
    {
        return (LVThemeTempl *)lv_theme_templ_init(hue, font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeTempl * getInstance(void)
    {
        return (LVThemeTempl *)lv_theme_get_templ();
    }

};

/**********************
 *      MACROS
 **********************/

#endif

#endif /*LVTHEMETEMPL_H*/
