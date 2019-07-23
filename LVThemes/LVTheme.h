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

    /**
     * Get the current system theme.
     * @return pointer to the current system theme. NULL if not set.
     */
    static LVTheme * getCurrent(void)
    {
        return (LVTheme *)lv_theme_get_current();
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
