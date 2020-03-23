/**
 * @file lv_spinbox.h
 *
 */

#ifndef LVSPINBOX_H
#define LVSPINBOX_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_objx/lv_spinbox.h>

#if LV_USE_SPINBOX != 0

#include "../LVCore/LVObject.h"

/**********************
 *      TYPEDEFS
 **********************/

/*Data of spinbox*/
class LVSpinBox
        : public LVObject
        , public lv_spinbox_ext_t
{
    LV_OBJECT(LVSpinBox,lv_spinbox_create,lv_spinbox_ext_t)
public:


    /*Styles*/
    enum Styles : lv_spinbox_style_t
    {
        STYLE_BG     = LV_SPINBOX_STYLE_BG,
        STYLE_SB     = LV_SPINBOX_STYLE_SB,
        STYLE_CURSOR = LV_SPINBOX_STYLE_CURSOR,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a spinbox objects
     * @param par pointer to an object, it will be the parent of the new spinbox
     * @param copy pointer to a spinbox object, if not NULL then the new object will be copied from it
     * @return pointer to the created spinbox
     */
    //LVSpinBox(LVObject * par, const LVSpinBox * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a style of a spinbox.
     * @param templ pointer to template object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type)
    {
        lv_spinbox_set_style(this, type, style);
    }

    /**
     * Set spinbox value
     * @param spinbox pointer to spinbox
     * @param i value to be set
     */
    void setValue(int32_t i)
    {
        lv_spinbox_set_value(this,i);
    }

    /**
     * Set spinbox digit format (digit count and decimal format)
     * @param spinbox pointer to spinbox
     * @param digit_count number of digit excluding the decimal separator and the sign
     * @param separator_position number of digit before the decimal point. If 0, decimal point is not
     * shown
     */
    void setDigitFormat(uint8_t digit_count, uint8_t separator_position)
    {
        lv_spinbox_set_digit_format(this,digit_count,separator_position);
    }

    /**
     * Set spinbox step
     * @param spinbox pointer to spinbox
     * @param step steps on increment/decrement
     */
    void setStep(uint32_t step)
    {
        lv_spinbox_set_step(this,step);
    }

    /**
     * Set spinbox value range
     * @param spinbox pointer to spinbox
     * @param range_min maximum value, inclusive
     * @param range_max minimum value, inclusive
     */
    void setRange(int32_t range_min, int32_t range_max)
    {
        lv_spinbox_set_range(this,range_min,range_max);
    }

    /**
     * Set spinbox left padding in digits count (added between sign and first digit)
     * @param spinbox pointer to spinbox
     * @param cb Callback function called on value change event
     */
    void setPaddingLeft(uint8_t padding)
    {
        lv_spinbox_set_padding_left(this,padding);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get style of a spinbox.
     * @param templ pointer to template object
     * @param type which style should be get
     * @return style pointer to the style
     */
    const LVStyle * getStyle(Styles type)
    {
        return (const LVStyle *)lv_spinbox_get_style(this, type);
    }

    /**
     * Get the spinbox numeral value (user has to convert to float according to its digit format)
     * @param spinbox pointer to spinbox
     * @return value integer value of the spinbox
     */
    int32_t getValue()
    {
        return lv_spinbox_get_value(this);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Select next lower digit for edition by dividing the step by 10
     * @param spinbox pointer to spinbox
     */
    void stepNext()
    {
        lv_spinbox_step_next(this);
    }

    /**
     * Select next higher digit for edition by multiplying the step by 10
     * @param spinbox pointer to spinbox
     */
    void stepPrev()
    {
        return lv_spinbox_step_prev(this);
    }

    /**
     * Increment spinbox value by one step
     * @param spinbox pointer to spinbox
     */
    void increment()
    {
        lv_spinbox_increment(this);
    }

    /**
     * Decrement spinbox value by one step
     * @param spinbox pointer to spinbox
     */
    void decrement()
    {
        lv_spinbox_decrement(this);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_SPINBOX*/

#endif /*LVSPINBOX_H*/
