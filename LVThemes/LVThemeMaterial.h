/**
 * @file lv_theme_material.h
 *
 */

#ifndef LVTHEMEMATERIAL_H
#define LVTHEMEMATERIAL_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_themes/lv_theme_material.h>
#include "LVTheme.h"

#if LV_USE_THEME_MATERIAL

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
class LVThemeMaterial : public LVTheme
{
    LV_THEME
    LVThemeMaterial() {}
public:

    /**
     * Initialize the material theme
     * @param hue [0..360] hue value from HSV color space to define the theme's base color
     * @param font pointer to a font (NULL to use the default)
     * @return pointer to the initialized theme
     */
    static LVThemeMaterial * init(uint16_t hue, lv_font_t * font = nullptr)
    {
        return (LVThemeMaterial *)lv_theme_material_init(hue,font);
    }

    /**
     * Get a pointer to the theme
     * @return pointer to the theme
     */
    static LVThemeMaterial * getInstance(void)
    {
        return (LVThemeMaterial *)lv_theme_get_material();
    }

};

/**********************
 *      MACROS
 **********************/

#endif


#endif /*LVTHEMEMATERIAL_H*/
