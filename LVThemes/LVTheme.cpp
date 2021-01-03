#include "LVTheme.h"

#if LV_USE_THEME_DEFAULT
    static const char * th_Default = "Default";
#endif
#if LV_USE_THEME_ALIEN
    static const char * th_Alien = "Alien";
#endif
#if LV_USE_THEME_MATERIAL
    static const char * th_Material = "Material";
#endif
#if LV_USE_THEME_MONO
    static const char * th_Mono = "Mono";
#endif
#if LV_USE_THEME_NEMO
    static const char * th_Nemo = "Nemo";
#endif
#if LV_USE_THEME_NIGHT
    static const char * th_Night = "Night";
#endif
#if LV_USE_THEME_ZEN
    static const char * th_Zen = "Zen";
#endif
#if LV_USE_THEME_TEMPL
    static const char * th_Templ = "Templ";
#endif

const char * LVTheme::ThemeNames[] =
{
#if LV_USE_THEME_DEFAULT
    th_Default,
#endif
#if LV_USE_THEME_ALIEN
    th_Alien,
#endif
#if LV_USE_THEME_MATERIAL
    th_Material,
#endif
#if LV_USE_THEME_MONO
    th_Mono,
#endif
#if LV_USE_THEME_NEMO
    th_Nemo,
#endif
#if LV_USE_THEME_NIGHT
    th_Night,
#endif
#if LV_USE_THEME_ZEN
    th_Zen,
#endif
#if LV_USE_THEME_TEMPL
    th_Templ,
#endif
};

void LVTheme::setCurrent(Themes theme , uint16_t hue, lv_font_t *font)
{
    switch (theme%_END_THEME)
    {
#if LV_USE_THEME_DEFAULT
    case LVTheme::Default : LVThemeDefault::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_ALIEN
    case LVTheme::Alien : LVThemeAlien::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_MATERIAL
    case LVTheme::Material : LVThemeMaterial::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_MONO
    case LVTheme::Mono : LVThemeMono::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_NEMO
    case LVTheme::Nemo : LVThemeNemo::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_NIGHT
    case LVTheme::Night : LVThemeNight::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_ZEN
    case LVTheme::Zen : LVThemeZen::init(hue,font)->setCurrent(); break;
#endif
#if LV_USE_THEME_TEMPL
    case LVTheme::Templ : LVThemeTempl::init(hue,font)->setCurrent(); break;
#endif
    default:
        break;
    }
}
