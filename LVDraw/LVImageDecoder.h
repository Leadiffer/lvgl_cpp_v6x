/**
 * @file lv_img_decoder.h
 *
 */

#ifndef LVIMAGEDEOCER_H
#define LVIMAGEDEOCER_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_draw/lv_img_decoder.h>
#include "../LVMisc/LVFileSystem.h"
#include "../LVMisc/LVTypes.h"
#include "../LVMisc/LVArea.h"
#include "../LVCore/LVStyle.h"
#include "../LVMisc/LVMemory.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/

/**
 * Source of image. */
enum ImageSource : lv_img_src_t
{
    SRC_VARIABLE = LV_IMG_SRC_VARIABLE, /** Binary/C variable */
    SRC_FILE     = LV_IMG_SRC_FILE, /** File in filesystem */
    SRC_SYMBOL   = LV_IMG_SRC_SYMBOL, /** Symbol (@ref lv_symbol_def.h) */
    SRC_UNKNOWN  = LV_IMG_SRC_UNKNOWN, /** Unknown source */
};

/*Image color format*/
enum ColorFromat : lv_img_cf_t
{
    CF_UNKNOWN                   = LV_IMG_CF_UNKNOWN ,

    CF_RAW                       = LV_IMG_CF_RAW,              /**< Contains the file as it is. Needs custom decoder function*/
    CF_RAW_ALPHA                 = LV_IMG_CF_RAW_ALPHA,        /**< Contains the file as it is. The image has alpha. Needs custom decoder
                                                                    function*/
    CF_RAW_CHROMA_KEYED          = LV_IMG_CF_RAW_CHROMA_KEYED, /**< Contains the file as it is. The image is chroma keyed. Needs
                                                                    custom decoder function*/

    CF_TRUE_COLOR                = LV_IMG_CF_TRUE_COLOR,              /**< Color format and depth should match with LV_COLOR settings*/
    CF_TRUE_COLOR_ALPHA          = LV_IMG_CF_TRUE_COLOR_ALPHA,        /**< Same as `LV_IMG_CF_TRUE_COLOR` but every pixel has an alpha byte*/
    CF_TRUE_COLOR_CHROMA_KEYED   = LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED, /**< Same as `LV_IMG_CF_TRUE_COLOR` but LV_COLOR_TRANSP pixels
                                                                         will be transparent*/

    CF_INDEXED_1BIT              = LV_IMG_CF_INDEXED_1BIT, /**< Can have 2 different colors in a palette (always chroma keyed)*/
    CF_INDEXED_2BIT              = LV_IMG_CF_INDEXED_2BIT, /**< Can have 4 different colors in a palette (always chroma keyed)*/
    CF_INDEXED_4BIT              = LV_IMG_CF_INDEXED_4BIT, /**< Can have 16 different colors in a palette (always chroma keyed)*/
    CF_INDEXED_8BIT              = LV_IMG_CF_INDEXED_8BIT, /**< Can have 256 different colors in a palette (always chroma keyed)*/

    CF_ALPHA_1BIT                = LV_IMG_CF_ALPHA_1BIT, /**< Can have one color and it can be drawn or not*/
    CF_ALPHA_2BIT                = LV_IMG_CF_ALPHA_2BIT, /**< Can have one color but 4 different alpha value*/
    CF_ALPHA_4BIT                = LV_IMG_CF_ALPHA_4BIT, /**< Can have one color but 16 different alpha value*/
    CF_ALPHA_8BIT                = LV_IMG_CF_ALPHA_8BIT, /**< Can have one color but 256 different alpha value*/
};


/**
 * LittlevGL image header
 */
class LVImageHeader : public lv_img_header_t
{
    LV_MEMORY
public:
    LVImageHeader() {}
};

class LVImageDsc : public lv_img_dsc_t
{
    struct Private
    {
        LVImageHeader header;
        uint32_t data_size;
        const uint8_t * data;
    };

public:
    LVImageDsc() {}

