#ifndef LVSYMBOL_H
#define LVSYMBOL_H
/* clang-format off */

#include <stdint.h>
#include <lv_font/lv_symbol_def.h>

/*
 * following list is generated using
 * cat lv_symbol_def.h | sed -E -n 's/^#define\s+(SYMBOL_\w+).*$/    _LV_STR_\1,/p'
 */
class LVSymbol
{
protected:

    LVSymbol(){}

    static const char** s_symbolList()
    {
        static const char symbolList[][4] =
        {
            //{LV_SYMBOL_GLYPH_FIRST  }, //  0xF800
            {LV_SYMBOL_AUDIO        }, // "\xEF\xA0\x80"
            {LV_SYMBOL_VIDEO        }, // "\xEF\xA0\x81"
            {LV_SYMBOL_LIST         }, // "\xEF\xA0\x82"
            {LV_SYMBOL_OK           }, // "\xEF\xA0\x83"
            {LV_SYMBOL_CLOSE        }, // "\xEF\xA0\x84"
            {LV_SYMBOL_POWER        }, // "\xEF\xA0\x85"
            {LV_SYMBOL_SETTINGS     }, // "\xEF\xA0\x86"
            {LV_SYMBOL_TRASH        }, // "\xEF\xA0\x87"
            {LV_SYMBOL_HOME         }, // "\xEF\xA0\x88"
            {LV_SYMBOL_DOWNLOAD     }, // "\xEF\xA0\x89"
            {LV_SYMBOL_DRIVE        }, // "\xEF\xA0\x8A"
            {LV_SYMBOL_REFRESH      }, // "\xEF\xA0\x8B"
            {LV_SYMBOL_MUTE         }, // "\xEF\xA0\x8C"
            {LV_SYMBOL_VOLUME_MID   }, // "\xEF\xA0\x8D"
            {LV_SYMBOL_VOLUME_MAX   }, // "\xEF\xA0\x8E"
            {LV_SYMBOL_IMAGE        }, // "\xEF\xA0\x8F"
            {LV_SYMBOL_EDIT         }, // "\xEF\xA0\x90"
            {LV_SYMBOL_PREV         }, // "\xEF\xA0\x91"
            {LV_SYMBOL_PLAY         }, // "\xEF\xA0\x92"
            {LV_SYMBOL_PAUSE        }, // "\xEF\xA0\x93"
            {LV_SYMBOL_STOP         }, // "\xEF\xA0\x94"
            {LV_SYMBOL_NEXT         }, // "\xEF\xA0\x95"
            {LV_SYMBOL_EJECT        }, // "\xEF\xA0\x96"
            {LV_SYMBOL_LEFT         }, // "\xEF\xA0\x97"
            {LV_SYMBOL_RIGHT        }, // "\xEF\xA0\x98"
            {LV_SYMBOL_PLUS         }, // "\xEF\xA0\x99"
            {LV_SYMBOL_MINUS        }, // "\xEF\xA0\x9A"
            {LV_SYMBOL_WARNING      }, // "\xEF\xA0\x9B"
            {LV_SYMBOL_SHUFFLE      }, // "\xEF\xA0\x9C"
            {LV_SYMBOL_UP           }, // "\xEF\xA0\x9D"
            {LV_SYMBOL_DOWN         }, // "\xEF\xA0\x9E"
            {LV_SYMBOL_LOOP         }, // "\xEF\xA0\x9F"
            {LV_SYMBOL_DIRECTORY    }, // "\xEF\xA0\xA0"
            {LV_SYMBOL_UPLOAD       }, // "\xEF\xA0\xA1"
            {LV_SYMBOL_CALL         }, // "\xEF\xA0\xA2"
            {LV_SYMBOL_CUT          }, // "\xEF\xA0\xA3"
            {LV_SYMBOL_COPY         }, // "\xEF\xA0\xA4"
            {LV_SYMBOL_SAVE         }, // "\xEF\xA0\xA5"
            {LV_SYMBOL_CHARGE       }, // "\xEF\xA0\xA6"
            {LV_SYMBOL_BELL         }, // "\xEF\xA0\xA7"
            {LV_SYMBOL_KEYBOARD     }, // "\xEF\xA0\xA8"
            {LV_SYMBOL_GPS          }, // "\xEF\xA0\xA9"
            {LV_SYMBOL_FILE         }, // "\xEF\xA0\xAA"
            {LV_SYMBOL_WIFI         }, // "\xEF\xA0\xAB"
            {LV_SYMBOL_BATTERY_FULL }, // "\xEF\xA0\xAC"
            {LV_SYMBOL_BATTERY_3    }, // "\xEF\xA0\xAD"
            {LV_SYMBOL_BATTERY_2    }, // "\xEF\xA0\xAE"
            {LV_SYMBOL_BATTERY_1    }, // "\xEF\xA0\xAF"
            {LV_SYMBOL_BATTERY_EMPTY}, // "\xEF\xA0\xB0"
            {LV_SYMBOL_BLUETOOTH    }, // "\xEF\xA0\xB1"
            //{LV_SYMBOL_GLYPH_LAST   }, // 0xF831

            /*Invalid symbol at (U+F831). If written before a string then `lv_img` will show it as a label*/
            {LV_SYMBOL_DUMMY        }, // "\xEF\xA3\xBF"
        };
        return (const char**)symbolList;
    }


public:
    enum Name : uint8_t
    {
        AUDIO,
        VIDEO,
        LIST,
        OK,
        CLOSE,
        POWER,
        SETTINGS,
        TRASH,
        HOME,
        DOWNLOAD,
        DRIVE,
        REFRESH,
        MUTE,
        VOLUME_MID,
        VOLUME_MAX,
        IMAGE,
        EDIT,
        PREV,
        PLAY,
        PAUSE,
        STOP,
        NEXT,
        EJECT,
        LEFT,
        RIGHT,
        PLUS,
        MINUS,
        WARNING,
        SHUFFLE,
        UP,
        DOWN,
        LOOP,
        DIRECTORY,
        UPLOAD,
        CALL,
        CUT,
        COPY,
        SAVE,
        CHARGE,
        BELL,
        KEYBOARD,
        GPS,
        FILE,
        WIFI,
        BATTERY_FULL,
        BATTERY_3,
        BATTERY_2,
        BATTERY_1,
        BATTERY_EMPTY,
        BLUETOOTH,
        DUMMY,
    };

    inline static const char * get(Name symbol)
    {
        return s_symbolList()[symbol];
    }

};


#endif /*LV_SYMBOL_DEF_H*/





