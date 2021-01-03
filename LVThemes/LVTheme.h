/**
 *@file lv_themes.h
 *
 */

#ifndef LVTHEMES_H
#define LVTHEMES_H

/*********************
 *    INCLUDES
 *********************/
#include <lv_themes/lv_theme.h>

#include "LVCore/LVStyle.h"
#include "LVCore/LVGroup.h"

/*********************
 *    DEFINES
 *********************/

/**
  * 实现LVTheme的公共接口
  **/
#define LV_THEME


/**********************
 *    TYPEDEFS
 **********************/

class LVTheme : public lv_theme_t
{
    LV_THEME
protected:

    LVTheme() {}
public:

    /**
     * @brief 主题的枚举
     */
    enum Themes : uint16_t
    {
#if LV_USE_THEME_DEFAULT
        Default,
#endif
#if LV_USE_THEME_ALIEN
        Alien,
#endif
#if LV_USE_THEME_MATERIAL
        Material,
#endif
#if LV_USE_THEME_MONO
        Mono,
#endif
#if LV_USE_THEME_NEMO
        Nemo,
#endif
#if LV_USE_THEME_NIGHT
        Night,
#endif
#if LV_USE_THEME_ZEN
        Zen,
#endif
#if LV_USE_THEME_TEMPL
        Templ,
#endif
        _END_THEME
    };

    static const char * ThemeNames[];

    /**********************
     *  GLOBAL PROTOTYPES
     **********************/

    /**
     * Set a theme for the system.
     * From now, all the created objects will use styles from this theme by default
     * @param th pointer to theme (return value of: 'lv_theme_init_xxx()')
     */
    void setCurrent()
    {
        lv_theme_set_current(this);
    }

    static void setCurrent(Themes theme , uint16_t hue ,lv_font_t * font = nullptr);

    /**
     * Get the current system theme.
     * @return pointer to the current system theme. NULL if not set.
     */
    static LVTheme * getCurrent(void)
    {
        return static_cast<LVTheme *>(lv_theme_get_current());
    }

};

/**********************
 *    MACROS
 **********************/


/**********************
 *     POST INCLUDE
 *********************/
#include "LVThemeTempl.h"
#include "LVThemeDefault.h"
#include "LVThemeAlien.h"
#include "LVThemeNight.h"
#include "LVThemeZen.h"
#include "LVThemeMono.h"
#include "LVThemeNemo.h"
#include "LVThemeMaterial.h"


#endif /*LVTHEMES_H*/
