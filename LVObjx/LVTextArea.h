/**
 * @file lv_ta.h
 *
 */

#ifndef LVTEXTAREA_H
#define LVTEXTAREA_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_ta.h>

#if LV_USE_TA != 0

#include "../LVCore/LVObject.h"
#include "LVLabel.h"
#include "LVPage.h"
#include "LVLabel.h"

/**********************
 *      TYPEDEFS
 **********************/

/*Data of text area*/
class LVTextArea
        : public LVObject
        , public lv_ta_ext_t
{
    LV_OBJECT(LVTextArea,lv_ta_create,lv_ta_ext_t)
public:

    /** Possible text areas tyles. */
    enum Styles : lv_ta_style_t
    {
        STYLE_BG           = LV_TA_STYLE_BG,          /**< Text area background style */
        STYLE_SB           = LV_TA_STYLE_SB,          /**< Scrollbar style */
        STYLE_CURSOR       = LV_TA_STYLE_CURSOR,      /**< Cursor style */
        STYLE_EDGE_FLASH   = LV_TA_STYLE_EDGE_FLASH,  /**< Edge flash style */
        STYLE_PLACEHOLDER  = LV_TA_STYLE_PLACEHOLDER, /**< Placeholder style */
    };

    /** Style of text area's cursor. */
    enum Cursors : lv_cursor_type_t
    {
        CURSOR_NONE = LV_CURSOR_NONE, /**< No cursor */
        CURSOR_LINE = LV_CURSOR_LINE, /**< Vertical line */
        CURSOR_BLOCK = LV_CURSOR_BLOCK, /**< Rectangle */
        CURSOR_OUTLINE = LV_CURSOR_OUTLINE, /**< Outline around character */
        CURSOR_UNDERLINE = LV_CURSOR_UNDERLINE, /**< Horizontal line under character */
        CURSOR_HIDDEN = LV_CURSOR_HIDDEN /**< this flag can be ORed to any of the other values to temporarily hide the cursor */
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a text area objects
     * @param par pointer to an object, it will be the parent of the new text area
     * @param copy pointer to a text area object, if not NULL then the new object will be copied from it
     * @return pointer to the created text area
     */
    //LVTextArea(LVObject * par, const LVTextArea * copy);

    /*======================
     * Add/remove functions
     *=====================*/

    /**
     * Insert a character to the current cursor position.
     * To add a wide char, e.g. 'Á' use `lv_txt_encoded_conv_wc('Á')`
     * @param ta pointer to a text area object
     * @param c a character (e.g. 'a')
     */
    void addChar(uint32_t c)
    {
        lv_ta_add_char(this,c);
    }

    /**
     * Insert a text to the current cursor position
     * @param ta pointer to a text area object
     * @param txt a '\0' terminated string to insert
     */
    void addText(const char * txt)
    {
        lv_ta_add_text(this,txt);
    }

    /**
     * Delete a the left character from the current cursor position
     * @param ta pointer to a text area object
     */
    void deleteChar()
    {
        lv_ta_del_char(this);
    }

    /**
     * Delete the right character from the current cursor position
     * @param ta pointer to a text area object
     */
    void deleteCharForward()
    {
        lv_ta_del_char_forward(this);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the text of a text area
     * @param ta pointer to a text area
     * @param txt pointer to the text
     */
    void setText(const char * txt)
    {
        lv_ta_set_text(this,txt);
    }

    /**
     * Set the placeholder text of a text area
     * @param ta pointer to a text area
     * @param txt pointer to the text
     */
    void setPlaceholderText(const char * txt)
    {
        lv_ta_set_placeholder_text(this,txt);
    }

    /**
     * Set the cursor position
     * @param obj pointer to a text area object
     * @param pos the new cursor position in character index
     *             < 0 : index from the end of the text
     *             LV_TA_CURSOR_LAST: go after the last character
     */
    void setCursorPos(int16_t pos)
    {
        lv_ta_set_cursor_pos(this,pos);
    }


    /**
     * Set the cursor type.
     * @param ta pointer to a text area object
     * @param cur_type: element of 'lv_cursor_type_t'
     */
    void setCursorType(Cursors cur_type)
    {
        lv_ta_set_cursor_type(this,cur_type);
    }

    /**
     * Enable/Disable the positioning of the the cursor by clicking the text on the text area.
     * @param ta pointer to a text area object
     * @param en true: enable click positions; false: disable
     */
    void setCursorClickPos(bool en)
    {
        lv_ta_set_cursor_click_pos(this,en);
    }

    /**
     * Enable/Disable password mode
     * @param ta pointer to a text area object
     * @param en true: enable, false: disable
     */
    void setPwdMode(bool en)
    {
        lv_ta_set_pwd_mode(this,en);
    }

    /**
     * Configure the text area to one line or back to normal
     * @param ta pointer to a Text area object
     * @param en true: one line, false: normal
     */
    void setOneLine(bool en)
    {
        lv_ta_set_one_line(this,en);
    }

    /**
     * Set the alignment of the text area.
     * In one line mode the text can be scrolled only with `LV_LABEL_ALIGN_LEFT`.
     * this function should be called if the size of text area changes.
     * @param ta pointer to a text are object
     * @param align the desired alignment from `lv_label_align_t`. (LV_LABEL_ALIGN_LEFT/CENTER/RIGHT)
     */
    void setTextAlign(LVLabel::AlignPolicy align)
    {
        lv_ta_set_text_align(this,align);
    }

    /**
     * Set a list of characters. Only these characters will be accepted by the text area
     * @param ta pointer to  Text Area
     * @param list list of characters. Only the pointer is saved. E.g. "+-.,0123456789"
     */
    void setAcceptedChars(const char * list)
    {
        lv_ta_set_accepted_chars(this,list);
    }

    /**
     * Set max length of a Text Area.
     * @param ta pointer to  Text Area
     * @param num the maximal number of characters can be added (`lv_ta_set_text` ignores it)
     */
    void setMaxLength(uint16_t num)
    {
        lv_ta_set_max_length(this,num);
    }

    /**
     * In `LV_EVENT_INSERT` the text which planned to be inserted can be replaced by an other text.
     * It can be used to add automatic formatting to the text area.
     * @param ta pointer to a text area.
     * @param txt pointer to a new string to insert. If `""` no text will be added.
     *            The variable must be live after the `event_cb` exists. (Should be `global` or
     * `static`)
     */
    void setInsertReplace(const char * txt)
    {
        lv_ta_set_insert_replace(this,txt);
    }

    /**
     * Set the scroll bar mode of a text area
     * @param ta pointer to a text area object
     * @param sb_mode the new mode from 'lv_page_sb_mode_t' enum
     */
    void setScrollBarMode(LVPage::SBModes mode)
    {
        lv_ta_set_sb_mode(this, mode);
    }

    /**
     * Enable the scroll propagation feature. If enabled then the Text area will move its parent if
     * there is no more space to scroll.
     * @param ta pointer to a Text area
     * @param en true or false to enable/disable scroll propagation
     */
    void setScrollPropagation(bool en)
    {
        lv_ta_set_scroll_propagation(this, en);
    }

    /**
     * Enable the edge flash effect. (Show an arc when the an edge is reached)
     * @param page pointer to a Text Area
     * @param en true or false to enable/disable end flash
     */
    void setEdgeFlash(bool en)
    {
        lv_ta_set_edge_flash(this, en);
    }

    /**
     * Set a style of a text area
     * @param ta pointer to a text area object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_ta_set_style(this,type,style);
    }

    /**
     * Enable/disable selection mode.
     * @param ta pointer to a text area object
     * @param en true or false to enable/disable selection mode
     */
    void setTextSel(bool en)
    {
        lv_ta_set_text_sel(this,en);
    }

    /**
     * Set how long show the password before changing it to '*'
     * @param ta pointer to Text area
     * @param time show time in milliseconds. 0: hide immediately.
     */
    void setPwdShowTime(uint16_t time)
    {
        lv_ta_set_pwd_show_time(this,time);
    }

    /**
     * Set cursor blink animation time
     * @param ta pointer to Text area
     * @param time blink period. 0: disable blinking
     */
    void setCursorBlinkTime(uint16_t time)
    {
        lv_ta_set_cursor_blink_time(this,time);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the text of a text area. In password mode it gives the real text (not '*'s).
     * @param ta pointer to a text area object
     * @return pointer to the text
     */
    const char * getText()
    {
        return lv_ta_get_text(this);
    }

    /**
     * Get the placeholder text of a text area
     * @param ta pointer to a text area object
     * @return pointer to the text
     */
    const char * getPlaceholderText()
    {
        return lv_ta_get_placeholder_text(this);
    }

    /**
     * Get the label of a text area
     * @param ta pointer to a text area object
     * @return pointer to the label object
     */
    LVLabel * getLabel()
    {
        return (LVLabel *)lv_ta_get_label(this);
    }

    /**
     * Get the current cursor position in character index
     * @param ta pointer to a text area object
     * @return the cursor position
     */
    uint16_t getCursorPos()
    {
        return lv_ta_get_cursor_pos(this);
    }

    /**
     * Get the current cursor type.
     * @param ta pointer to a text area object
     * @return element of 'lv_cursor_type_t'
     */
    Cursors getCursorType()
    {
        return (Cursors)lv_ta_get_cursor_type(this);
    }

    /**
     * Get whether the cursor click positioning is enabled or not.
     * @param ta pointer to a text area object
     * @return true: enable click positions; false: disable
     */
    bool getCursorClickPos()
    {
        return lv_ta_get_cursor_click_pos(this);
    }

    /**
     * Get the password mode attribute
     * @param ta pointer to a text area object
     * @return true: password mode is enabled, false: disabled
     */
    bool getPwdMode()
    {
        return lv_ta_get_pwd_mode(this);
    }

    /**
     * Get the one line configuration attribute
     * @param ta pointer to a text area object
     * @return true: one line configuration is enabled, false: disabled
     */
    bool getOneLine()
    {
        return lv_ta_get_one_line(this);
    }

    /**
     * Get a list of accepted characters.
     * @param ta pointer to  Text Area
     * @return list of accented characters.
     */
    const char * getAcceptedChars()
    {
        return lv_ta_get_accepted_chars(this);
    }

    /**
     * Set max length of a Text Area.
     * @param ta pointer to  Text Area
     * @return the maximal number of characters to be add
     */
    uint16_t getMaxLength()
    {
        return lv_ta_get_max_length(this);
    }

    /**
     * Get the scroll bar mode of a text area
     * @param ta pointer to a text area object
     * @return scrollbar mode from 'lv_page_sb_mode_t' enum
     */
    LVPage::SBModes getScrollBarMode()
    {
        return (LVPage::SBModes)lv_ta_get_sb_mode(this);
    }

    /**
     * Get the scroll propagation property
     * @param ta pointer to a Text area
     * @return true or false
     */
    bool getScrollPropagation()
    {
        return lv_ta_get_scroll_propagation(this);
    }

    /**
     * Get the scroll propagation property
     * @param ta pointer to a Text area
     * @return true or false
     */
    bool getEdgeFlash()
    {
        return lv_ta_get_edge_flash(this);
    }

    /**
     * Get a style of a text area
     * @param ta pointer to a text area object
     * @param type which style should be get
     * @return style pointer to a style
     */
    const LVStyle * get_style(Styles type)
    {
        return (LVStyle *)lv_ta_get_style(this,type);
    }

    /**
     * Find whether text is selected or not.
     * @param ta Text area object
     * @return whether text is selected or not
     */
    bool isTextSelected()
    {
        return lv_ta_text_is_selected(this);
    }

    /**
     * Find whether selection mode is enabled.
     * @param ta pointer to a text area object
     * @return true: selection mode is enabled, false: disabled
     */
    bool getTextSelEn()
    {
        return lv_ta_get_text_sel_en(this);
    }

    /**
     * Set how long show the password before changing it to '*'
     * @param ta pointer to Text area
     * @return show time in milliseconds. 0: hide immediately.
     */
    uint16_t getPwdShowTime()
    {
        return lv_ta_get_pwd_show_time(this);
    }

    /**
     * Set cursor blink animation time
     * @param ta pointer to Text area
     * @return time blink period. 0: disable blinking
     */
    uint16_t getCursorBlinkTime()
    {
        return lv_ta_get_cursor_blink_time(this);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Clear the selection on the text area.
     * @param ta Text area object
     */
    void clearSelection()
    {
        lv_ta_clear_selection(this);
    }

    /**
     * Move the cursor one character right
     * @param ta pointer to a text area object
     */
    void cursorRight()
    {
        lv_ta_cursor_right(this);
    }

    /**
     * Move the cursor one character left
     * @param ta pointer to a text area object
     */
    void cursorLeft()
    {
        lv_ta_cursor_left(this);
    }

    /**
     * Move the cursor one line down
     * @param ta pointer to a text area object
     */
    void cursorDown()
    {
        lv_ta_cursor_down(this);
    }

    /**
     * Move the cursor one line up
     * @param ta pointer to a text area object
     */
    void cursorUp()
    {
        lv_ta_cursor_up(this);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TA_H*/

#endif /*LVTEXTAREA_H*/
