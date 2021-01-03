#ifndef LVSYMBOL_H
#define LVSYMBOL_H
/* clang-format off */

#include <stdint.h>
#include "string.h"
#include <lv_font/lv_symbol_def.h>

class Utf8Str
{
public:
    char utf8[7];

    Utf8Str(){ memset(utf8,0,7); }
    Utf8Str(const char * str){ strcpy(utf8,str); }
    Utf8Str(uint64_t unicode);
    Utf8Str(const Utf8Str & other){ strcpy(utf8,other.utf8); }

    operator unsigned char*(){ return (unsigned char*)utf8; }
    operator char *(){ return utf8; }
    operator void *(){ return utf8; }

    operator const unsigned char*() const{ return (unsigned char*)utf8; }
    operator const char *() const{ return utf8; }
    operator const void *() const{ return utf8; }
};

#define LV_SYMBOL(u) LVSymbol::fromUnicode(u)

/*
 * following list is generated using
 * cat lv_symbol_def.h | sed -E -n 's/^#define\s+(SYMBOL_\w+).*$/    _LV_STR_\1,/p'
 */
class LVSymbol
{
protected:

    LVSymbol(){}

//    static const char** s_symbolList()
//    {
//        static const char symbolList[][4] =
//        {
//            //{LV_SYMBOL_GLYPH_FIRST  }, //  0xF800
//            {LV_SYMBOL_AUDIO        }, // "\xEF\xA0\x80"
//            {LV_SYMBOL_VIDEO        }, // "\xEF\xA0\x81"
//            {LV_SYMBOL_LIST         }, // "\xEF\xA0\x82"
//            {LV_SYMBOL_OK           }, // "\xEF\xA0\x83"
//            {LV_SYMBOL_CLOSE        }, // "\xEF\xA0\x84"
//            {LV_SYMBOL_POWER        }, // "\xEF\xA0\x85"
//            {LV_SYMBOL_SETTINGS     }, // "\xEF\xA0\x86"
//            {LV_SYMBOL_TRASH        }, // "\xEF\xA0\x87"
//            {LV_SYMBOL_HOME         }, // "\xEF\xA0\x88"
//            {LV_SYMBOL_DOWNLOAD     }, // "\xEF\xA0\x89"
//            {LV_SYMBOL_DRIVE        }, // "\xEF\xA0\x8A"
//            {LV_SYMBOL_REFRESH      }, // "\xEF\xA0\x8B"
//            {LV_SYMBOL_MUTE         }, // "\xEF\xA0\x8C"
//            {LV_SYMBOL_VOLUME_MID   }, // "\xEF\xA0\x8D"
//            {LV_SYMBOL_VOLUME_MAX   }, // "\xEF\xA0\x8E"
//            {LV_SYMBOL_IMAGE        }, // "\xEF\xA0\x8F"
//            {LV_SYMBOL_EDIT         }, // "\xEF\xA0\x90"
//            {LV_SYMBOL_PREV         }, // "\xEF\xA0\x91"
//            {LV_SYMBOL_PLAY         }, // "\xEF\xA0\x92"
//            {LV_SYMBOL_PAUSE        }, // "\xEF\xA0\x93"
//            {LV_SYMBOL_STOP         }, // "\xEF\xA0\x94"
//            {LV_SYMBOL_NEXT         }, // "\xEF\xA0\x95"
//            {LV_SYMBOL_EJECT        }, // "\xEF\xA0\x96"
//            {LV_SYMBOL_LEFT         }, // "\xEF\xA0\x97"
//            {LV_SYMBOL_RIGHT        }, // "\xEF\xA0\x98"
//            {LV_SYMBOL_PLUS         }, // "\xEF\xA0\x99"
//            {LV_SYMBOL_MINUS        }, // "\xEF\xA0\x9A"
//            {LV_SYMBOL_WARNING      }, // "\xEF\xA0\x9B"
//            {LV_SYMBOL_SHUFFLE      }, // "\xEF\xA0\x9C"
//            {LV_SYMBOL_UP           }, // "\xEF\xA0\x9D"
//            {LV_SYMBOL_DOWN         }, // "\xEF\xA0\x9E"
//            {LV_SYMBOL_LOOP         }, // "\xEF\xA0\x9F"
//            {LV_SYMBOL_DIRECTORY    }, // "\xEF\xA0\xA0"
//            {LV_SYMBOL_UPLOAD       }, // "\xEF\xA0\xA1"
//            {LV_SYMBOL_CALL         }, // "\xEF\xA0\xA2"
//            {LV_SYMBOL_CUT          }, // "\xEF\xA0\xA3"
//            {LV_SYMBOL_COPY         }, // "\xEF\xA0\xA4"
//            {LV_SYMBOL_SAVE         }, // "\xEF\xA0\xA5"
//            {LV_SYMBOL_CHARGE       }, // "\xEF\xA0\xA6"
//            {LV_SYMBOL_BELL         }, // "\xEF\xA0\xA7"
//            {LV_SYMBOL_KEYBOARD     }, // "\xEF\xA0\xA8"
//            {LV_SYMBOL_GPS          }, // "\xEF\xA0\xA9"
//            {LV_SYMBOL_FILE         }, // "\xEF\xA0\xAA"
//            {LV_SYMBOL_WIFI         }, // "\xEF\xA0\xAB"
//            {LV_SYMBOL_BATTERY_FULL }, // "\xEF\xA0\xAC"
//            {LV_SYMBOL_BATTERY_3    }, // "\xEF\xA0\xAD"
//            {LV_SYMBOL_BATTERY_2    }, // "\xEF\xA0\xAE"
//            {LV_SYMBOL_BATTERY_1    }, // "\xEF\xA0\xAF"
//            {LV_SYMBOL_BATTERY_EMPTY}, // "\xEF\xA0\xB0"
//            {LV_SYMBOL_BLUETOOTH    }, // "\xEF\xA0\xB1"
//            //{LV_SYMBOL_GLYPH_LAST   }, // 0xF831

//            /*Invalid symbol at (U+F831). If written before a string then `lv_img` will show it as a label*/
//            {LV_SYMBOL_DUMMY        }, // "\xEF\xA3\xBF"
//        };
//        return (const char**)symbolList;
//    }


public:
//    enum Name : uint8_t
//    {
//        AUDIO,
//        VIDEO,
//        LIST,
//        OK,
//        CLOSE,
//        POWER,
//        SETTINGS,
//        TRASH,
//        HOME,
//        DOWNLOAD,
//        DRIVE,
//        REFRESH,
//        MUTE,
//        VOLUME_MID,
//        VOLUME_MAX,
//        IMAGE,
//        EDIT,
//        PREV,
//        PLAY,
//        PAUSE,
//        STOP,
//        NEXT,
//        EJECT,
//        LEFT,
//        RIGHT,
//        PLUS,
//        MINUS,
//        WARNING,
//        SHUFFLE,
//        UP,
//        DOWN,
//        LOOP,
//        DIRECTORY,
//        UPLOAD,
//        CALL,
//        CUT,
//        COPY,
//        SAVE,
//        CHARGE,
//        BELL,
//        KEYBOARD,
//        GPS,
//        FILE,
//        WIFI,
//        BATTERY_FULL,
//        BATTERY_3,
//        BATTERY_2,
//        BATTERY_1,
//        BATTERY_EMPTY,
//        BLUETOOTH,
//        DUMMY,
//    };

//    inline static const char * get(Name symbol)
//    {
//        return s_symbolList()[symbol];
//    }

