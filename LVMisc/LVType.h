/**
 * @file lv_types.h
 *
 */

#ifndef LVTYPE_H
#define LVTYPE_H

#include <lv_misc/lv_types.h>

/*********************
 *      INCLUDES
 *********************/

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

enum LVResult : lv_res_t
{
    RES_Invalid = LV_RES_INV, /*Typically indicates that the object is deleted (become invalid) in the action
                       function or an operation was failed*/
    RES_OK = LV_RES_OK, /*The object is valid (no deleted) after the action*/
    RES_Valid = RES_OK,
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/


#endif // LVTYPE_H
