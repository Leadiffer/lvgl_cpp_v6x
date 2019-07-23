/**
 * @file lv_canvas.h
 *
 */

#ifndef LVCANVAS_H
#define LVCANVAS_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_canvas.h>

#if LV_USE_CANVAS != 0

#include "../LVCore/LVObject.h"
#include "../LVDraw/LVImageDecoder.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of canvas*/

class LVCanvas
        : public LVObject
        , public LVFakeMemHeader<lv_canvas_ext_t>
        , public lv_canvas_ext_t
{
    LV_OBJECT(LVCanvas,lv_canvas_create,lv_canvas_ext_t)

public:

    /*Styles*/
    enum Styles : lv_canvas_style_t
    {
        STYLE_MAIN = LV_CANVAS_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a canvas object
     * @param par pointer to an object, it will be the parent of the new canvas
     * @param copy pointer to a canvas object, if not NULL then the new object will be copied from it
     * @return pointer to the created canvas
     */
    //LVCanvas(LVObject * parent, const LVCanvas * copy);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set a buffer for the canvas.
     * @param buf a buffer where the content of the canvas will be.
     * The required size is (lv_img_color_format_get_px_size(cf) * w * h) / 8)
     * It can be allocated with `lv_mem_alloc()` or
     * it can be statically allocated array (e.g. static lv_color_t buf[100*50]) or
     * it can be an address in RAM or external SRAM
     * @param canvas pointer to a canvas object
     * @param w width of the canvas
     * @param h height of the canvas
     * @param cf color format. `LV_IMG_CF_...`
     */
    void setBuffer(void * buf, LVCoord w, LVCoord h, lv_img_cf_t cf)
    {
        lv_canvas_set_buffer(this,buf,w,h,cf);
    }

    /**
     * Set the color of a pixel on the canvas
     * @param canvas
     * @param x x coordinate of the point to set
     * @param y x coordinate of the point to set
     * @param c color of the point
     */
    void setPx(LVCoord x, LVCoord y, LVColor c)
    {
        lv_canvas_set_px(this,x,y,c);
    }

    /**
     * Set the palette color of a canvas with index format. Valid only for `LV_IMG_CF_INDEXED1/2/4/8`
     * @param canvas pointer to canvas object
     * @param id the palette color to set:
     *   - for `LV_IMG_CF_INDEXED1`: 0..1
     *   - for `LV_IMG_CF_INDEXED2`: 0..3
     *   - for `LV_IMG_CF_INDEXED4`: 0..15
     *   - for `LV_IMG_CF_INDEXED8`: 0..255
     * @param c the color to set
     */
    void setPalette(uint8_t id, LVColor c)
    {
        lv_canvas_set_palette(this,id,c);
    }

    /**
     * Set a style of a canvas.
     * @param canvas pointer to canvas object
     * @param type which style should be set
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style , Styles type = STYLE_MAIN)
    {
        lv_canvas_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the color of a pixel on the canvas
     * @param canvas
     * @param x x coordinate of the point to set
     * @param y x coordinate of the point to set
     * @return color of the point
     */
    LVColor getPx(LVCoord x, LVCoord y)
    {
        return lv_canvas_get_px(this,x,y);
    }

    /**
     * Get the image of the canvas as a pointer to an `lv_img_dsc_t` variable.
     * @param canvas pointer to a canvas object
     * @return pointer to the image descriptor.
     */
    LVImageDsc * getImage()
    {
        return (LVImageDsc *)lv_canvas_get_img(this);
    }

    /**
     * Get style of a canvas.
     * @param canvas pointer to canvas object
     * @param type which style should be get
     * @return style pointer to the style
     */
    const LVStyle * getStyle(Styles type = STYLE_MAIN)
    {
        return (const LVStyle *)lv_canvas_get_style(this,type);
    }

    /*=====================
     * Other functions
     *====================*/

    /**
     * Copy a buffer to the canvas
     * @param canvas pointer to a canvas object
     * @param to_copy buffer to copy. The color format has to match with the canvas's buffer color
     * format
     * @param x left side of the destination position
     * @param y top side of the destination position
     * @param w width of the buffer to copy
     * @param h height of the buffer to copy
     */
    void copyBuffer(const void * to_copy, LVCoord x, LVCoord y, LVCoord w, LVCoord h)
    {
        lv_canvas_copy_buf(this,to_copy,x,y,w,h);
    }

    /**
     * Rotate and image and store the result on a canvas.
     * @param canvas pointer to a canvas object
     * @param img pointer to an image descriptor.
     *             Can be the image descriptor of an other canvas too (`lv_canvas_get_img()`).
     * @param angle the angle of rotation (0..360);
     * @param offset_x offset X to tell where to put the result data on destination canvas
     * @param offset_y offset X to tell where to put the result data on destination canvas
     * @param pivot_x pivot X of rotation. Relative to the source canvas
     *                Set to `source width / 2` to rotate around the center
     * @param pivot_y pivot Y of rotation. Relative to the source canvas
     *                Set to `source height / 2` to rotate around the center
     */
    void rotate(LVImageDsc * img, int16_t angle, LVCoord offset_x, LVCoord offset_y, int32_t pivot_x, int32_t pivot_y)
    {
        lv_canvas_rotate(this,img,angle,offset_x,offset_y,pivot_x,pivot_y);
    }

    /**
     * Fill the canvas with color
     * @param canvas pointer to a canvas
     * @param color the background color
     */
    void fill_bg(LVColor color)
    {
        lv_canvas_fill_bg(this,color);
    }

    /**
     * Draw a rectangle on the canvas
     * @param canvas pointer to a canvas object
     * @param x left coordinate of the rectangle
     * @param y top coordinate of the rectangle
     * @param w width of the rectangle
     * @param h height of the rectangle
     * @param style style of the rectangle (`body` properties are used except `padding`)
     */
    void drawRect(LVCoord x, LVCoord y, LVCoord w, LVCoord h, const LVStyle * style)
    {
        lv_canvas_draw_rect(this, x, y, w, h, style);
    }

    /**
     * Draw a text on the canvas.
     * @param canvas pointer to a canvas object
     * @param x left coordinate of the text
     * @param y top coordinate of the text
     * @param max_w max width of the text. The text will be wrapped to fit into this size
     * @param style style of the text (`text` properties are used)
     * @param txt text to display
     * @param align align of the text (`LV_LABEL_ALIGN_LEFT/RIGHT/CENTER`)
     */
    void drawText(LVCoord x, LVCoord y, LVCoord max_w, const LVStyle * style,
                             const char * txt, lv_label_align_t align)
    {
        lv_canvas_draw_text(this, x, y, max_w, style, txt, align);
    }

    /**
     * Draw an image on the canvas
     * @param canvas pointer to a canvas object
     * @param src image source. Can be a pointer an `lv_img_dsc_t` variable or a path an image.
     * @param style style of the image (`image` properties are used)
     */
    void drawImage(LVCoord x, LVCoord y, const void * src, const LVStyle * style)
    {
        lv_canvas_draw_img(this,x,y,src,style);
    }

    /**
     * Draw a line on the canvas
     * @param canvas pointer to a canvas object
     * @param points point of the line
     * @param point_cnt number of points
     * @param style style of the line (`line` properties are used)
     */
    void drawLine(const LVPoint * points, uint32_t point_cnt, const LVStyle * style)
    {
        lv_canvas_draw_line(this,points,point_cnt,style);
    }

    /**
     * Draw a polygon on the canvas
     * @param canvas pointer to a canvas object
     * @param points point of the polygon
     * @param point_cnt number of points
     * @param style style of the polygon (`body.main_color` and `body.opa` is used)
     */
    void drawPolygon(const LVPoint * points, uint32_t point_cnt, const LVStyle * style)
    {
        lv_canvas_draw_polygon(this,points,point_cnt,style);
    }

    /**
     * Draw an arc on the canvas
     * @param canvas pointer to a canvas object
     * @param x origo x  of the arc
     * @param y origo y of the arc
     * @param r radius of the arc
     * @param start_angle start angle in degrees
     * @param end_angle end angle in degrees
     * @param style style of the polygon (`body.main_color` and `body.opa` is used)
     */
    void drawArc(LVCoord x, LVCoord y, LVCoord r, int32_t start_angle,
                            int32_t end_angle, const LVStyle * style)
    {
        lv_canvas_draw_arc(this,x,y,r,start_angle,end_angle,style);
    }

};
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_CANVAS*/

#endif /*LVCANVAS_H*/
