/**
 * @file lv_utils.h
 *
 */

#ifndef LVUTILS_H
#define LVUTILS_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_misc/lv_utils.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

class LVUtils
{
    LVUtils() {}
public:

    /**
     * Convert a number to string
     * @param num a number
     * @param buf pointer to a `char` buffer. The result will be stored here (max 10 elements)
     * @return same as `buf` (just for convenience)
     */
    static char * numToStr(int32_t num,char * buf = nullptr)
    {
        extern char* tempSter;
        if(buf == nullptr) buf = tempSter;
        return lv_utils_num_to_str(num,tempSter);
    }

    /** Searches base[0] to base[n - 1] for an item that matches *key.
     *
     * @note The function cmp must return negative if its first
     *  argument (the search key) is less that its second (a table entry),
     *  zero if equal, and positive if greater.
     *
     *  @note Items in the array must be in ascending order.
     *
     * @param key    Pointer to item being searched for
     * @param base   Pointer to first element to search
     * @param n      Number of elements
     * @param size   Size of each element
     * @param cmp    Pointer to comparison function (see #lv_font_codeCompare as a comparison function
     * example)
     *
     * @return a pointer to a matching item, or NULL if none exists.
     */
    static void * bsearch(const void * key, const void * base, uint32_t n, uint32_t size,
                            int32_t (*cmp)(const void * pRef, const void * pElement))
    {
        return lv_utils_bsearch(key, base,n, size,cmp);
    }

};
/**********************
 *      MACROS
 **********************/

#endif
