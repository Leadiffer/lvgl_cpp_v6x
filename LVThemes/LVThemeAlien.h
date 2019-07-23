/**
 * @file lv_theme_alien.h
 *
 */

#ifndef LVTHEMEALIEN_H
#define LVTHEMEALIEN_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_alien.h>
#include "LVTheme.h"

#if LV_USE_THEME_ALIEN

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

class LVThemeAlien : public LVTheme
{
    LV_THEME
    LVThemeAlien() {}
public:

    /**
     * Initialize the alien theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeAlien * init(uint16_t hue, lv_font_t * font = nullptr)
    {
        return (LVThemeAlien *)lv_theme_alien_init(hue, font);
    }
    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeAlien * getInstance(void)
    {
        return (LVThemeAlien *)lv_theme_get_alien();
    }

};

/**********************
 *      MACROS
 **********************/

#endif

#endif /*LVTHEMEALIEN_H*/
