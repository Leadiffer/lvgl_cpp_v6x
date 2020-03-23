/**
 * @file lv_theme_night.h
 *
 */

#ifndef LVTHEMENIGHT_H
#define LVTHEMENIGHT_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_night.h>
#include "LVTheme.h"
#if LV_USE_THEME_NIGHT

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
class LVThemeNight : public LVTheme
{
    LV_THEME
    LVThemeNight() {}
public:

    /**
     * Initialize the night theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeNight * init(uint16_t hue, lv_font_t * font = nullptr)
    {
        return (LVThemeNight *)lv_theme_night_init(hue,font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeNight * getInstance(void)
    {
        return (LVThemeNight *)lv_theme_get_night();
    }

};
/**********************
 *      MACROS
 **********************/

#endif


#endif /*LVTHEMENIGHT_H*/
