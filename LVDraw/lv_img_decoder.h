/**
 * @file lv_img_decoder.h
 *
 */

#ifndef LV_IMG_DEOCER_H
#define LV_IMG_DEOCER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_conf.h"
#else
#include "../../../lv_conf.h"
#endif

#include <stdint.h>
#include "../lv_misc/lv_fs.h"
#include "../lv_misc/lv_types.h"
#include "../lv_misc/lv_area.h"
#include "../lv_core/lv_style.h"

/*********************
 *      DEFINES
 *********************/
/*If image pixels contains alpha we need to know how much byte is a pixel*/
#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8
#define LV_IMG_PX_SIZE_ALPHA_BYTE 2
#elif LV_COLOR_DEPTH == 16
#define LV_IMG_PX_SIZE_ALPHA_BYTE 3
#elif LV_COLOR_DEPTH == 32
#define LV_IMG_PX_SIZE_ALPHA_BYTE 4
#endif


#define LV_IMG_DECODER_OPEN_FAIL ((void *)(-1))

/**********************
 *      TYPEDEFS
 **********************/

enum {
    LV_IMG_SRC_VARIABLE,
    LV_IMG_SRC_FILE,
    LV_IMG_SRC_SYMBOL,
    LV_IMG_SRC_UNKNOWN,
};

typedef uint8_t lv_img_src_t;

typedef struct
{

    /* The first 8 bit is very important to distinguish the different source types.
     * For more info see `lv_img_get_src_type()` in lv_img.c */
    uint32_t cf : 5;          /* Color format: See `lv_img_color_format_t`*/
    uint32_t always_zero : 3; /*It the upper bits of the first byte. Always zero to look like a
                                 non-printable character*/

    uint32_t reserved : 2; /*Reserved to be used later*/

    uint32_t w : 11; /*Width of the image map*/
    uint32_t h : 11; /*Height of the image map*/
} lv_img_header_t;

/*Image color format*/
enum {
    LV_IMG_CF_UNKNOWN = 0,

    LV_IMG_CF_RAW,       /*Contains the file as it is. Needs custom decoder function*/
    LV_IMG_CF_RAW_ALPHA, /*Contains the file as it is. The image has alpha. Needs custom decoder
                            function*/
    LV_IMG_CF_RAW_CHROMA_KEYED, /*Contains the file as it is. The image is chroma keyed. Needs
                                   custom decoder function*/

    LV_IMG_CF_TRUE_COLOR,       /*Color format and depth should match with LV_COLOR settings*/
    LV_IMG_CF_TRUE_COLOR_ALPHA, /*Same as `LV_IMG_CF_TRUE_COLOR` but every pixel has an alpha byte*/
    LV_IMG_CF_TRUE_COLOR_CHROMA_KEYED, /*Same as `LV_IMG_CF_TRUE_COLOR` but LV_COLOR_TRANSP pixels
                                          will be transparent*/

    LV_IMG_CF_INDEXED_1BIT, /*Can have 2 different colors in a palette (always chroma keyed)*/
    LV_IMG_CF_INDEXED_2BIT, /*Can have 4 different colors in a palette (always chroma keyed)*/
    LV_IMG_CF_INDEXED_4BIT, /*Can have 16 different colors in a palette (always chroma keyed)*/
    LV_IMG_CF_INDEXED_8BIT, /*Can have 256 different colors in a palette (always chroma keyed)*/

    LV_IMG_CF_ALPHA_1BIT, /*Can have one color and it can be drawn or not*/
    LV_IMG_CF_ALPHA_2BIT, /*Can have one color but 4 different alpha value*/
    LV_IMG_CF_ALPHA_4BIT, /*Can have one color but 16 different alpha value*/
    LV_IMG_CF_ALPHA_8BIT, /*Can have one color but 256 different alpha value*/
};
typedef uint8_t lv_img_cf_t;

/* Image header it is compatible with
 * the result image converter utility*/