    Private* operator->()
    {
        return (Private*)this;
    }
};

///** Image header it is compatible with
// * the result from image converter utility*/


///* Decoder function definitions */

//struct _lv_img_decoder;
//struct _lv_img_decoder_dsc;

///**
// * Get info from an image and store in the `header`
// * @param src the image source. Can be a pointer to a C array or a file name (Use
// * `lv_img_src_get_type` to determine the type)
// * @param header store the info here
// * @return LV_RES_OK: info written correctly; LV_RES_INV: failed
// */
//typedef lv_res_t (*lv_img_decoder_info_f_t)(struct _lv_img_decoder * decoder, const void * src,
//                                            lv_img_header_t * header);

///**
// * Open an image for decoding. Prepare it as it is required to read it later
// * @param decoder pointer to the decoder the function associated with
// * @param dsc pointer to decoder descriptor. `src`, `style` are already initialized in it.
// */
//typedef lv_res_t (*lv_img_decoder_open_f_t)(struct _lv_img_decoder * decoder, struct _lv_img_decoder_dsc * dsc);

///**
// * Decode `len` pixels starting from the given `x`, `y` coordinates and store them in `buf`.
// * Required only if the "open" function can't return with the whole decoded pixel array.
// * @param decoder pointer to the decoder the function associated with
// * @param dsc pointer to decoder descriptor
// * @param x start x coordinate
// * @param y start y coordinate
// * @param len number of pixels to decode
// * @param buf a buffer to store the decoded pixels
// * @return LV_RES_OK: ok; LV_RES_INV: failed
// */
//typedef lv_res_t (*lv_img_decoder_read_line_f_t)(struct _lv_img_decoder * decoder, struct _lv_img_decoder_dsc * dsc,
//                                                 lv_coord_t x, lv_coord_t y, lv_coord_t len, uint8_t * buf);

///**
// * Close the pending decoding. Free resources etc.
// * @param decoder pointer to the decoder the function associated with
// * @param dsc pointer to decoder descriptor
// */
//typedef void (*lv_img_decoder_close_f_t)(struct _lv_img_decoder * decoder, struct _lv_img_decoder_dsc * dsc);

//typedef struct _lv_img_decoder
//{
//    lv_img_decoder_info_f_t info_cb;
//    lv_img_decoder_open_f_t open_cb;
//    lv_img_decoder_read_line_f_t read_line_cb;
//    lv_img_decoder_close_f_t close_cb;

//#if LV_USE_USER_DATA
//    lv_img_decoder_user_data_t user_data;
//#endif
//} lv_img_decoder_t;

///**Describe an image decoding session. Stores data about the decoding*/
//typedef struct _lv_img_decoder_dsc
//{
//    /**The decoder which was able to open the image source*/
//    lv_img_decoder_t * decoder;

//    /**The image source. A file path like "S:my_img.png" or pointer to an `lv_img_dsc_t` variable*/
//    const void * src;

//    /**Style to draw the image.*/
//    const lv_style_t * style;

//    /**Type of the source: file or variable. Can be set in `open` function if required*/
//    lv_img_src_t src_type;

//    /**Info about the opened image: color format, size, etc. MUST be set in `open` function*/
//    lv_img_header_t header;

//    /** Pointer to a buffer where the image's data (pixels) are stored in a decoded, plain format.
//     *  MUST be set in `open` function*/
//    const uint8_t * img_data;

//    /** How much time did it take to open the image. [ms]
//     *  If not set `lv_img_cache` will measure and set the time to open*/
//    uint32_t time_to_open;

//    /**A text to display instead of the image when the image can't be opened.
//     * Can be set in `open` function or set NULL. */
//    const char * error_msg;

//    /**Store any custom data here is required*/
//    void * user_data;
//} lv_img_decoder_dsc_t;

///**********************
// * GLOBAL PROTOTYPES
// **********************/

///**
// * Initialize the image decoder module
// */
//void lv_img_decoder_init(void);

