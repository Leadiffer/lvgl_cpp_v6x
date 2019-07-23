/**
 * @file lv_table.h
 *
 */

#ifndef LVTABLE_H
#define LVTABLE_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_table.h>

#if LV_USE_TABLE != 0

#include "../LVCore/LVObject.h"
#include "LVLabel.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Internal table cell format structure.
 * 
 * Use the `lv_table` APIs instead.
 */
class LVTableCellFormat
{
public:
    union
    {
        struct
        {
            uint8_t align : 2;
            uint8_t right_merge : 1;
            uint8_t type : 2;
            uint8_t crop : 1;
        } s;
        uint8_t format_byte;
    };
};


/*Data of table*/
class LVTable
        : public LVObject
        , public LVFakeMemHeader<lv_table_ext_t>
        , public lv_table_ext_t
{
    LV_OBJECT(LVTable,lv_table_create,lv_table_ext_t)
public:

    /*Styles*/
    enum Styles :lv_table_style_t
    {
        STYLE_BG     = LV_TABLE_STYLE_BG,
        STYLE_CELL1 = LV_TABLE_STYLE_CELL1,
        STYLE_CELL2 = LV_TABLE_STYLE_CELL2,
        STYLE_CELL3 = LV_TABLE_STYLE_CELL3,
        STYLE_CELL4 = LV_TABLE_STYLE_CELL4,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a table object
     * @param par pointer to an object, it will be the parent of the new table
     * @param copy pointer to a table object, if not NULL then the new object will be copied from it
     * @return pointer to the created table
     */
    //LVTable(LVObject * par, const LVTable * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the value of a cell.
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @param txt text to display in the cell. It will be copied and saved so this variable is not
     * required after this function call.
     */
    void setCellValue(uint16_t row, uint16_t col, const char * txt)
    {
        lv_table_set_cell_value(this,row,col,txt);
    }

    /**
     * Set the number of rows
     * @param table table pointer to a Table object
     * @param row_cnt number of rows
     */
    void setRowCnt(uint16_t row_cnt)
    {
        lv_table_set_row_cnt(this,row_cnt);
    }

    /**
     * Set the number of columns
     * @param table table pointer to a Table object
     * @param col_cnt number of columns. Must be < LV_TABLE_COL_MAX
     */
    void setColCnt(uint16_t col_cnt)
    {
        lv_table_set_col_cnt(this,col_cnt);
    }

    /**
     * Set the width of a column
     * @param table table pointer to a Table object
     * @param col_id id of the column [0 .. LV_TABLE_COL_MAX -1]
     * @param w width of the column
     */
    void setColWidth(uint16_t col_id, lv_coord_t w)
    {
        lv_table_set_col_width(this,col_id,w);
    }

    /**
     * Set the text align in a cell
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @param align LV_LABEL_ALIGN_LEFT or LV_LABEL_ALIGN_CENTER or LV_LABEL_ALIGN_RIGHT
     */
    void setCellAlign(uint16_t row, uint16_t col, LVLabel::AlignPolicy align)
    {
        lv_table_set_cell_align(this,row,col,align);
    }

    /**
     * Set the type of a cell.
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @param type 1,2,3 or 4. The cell style will be chosen accordingly.
     */
    void setCellType(uint16_t row, uint16_t col, uint8_t type)
    {
        lv_table_set_cell_type(this,row,col,type);
    }

    /**
     * Set the cell crop. (Don't adjust the height of the cell according to its content)
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @param crop true: crop the cell content; false: set the cell height to the content.
     */
    void setCellCrop(uint16_t row, uint16_t col, bool crop)
    {
        lv_table_set_cell_crop(this,row,col,crop);
    }

    /**
     * Merge a cell with the right neighbor. The value of the cell to the right won't be displayed.
     * @param table table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @param en true: merge right; false: don't merge right
     */
    void setCellMergeRight(uint16_t row, uint16_t col, bool en)
    {
        lv_table_set_cell_merge_right(this,row,col,en);
    }

    /**
     * Set a style of a table.
     * @param table pointer to table object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(Styles type, const LVStyle * style)
    {
        lv_table_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the value of a cell.
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @return text in the cell
     */
    const char * getCellValue(uint16_t row, uint16_t col)
    {
        return lv_table_get_cell_value(this,row,col);
    }

    /**
     * Get the number of rows.
     * @param table table pointer to a Table object
     * @return number of rows.
     */
    uint16_t getRowCnt()
    {
        return lv_table_get_row_cnt(this);
    }

    /**
     * Get the number of columns.
     * @param table table pointer to a Table object
     * @return number of columns.
     */
    uint16_t getColCnt()
    {
        return lv_table_get_col_cnt(this);
    }

    /**
     * Get the width of a column
     * @param table table pointer to a Table object
     * @param col_id id of the column [0 .. LV_TABLE_COL_MAX -1]
     * @return width of the column
     */
    lv_coord_t getColWidth(uint16_t col_id)
    {
        return lv_table_get_col_width(this,col_id);
    }

    /**
     * Get the text align of a cell
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @return LV_LABEL_ALIGN_LEFT (default in case of error) or LV_LABEL_ALIGN_CENTER or
     * LV_LABEL_ALIGN_RIGHT
     */
    lv_label_align_t getCellAlign(uint16_t row, uint16_t col)
    {
        return lv_table_get_cell_align(this,row,col);
    }

    /**
     * Get the type of a cell
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @return 1,2,3 or 4
     */
    lv_label_align_t getCellType(uint16_t row, uint16_t col)
    {
        return lv_table_get_cell_type(this,row,col);
    }

    /**
     * Get the crop property of a cell
     * @param table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @return true: text crop enabled; false: disabled
     */
    lv_label_align_t getCellCrop(uint16_t row, uint16_t col)
    {
        return lv_table_get_cell_crop(this,row,col);
    }

    /**
     * Get the cell merge attribute.
     * @param table table pointer to a Table object
     * @param row id of the row [0 .. row_cnt -1]
     * @param col id of the column [0 .. col_cnt -1]
     * @return true: merge right; false: don't merge right
     */
    bool getCellMergeRight(uint16_t row, uint16_t col)
    {
        return lv_table_get_cell_merge_right(this,row,col);
    }

    /**
     * Get style of a table.
     * @param table pointer to table object
     * @param type which style should be get
     * @return style pointer to the style
     */
    const LVStyle * getStyle(lv_table_style_t type)
    {
        return (const LVStyle *)lv_table_get_style(this,type);
    }

};

/*=====================
 * Other functions
 *====================*/

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TABLE*/

#endif /*LVTABLE_H*/