    /**
     * @brief 从unicode编号中获得图像符号
     * @param unicode
     * @return
     */
    static const Utf8Str fromUnicode(uint32_t unicode)
    {
        Utf8Str utf8;
        enc_unicode_to_utf8_one(unicode,(unsigned char*)utf8,20);
        return utf8;
    }

    /*****************************************************************************
     * 将一个字符的Unicode(UCS-2和UCS-4)编码转换成UTF-8编码.
     *
     * 参数:
     *    unic     字符的Unicode编码值
     *    pOutput  指向输出的用于存储UTF8编码值的缓冲区的指针
     *    outsize  pOutput缓冲的大小
     *
     * 返回值:
     *    返回转换后的字符的UTF8编码所占的字节数, 如果出错则返回 0 .
     *
     * 注意:
     *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
     *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
     *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
     *     2. 请保证 pOutput 缓冲区有最少有 6 字节的空间大小!
     ****************************************************************************/
    static int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput,int outSize);

    /*****************************************************************************
     * 将一个字符的UTF8编码转换成Unicode(UCS-2和UCS-4)编码.
     *
     * 参数:
     *    pInput      指向输入缓冲区, 以UTF-8编码
     *    Unic        指向输出缓冲区, 其保存的数据即是Unicode编码值,
     *                类型为unsigned long .
     *
     * 返回值:
     *    成功则返回该字符的UTF8编码所占用的字节数; 失败则返回0.
     *
     * 注意:
     *     1. UTF8没有字节序问题, 但是Unicode有字节序要求;
     *        字节序分为大端(Big Endian)和小端(Little Endian)两种;
     *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位)
     ****************************************************************************/
    static int enc_utf8_to_unicode_one(const unsigned char* pInput, unsigned long *Unic);

};





#endif /*LV_SYMBOL_DEF_H*/