///**
// * Get information about an image.
// * Try the created image decoder one by one. Once one is able to get info that info will be used.
// * @param src the image source. Can be
// *  1) File name: E.g. "S:folder/img1.png" (The drivers needs to registered via `lv_fs_add_drv()`)
// *  2) Variable: Pointer to an `lv_img_dsc_t` variable
// *  3) Symbol: E.g. `LV_SYMBOL_OK`
// * @param header the image info will be stored here
// * @return LV_RES_OK: success; LV_RES_INV: wasn't able to get info about the image
// */
//lv_res_t lv_img_decoder_get_info(const char * src, lv_img_header_t * header);

///**
// * Open an image.
// * Try the created image decoder one by one. Once one is able to open the image that decoder is save in `dsc`
// * @param dsc describe a decoding session. Simply a pointer to an `lv_img_decoder_dsc_t` variable.
// * @param src the image source. Can be
// *  1) File name: E.g. "S:folder/img1.png" (The drivers needs to registered via `lv_fs_add_drv()`)
// *  2) Variable: Pointer to an `lv_img_dsc_t` variable
// *  3) Symbol: E.g. `LV_SYMBOL_OK`
// * @param style the style of the image
// * @return LV_RES_OK: opened the image. `dsc->img_data` and `dsc->header` are set.
// *         LV_RES_INV: none of the registered image decoders were able to open the image.
// */
//lv_res_t lv_img_decoder_open(lv_img_decoder_dsc_t * dsc, const void * src, const lv_style_t * style);

///**
// * Read a line from an opened image
// * @param dsc pointer to `lv_img_decoder_dsc_t` used in `lv_img_decoder_open`
// * @param x start X coordinate (from left)
// * @param y start Y coordinate (from top)
// * @param len number of pixels to read
// * @param buf store the data here
// * @return LV_RES_OK: success; LV_RES_INV: an error occurred
// */
//lv_res_t lv_img_decoder_read_line(lv_img_decoder_dsc_t * dsc, lv_coord_t x, lv_coord_t y, lv_coord_t len,
//                                  uint8_t * buf);

///**
// * Close a decoding session
// * @param dsc pointer to `lv_img_decoder_dsc_t` used in `lv_img_decoder_open`
// */
//void lv_img_decoder_close(lv_img_decoder_dsc_t * dsc);

///**
// * Create a new image decoder
// * @return pointer to the new image decoder
// */
//lv_img_decoder_t * lv_img_decoder_create(void);

///**
// * Delete an image decoder
// * @param decoder pointer to an image decoder
// */
//void lv_img_decoder_delete(lv_img_decoder_t * decoder);

///**
// * Set a callback to get information about the image
// * @param decoder pointer to an image decoder
// * @param info_cb a function to collect info about an image (fill an `lv_img_header_t` struct)
// */
//void lv_img_decoder_set_info_cb(lv_img_decoder_t * decoder, lv_img_decoder_info_f_t info_cb);

///**
// * Set a callback to open an image
// * @param decoder pointer to an image decoder
// * @param open_cb a function to open an image
// */
//void lv_img_decoder_set_open_cb(lv_img_decoder_t * decoder, lv_img_decoder_open_f_t open_cb);

///**
// * Set a callback to a decoded line of an image
// * @param decoder pointer to an image decoder
// * @param read_line_cb a function to read a line of an image
// */
//void lv_img_decoder_set_read_line_cb(lv_img_decoder_t * decoder, lv_img_decoder_read_line_f_t read_line_cb);

///**
// * Set a callback to close a decoding session. E.g. close files and free other resources.
// * @param decoder pointer to an image decoder
// * @param close_cb a function to close a decoding session
// */
//void lv_img_decoder_set_close_cb(lv_img_decoder_t * decoder, lv_img_decoder_close_f_t close_cb);

/**********************
 *      MACROS
 **********************/

#endif /*LV_TEMPL_H*/