typedef struct
{
    lv_img_header_t header;
    uint32_t data_size;
    const uint8_t * data;
} lv_img_dsc_t;

/* Decoder function definitions */

struct _lv_img_decoder;
struct _lv_img_decoder_dsc;

/**
 * Get info from an image and store in the `header`
 * @param src the image source. Can be a pointer to a C array or a file name (Use
 * `lv_img_src_get_type` to determine the type)
 * @param header store the info here
 * @return LV_RES_OK: info written correctly; LV_RES_INV: failed
 */
typedef lv_res_t (*lv_img_decoder_info_f_t)(struct _lv_img_decoder * decoder, const void * src, lv_img_header_t * header);

/**
 * Open an image for decoding. Prepare it as it is required to read it later
 * @param src the image source. Can be a pointer to a C array or a file name (Use
 * `lv_img_src_get_type` to determine the type)
 * @param style the style of image (maybe it will be required to determine a color or something)
 * @return there are 3 possible return values:
 *    1) buffer with the decoded image
 *    2) if can decode the whole image NULL. decoder_read_line will be called to read the image
 * line-by-line
 *    3) LV_IMG_DECODER_OPEN_FAIL if the image format is unknown to the decoder or an
 * error occurred
 */
typedef const uint8_t * (*lv_img_decoder_open_f_t)(struct _lv_img_decoder * decoder, struct _lv_img_decoder_dsc * dsc);

/**
 * Decode `len` pixels starting from the given `x`, `y` coordinates and store them in `buf`.
 * Required only if the "open" function can't return with the whole decoded pixel array.
 * @param x start x coordinate
 * @param y start y coordinate
 * @param len number of pixels to decode
 * @param buf a buffer to store the decoded pixels
 * @return LV_RES_OK: ok; LV_RES_INV: failed
 */
typedef lv_res_t (*lv_img_decoder_read_line_f_t)(struct _lv_img_decoder * decoder, struct _lv_img_decoder_dsc * dsc,
                                                 lv_coord_t x, lv_coord_t y, lv_coord_t len, uint8_t * buf);

/**
 * Close the pending decoding. Free resources etc.
 */
typedef void (*lv_img_decoder_close_f_t)(struct _lv_img_decoder * decoder, struct _lv_img_decoder_dsc * dsc);

typedef struct _lv_img_decoder {
    lv_img_decoder_info_f_t info_cb;
    lv_img_decoder_open_f_t open_cb;
    lv_img_decoder_read_line_f_t read_line_cb;
    lv_img_decoder_close_f_t close_cb;

#if LV_USE_USER_DATA
    lv_img_decoder_user_data_t user_data;
#endif
}lv_img_decoder_t;


typedef struct _lv_img_decoder_dsc {
    lv_img_decoder_t * decoder;
    const lv_style_t * style;
    const void * src;
    lv_img_src_t src_type;
    lv_img_header_t header;

#if LV_USE_USER_DATA
    void * user_data;
#endif
}lv_img_decoder_dsc_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the image decoder module
 */
void lv_img_decoder_init(void);

/**
 * Get information about an image.
 * Try the created image decoder one by one. Once one is able to get info that info will be used.
 * @param src the image source. Can be
 *  1) File name: E.g. "S:folder/img1.png" (The drivers needs to registered via `lv_fs_add_drv()`)
 *  2) Variable: Pointer to an `lv_img_dsc_t` variable
 *  3) Symbol: E.g. `LV_SYMBOL_OK`
 * @param header the image info will be stored here
 * @return LV_RES_OK: success; LV_RES_INV: wasn't able to get info about the image
 */
lv_res_t lv_img_decoder_get_info(const char * src, lv_img_header_t * header);

