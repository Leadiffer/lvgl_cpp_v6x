/**
 * @file lv_rect.h
 *
 */

#ifndef LVLABEL_H
#define LVLABEL_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_label.h>

#if LV_USE_LABEL != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/** Data of label*/
class LVLabel
        : public LVObject
        , public LVFakeMemHeader<lv_label_ext_t>
        , public lv_label_ext_t
{
    LV_OBJECT(LVLabel,lv_label_create,lv_label_ext_t)
public:

    /** Long mode behaviors. Used in 'lv_label_ext_t' */
    enum LongMode : lv_label_long_mode_t
    {
        LONG_EXPAND     = LV_LABEL_LONG_EXPAND,    /**< Expand the object size to the text size*/
        LONG_BREAK      = LV_LABEL_LONG_BREAK,     /**< Keep the object width, break the too long lines and expand the object
                                                       height*/
        LONG_DOT        = LV_LABEL_LONG_DOT,       /**< Keep the size and write dots at the end if the text is too long*/
        LONG_SROLL      = LV_LABEL_LONG_SROLL,      /**< Keep the size and roll the text back and forth*/
        LONG_SROLL_CIRC = LV_LABEL_LONG_SROLL_CIRC, /**< Keep the size and roll the text circularly*/
        LONG_CROP       = LV_LABEL_LONG_CROP,      /**< Keep the size and crop the text out of it*/
    };

    /** Label align policy*/
    enum AlignPolicy : lv_label_align_t
    {
        ALIGN_LEFT   = LV_LABEL_ALIGN_LEFT, /**< Align text to left */
        ALIGN_CENTER = LV_LABEL_ALIGN_CENTER, /**< Align text to center */
        ALIGN_RIGHT  = LV_LABEL_ALIGN_RIGHT, /**< Align text to right */
    };

    /** Label styles*/
    enum Styles
    {
        STYLE_MAIN = LV_LABEL_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a label objects
     * @param par pointer to an object, it will be the parent of the new label
     * @param copy pointer to a button object, if not NULL then the new object will be copied from it
     * @return pointer to the created button
     */
    //LVLabel(LVObject * parent, const LVLabel * copy);
    LVLabel(const char * text ,LVObject * parent, const LVLabel * copy)
        :LVLabel(parent,copy)
    {
        setText(text);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a new text for a label. Memory will be allocated to store the text by the label.
     * @param label pointer to a label object
     * @param text '\0' terminated character string. NULL to refresh with the current text.
     */
    void setText(const char * text)
    {
        lv_label_set_text(this,text);
    }

    /**
     * Set a new text for a label from a character array. The array don't has to be '\0' terminated.
     * Memory will be allocated to store the array by the label.
     * @param label pointer to a label object
     * @param array array of characters or NULL to refresh the label
     * @param size the size of 'array' in bytes
     */
    void setArrayText(const char * array, uint16_t size)
    {
        lv_label_set_array_text(this,array,size);
    }

    /**
     * Set a static text. It will not be saved by the label so the 'text' variable
     * has to be 'alive' while the label exist.
     * @param label pointer to a label object
     * @param text pointer to a text. NULL to refresh with the current text.
     */
    void setStaticText(const char * text)
    {
        lv_label_set_static_text(this,text);
    }

    /**
     * Set the behavior of the label with longer text then the object size
     * @param label pointer to a label object
     * @param long_mode the new mode from 'lv_label_long_mode' enum.
     *                  In LV_LONG_BREAK/LONG/ROLL the size of the label should be set AFTER this
     * function
     */
    void setLongMode(LongMode long_mode)
    {
        lv_label_set_long_mode(this,long_mode);
    }

    /**
     * Set the align of the label (left or center)
     * @param label pointer to a label object
     * @param align 'LV_LABEL_ALIGN_LEFT' or 'LV_LABEL_ALIGN_LEFT'
     */
    void setAlign(AlignPolicy align)
    {
        lv_label_set_align(this,align);
    }

    /**
     * Enable the recoloring by in-line commands
     * @param label pointer to a label object
     * @param en true: enable recoloring, false: disable
     */
    void setRecolor(bool en)
    {
        lv_label_set_recolor(this,en);
    }

    /**
     * Set the label to draw (or not draw) background specified in its style's body
     * @param label pointer to a label object
     * @param en true: draw body; false: don't draw body
     */
    void setBodyDraw(bool en)
    {
        lv_label_set_body_draw(this,en);
    }

    /**
     * Set the label's animation speed in LV_LABEL_LONG_SROLL/SCROLL_CIRC modes
     * @param label pointer to a label object
     * @param anim_speed speed of animation in px/sec unit
     */
    void setAnimSpeed(uint16_t anim_speed)
    {
        lv_label_set_anim_speed(this,anim_speed);
    }

    /**
     * Set the style of an label
     * @param label pointer to an label object
     * @param type which style should be get (can be only `LV_LABEL_STYLE_MAIN`)
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_label_set_style(this,type,style);
    }

    /**
     * @brief Set the selection start index.
     * @param label pointer to a label object.
     * @param index index to set. `LV_LABEL_TXT_SEL_OFF` to select nothing.
     */
    void setTextSelectStart(uint16_t index)
    {
        lv_label_set_text_sel_start(this,index);
    }

    /**
     * @brief Set the selection end index.
     * @param label pointer to a label object.
     * @param index index to set. `LV_LABEL_TXT_SEL_OFF` to select nothing.
     */
    void setTextSelectEnd(uint16_t index)
    {
        lv_label_set_text_sel_end(this,index);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the text of a label
     * @param label pointer to a label object
     * @return the text of the label
     */
    char * getText()
    {
        return lv_label_get_text(this);
    }

    /**
     * Get the long mode of a label
     * @param label pointer to a label object
     * @return the long mode
     */
    LongMode getLongMode()
    {
        return (LongMode)lv_label_get_long_mode(this);
    }

    /**
     * Get the align attribute
     * @param label pointer to a label object
     * @return LV_LABEL_ALIGN_LEFT or LV_LABEL_ALIGN_CENTER
     */
    AlignPolicy getAlign()
    {
        return (AlignPolicy)lv_label_get_align(this);
    }

    /**
     * Get the recoloring attribute
     * @param label pointer to a label object
     * @return true: recoloring is enabled, false: disable
     */
    bool getRecolor()
    {
        return lv_label_get_recolor(this);
    }

    /**
     * Get the body draw attribute
     * @param label pointer to a label object
     * @return true: draw body; false: don't draw body
     */
    bool getBodyDraw()
    {
        return lv_label_get_body_draw(this);
    }

    /**
     * Get the label's animation speed in LV_LABEL_LONG_ROLL and SCROLL modes
     * @param label pointer to a label object
     * @return speed of animation in px/sec unit
     */
    uint16_t getAnimSpeed()
    {
        return lv_label_get_anim_speed(this);
    }

    /**
     * Get the relative x and y coordinates of a letter
     * @param label pointer to a label object
     * @param index index of the letter [0 ... text length]. Expressed in character index, not byte
     * index (different in UTF-8)
     * @param pos store the result here (E.g. index = 0 gives 0;0 coordinates)
     */
    LVPoint getLetterPos(uint16_t index)
    {
        LVPoint pos;
        lv_label_get_letter_pos(this,index,&pos);
        return pos;
    }

    /**
     * Get the index of letter on a relative point of a label
     * @param label pointer to label object
     * @param pos pointer to point with coordinates on a the label
     * @return the index of the letter on the 'pos_p' point (E.g. on 0;0 is the 0. letter)
     * Expressed in character index and not byte index (different in UTF-8)
     */
    uint16_t getLetterOn(LVPoint * pos)
    {
        return lv_label_get_letter_on(this,pos);
    }

    /**
     * Check if a character is drawn under a point.
     * @param label Label object
     * @param pos Point to check for characte under
     * @return whether a character is drawn under the point
     */
    bool isCharUnderPos(LVPoint * pos)
    {
        return lv_label_is_char_under_pos(this,pos);
    }

    /**
     * Get the style of an label object
     * @param label pointer to an label object
     * @param type which style should be get (can be only `LV_LABEL_STYLE_MAIN`)
     * @return pointer to the label's style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle*)lv_label_get_style(this,type);
    }

    /**
     * @brief Get the selection start index.
     * @param label pointer to a label object.
     * @return selection start index. `LV_LABEL_TXT_SEL_OFF` if nothing is selected.
     */
    uint16_t getTextSelectStart()
    {
        return lv_label_get_text_sel_start(this);
    }

    /**
     * @brief Get the selection end index.
     * @param label pointer to a label object.
     * @return selection end index. `LV_LABEL_TXT_SEL_OFF` if nothing is selected.
     */
    uint16_t getTextSelectEnd()
    {
        return lv_label_get_text_sel_end(this);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Insert a text to the label. The label text can not be static.
     * @param label pointer to a label object
     * @param pos character index to insert. Expressed in character index and not byte index (Different
     * in UTF-8) 0: before first char. LV_LABEL_POS_LAST: after last char.
     * @param txt pointer to the text to insert
     */
    void insertText(uint32_t pos, const char * txt)
    {
        lv_label_ins_text(this,pos,txt);
    }

    /**
     * Delete characters from a label. The label text can not be static.
     * @param label pointer to a label object
     * @param pos character index to insert. Expressed in character index and not byte index (Different
     * in UTF-8) 0: before first char.
     * @param cnt number of characters to cut
     */
    void cutText(uint32_t pos, uint32_t cnt)
    {
        lv_label_cut_text(this,pos,cnt);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_LABEL*/


#endif /*LVLABEL_H*/
