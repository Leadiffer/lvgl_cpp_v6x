/**
 * @file lv_theme_mono.h
 *
 */

#ifndef LVTHEMEMONO_H
#define LVTHEMEMONO_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_mono.h>
#include "LVTheme.h"

#if LV_USE_THEME_MONO

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
class LVThemeMono : public LVTheme
{
public:
    LVThemeMono() {}

    /**
     * Initialize the mono theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeMono * init(uint16_t hue, lv_font_t * font = nullptr)
    {
        return (LVThemeMono *)lv_theme_mono_init(hue, font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeMono * getInstance(void)
    {
        return (LVThemeMono *)lv_theme_get_mono();
    }
};

/**********************
 *      MACROS
 **********************/

#endif


#endif /*LVTHEMEMONO_H*/
