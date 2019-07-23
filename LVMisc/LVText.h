/**
 * @file lv_text.h
 *
 */

#ifndef LVTEXT_H
#define LVTEXT_H

/*********************
 *      INCLUDES
 *********************/

#include "LVMemory.h"
#include "../LVFonts/LVFont.h"
#include "LVArea.h"
#include <lv_misc/lv_txt.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * @brief The LVText class
 * 作用是啥,暂时不清楚
 */
class LVText
{
    LV_MEMORY

    enum Flag : lv_txt_flag_t
    {
        FLAG_NONE    = LV_TXT_FLAG_NONE,
        FLAG_RECOLOR = LV_TXT_FLAG_RECOLOR, /*Enable parsing of recolor command*/
        FLAG_EXPAND  = LV_TXT_FLAG_EXPAND,  /*Ignore width to avoid automatic word wrapping*/
        FLAG_CENTER  = LV_TXT_FLAG_CENTER,  /*Align the text to the middle*/
        FLAG_RIGHT   = LV_TXT_FLAG_RIGHT,   /*Align the text to the right*/
    };

    enum CmdState : lv_txt_cmd_state_t
    {
        CMD_STATE_WAITING   = LV_TXT_CMD_STATE_WAIT, /*Waiting for command*/
        CMD_STATE_PARAMETER = LV_TXT_CMD_STATE_PAR,  /*Processing the parameter*/
        CMD_STATE_COMMAND   = LV_TXT_CMD_STATE_IN,   /*Processing the command*/
    };

public:

    /**
     * Get size of a text
     * @param size_res pointer to a 'point_t' variable to store the result
     * @param text pointer to a text
     * @param font pinter to font of the text
     * @param letter_space letter space of the text
     * @param line_space line space of the text
     * @param flags settings for the text from 'txt_flag_t' enum
     * @param max_width max with of the text (break the lines to fit this size) Set CORD_MAX to avoid
     * line breaks
     */
    static LVPoint getSize(const LVFont * font, const char * text,
                         LVCoord letter_space, LVCoord line_space, LVCoord max_width,
                         Flag flag)
    {
        LVPoint size_res;
        lv_txt_get_size(&size_res, text, font, letter_space, line_space, max_width, flag);
        return size_res;
    }

    /**
     * Get the next line of text. Check line length and break chars too.
     * @param txt a '\0' terminated string
     * @param font pointer to a font
     * @param letter_space letter space
     * @param max_width max with of the text (break the lines to fit this size) Set CORD_MAX to avoid
     * line breaks
     * @param flags settings for the text from 'txt_flag_type' enum
     * @return the index of the first char of the new line (in byte index not letter index. With UTF-8
     * they are different)
     */
    static uint16_t getNextLine( const char * text,const LVFont * font, LVCoord letter_space,
                                  LVCoord max_width, Flag flag)
    {
        return lv_txt_get_next_line(text, font, letter_space,
                                     max_width,  flag);
    }

    /**
     * Give the length of a text with a given font
     * @param txt a '\0' terminate string
     * @param length length of 'txt' in byte count and not characters (Á is 1 character but 2 bytes in
     * UTF-8)
     * @param font pointer to a font
     * @param letter_space letter space
     * @param flags settings for the text from 'txt_flag_t' enum
     * @return length of a char_num long text
     */
    static LVCoord getWidth( const char * text,uint16_t length, const lv_font_t * font,
                                LVCoord letter_space, Flag flag)
    {
        return lv_txt_get_width(text , length, font, letter_space, flag);
    }

    /**
     * Check next character in a string and decide if te character is part of the command or not
     * @param state pointer to a txt_cmd_state_t variable which stores the current state of command
     * processing
     * @param c the current character
     * @return true: the character is part of a command and should not be written,
     *         false: the character should be written
     */
    static bool isCommand(CmdState * state, uint32_t c)
    {
        return lv_txt_is_cmd((lv_txt_cmd_state_t*)state, c);
    }

    /**
     * Insert a string into an other
     * @param txt_buf the original text (must be big enough for the result text)
     * @param pos position to insert (0: before the original text, 1: after the first char etc.)
     * @param ins_txt text to insert
     */
    static void Insert(char * txt_buf, uint32_t pos, const char * ins_txt)
    {
        lv_txt_ins(txt_buf, pos, ins_txt);
    }

    /**
     * Delete a part of a string
     * @param txt string to modify
     * @param pos position where to start the deleting (0: before the first char, 1: after the first
     * char etc.)
     * @param len number of characters to delete
     */
    static void cut(char * txt, uint32_t pos, uint32_t len)
    {
        lv_txt_cut(txt, pos, len);
    }

};

/**********************
 *      MACROS
 **********************/


#endif /*LVTEXT_H*/