/**
 * Open an image.
 * Try the created image decoder one by one. Once one is able to open the image that decoder is save in `dsc`
 * @param dsc describe a decoding session. Simply a pointer to an `lv_img_decoder_dsc_t` variable.
 * @param src the image source. Can be
 *  1) File name: E.g. "S:folder/img1.png" (The drivers needs to registered via `lv_fs_add_drv()`)
 *  2) Variable: Pointer to an `lv_img_dsc_t` variable
 *  3) Symbol: E.g. `LV_SYMBOL_OK`
 * @param style the style of the image
 * @return LV_IMG_DECODER_OPEN_FAIL: can open the image
 *         NULL: the image is opened but `lv_img_decoder_read_line` needs to be used to get the info line by line
 *         Else: a pointer to a buffer which holds the uncompressed pixels of the image
 */
const uint8_t * lv_img_decoder_open(lv_img_decoder_dsc_t * dsc, const void * src, const lv_style_t * style);

/**
 * Read a line from an opened image
 * @param dsc pointer to `lv_img_decoder_dsc_t` used in `lv_img_decoder_open`
 * @param x start X coordinate (from left)
 * @param y start Y coordinate (from top)
 * @param len number of pixels to read
 * @param buf store the data here
 * @return LV_RES_OK: success; LV_RES_INV: an error occurred
 */
lv_res_t lv_img_decoder_read_line(lv_img_decoder_dsc_t * dsc, lv_coord_t x, lv_coord_t y, lv_coord_t len, uint8_t * buf);

/**
 * Close a decoding session
 * @param dsc pointer to `lv_img_decoder_dsc_t` used in `lv_img_decoder_open`
 */
void lv_img_decoder_close(lv_img_decoder_dsc_t * dsc);

/**
 * Create a new image decoder
 * @return pointer to the new image decoder
 */
lv_img_decoder_t * lv_img_decoder_create(void);

/**
 * Delete an image decoder
 * @param decoder pointer to an image decoder
 */
void lv_img_decoder_delete(lv_img_decoder_t * decoder);

/**
 * Set a callback to get information about the image
 * @param decoder pointer to an image decoder
 * @param info_cb a function to collect info about an image (fill an `lv_img_header_t` struct)
 */
void lv_img_decoder_set_info_cb(lv_img_decoder_t * decoder, lv_img_decoder_info_f_t info_cb);

/**
 * Set a callback to open an image
 * @param decoder pointer to an image decoder
 * @param open_cb a function to open an image
 */
void lv_img_decoder_set_open_cb(lv_img_decoder_t * decoder, lv_img_decoder_open_f_t open_cb);

/**
 * Set a callback to a decoded line of an image
 * @param decoder pointer to an image decoder
 * @param read_line_cb a function to read a line of an image
 */
void lv_img_decoder_set_read_line_cb(lv_img_decoder_t * decoder, lv_img_decoder_read_line_f_t read_line_cb);

/**
 * Set a callback to close a decoding session. E.g. close files and free other resources.
 * @param decoder pointer to an image decoder
 * @param close_cb a function to close a decoding session
 */
void lv_img_decoder_set_close_cb(lv_img_decoder_t * decoder, lv_img_decoder_close_f_t close_cb);

/**
 * Set a custom user data in an image decoder.
 * @param decoder pointer to an image decoder
 * @param user_data the user data to set
 */
static inline void lv_img_decoder_set_user_data(lv_img_decoder_t * decoder, lv_img_decoder_t user_data)
{
    memcpy(&decoder->user_data, &user_data, sizeof(user_data));
}

/**
 * Get the user data
 * @param decoder pointer to an image decoder
 * @return the user data
 */
static inline lv_img_decoder_user_data_t lv_img_decoder_get_user_data(lv_img_decoder_t * decoder)
{
    return decoder->user_data;
}

/**
 * Get a pointer to the user data
 * @param decoder pointer to an image decoder
 * @return pointer to the user data
 */
static inline lv_img_decoder_user_data_t * lv_img_decoder_get_user_data_ptr(lv_img_decoder_t * decoder)
{
    return &decoder->user_data;
}

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TEMPL_H*/
