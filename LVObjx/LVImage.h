/**
 * @file lv_img.h
 *
 */

#ifndef LVIMG_H
#define LVIMG_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_objx/lv_img.h>

#if LV_USE_IMG != 0

#include "../LVCore/LVObject.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
/*Data of image*/
class LVImage
        : public LVObject
        , public LVFakeMemHeader<lv_img_ext_t>
        , public lv_img_ext_t
{
    LV_OBJECT(LVImage,lv_img_create,lv_img_ext_t)
public:

    /*Styles*/
    enum Styles : lv_img_style_t
    {
        STYLE_MAIN = LV_IMG_STYLE_MAIN,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create an image objects
     * @param par pointer to an object, it will be the parent of the new button
     * @param copy pointer to a image object, if not NULL then the new object will be copied from it
     * @return pointer to the created image
     */
    //LVImage(LVObject * par, const LVImage * copy);
    LVImage(const void * src_img,LVObject * parent, const LVImage * copy)
        :LVImage(parent,copy)
    {
        setSrc(src_img);
    }

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set the pixel map to display by the image
     * @param img pointer to an image object
     * @param data the image data
     */
    void setSrc(const void * src_img)
    {
        lv_img_set_src(this,src_img);
    }

    /**
     * Enable the auto size feature.
     * If enabled the object size will be same as the picture size.
     * @param img pointer to an image
     * @param en true: auto size enable, false: auto size disable
     */
    void setAutoSize(bool autosize_en)
    {
        lv_img_set_auto_size(this,autosize_en);
    }

    /**
     * Set an offset for the source of an image.
     * so the image will be displayed from the new origin.
     * @param img pointer to an image
     * @param x: the new offset along x axis.
     */
    void setOffsetX(LVCoord x)
    {
        lv_img_set_offset_x(this,x);
    }

    /**
     * Set an offset for the source of an image.
     * so the image will be displayed from the new origin.
     * @param img pointer to an image
     * @param y: the new offset along y axis.
     */
    void setOffsetY(LVCoord y)
    {
        lv_img_set_offset_y(this,y);
    }

    void setOffset(LVCoord x,LVCoord y)
    {
        lv_img_set_offset_x(this,x);
        lv_img_set_offset_y(this,y);
    }
    void setOffset(const LVPoint& p)
    {
        setOffset(p.x,p.y);
    }

    /**
     * Set the style of an image
     * @param img pointer to an image object
     * @param type which style should be set (can be only `LV_IMG_STYLE_MAIN`)
     * @param style pointer to a style
     */
    void setStyle(const LVStyle * style,Styles type = STYLE_MAIN)
    {
        lv_img_set_style(this,type,style);
    }

    /*=====================
     * Getter functions
     *====================*/

    /**
     * Get the source of the image
     * @param img pointer to an image object
     * @return the image source (symbol, file name or C array)
     */
    const void * getSrc()
    {
        return lv_img_get_src(this);
    }

    /**
     * Get the name of the file set for an image
     * @param img pointer to an image
     * @return file name
     */
    const char * getFileName()
    {
        return lv_img_get_file_name(this);
    }

    /**
     * Get the auto size enable attribute
     * @param img pointer to an image
     * @return true: auto size is enabled, false: auto size is disabled
     */
    bool getAutoSize()
    {
        return lv_img_get_auto_size(this);
    }

    /**
     * Get the offset.x attribute of the img object.
     * @param img pointer to an image
     * @return offset.x value.
     */
    LVCoord getOffsetX()
    {
        return lv_img_get_offset_x(this);
    }

    /**
     * Get the offset.y attribute of the img object.
     * @param img pointer to an image
     * @return offset.y value.
     */
    LVCoord getOffsetY()
    {
        return lv_img_get_offset_y(this);
    }

    /**
     * Get the style of an image object
     * @param img pointer to an image object
     * @param type which style should be get (can be only `LV_IMG_STYLE_MAIN`)
     * @return pointer to the image's style
     */
    const LVStyle * getStyle(Styles type = STYLE_MAIN)
    {
        return (const LVStyle *)lv_img_get_style(this,type);
    }

    //TODO:获取图像类型
    // int getSrcType();

};
/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_IMG*/

#endif /*LVIMG_H*/
