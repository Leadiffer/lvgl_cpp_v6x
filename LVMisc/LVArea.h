/**
 * @file LVArea.h
 *
 */

#ifndef LVAREA_H
#define LVAREA_H

/*********************
 *      INCLUDES
 *********************/
#include <math.h>
#include <lv_misc/lv_area.h>
#include "LVMemory.h"

/*********************
 *      DEFINES
 *********************/


/**********************
 *      TYPEDEFS
 **********************/
using LVCoord = lv_coord_t;

class LVPoint : public lv_point_t
{
    LV_MEMORY
public:
    LVPoint(LVCoord x = LV_COORD_MIN,LVCoord y = LV_COORD_MIN)
    {
        this->x = x;
        this->y = y;
    }

    LVPoint(const lv_point_t & other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    LVPoint(const LVPoint & other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    /**********************
     *      ENHANCE
     **********************/

    bool isNull() const
    {
        return x==LV_COORD_MIN && y ==LV_COORD_MIN;
    }

    LVPoint & operator =(const LVPoint & p2 ) { this->x = p2.x ; this->y = p2.y; return *this; }

    inline LVPoint & operator*=(float factor)  { x = std::round(x*factor); y=std::round(y*factor); return *this; }
    inline LVPoint & operator*=(double factor) { x = std::round(x*factor); y=std::round(y*factor); return *this; }
    inline LVPoint & operator*=(int factor)    { x *= std::round(x*factor); y=std::round(y*factor); return *this; }
    inline LVPoint & operator+=(const LVPoint &p2) { x += p2.x ; y += p2.y; return *this; }
    inline LVPoint & operator-=(const LVPoint &p2) { x -= p2.x ; y -= p2.y; return *this; }
    inline LVPoint & operator/=(double divisor) { x = std::round(x/divisor); y=std::round(y/divisor); return *this; }

    friend inline bool operator==(const LVPoint &p1, const LVPoint &p2);
    friend inline bool operator!=(const LVPoint &p1, const LVPoint &p2);
    friend inline const LVPoint operator*(const LVPoint &point, float factor);
    friend inline const LVPoint operator*(const LVPoint &point, double factor);
    friend inline const LVPoint operator*(const LVPoint &point, int factor);
    friend inline const LVPoint operator*(float factor, const LVPoint &point);
    friend inline const LVPoint operator*(double factor, const LVPoint &point);
    friend inline const LVPoint operator*(int factor, const LVPoint &point);
    friend inline const LVPoint operator+(const LVPoint &p1, const LVPoint &p2);
    friend inline const LVPoint operator+(const LVPoint &point);
    friend inline const LVPoint operator-(const LVPoint &p1, const LVPoint &p2);
    friend inline const LVPoint operator-(const LVPoint &point);
    friend inline const LVPoint operator/(const LVPoint &point, double divisor);

};

inline bool operator==(const LVPoint &p1, const LVPoint &p2) { return p1.x == p2.x && p1.y == p2.y; }
inline bool operator!=(const LVPoint &p1, const LVPoint &p2) { return p1.x != p2.x || p1.y != p2.y; }
inline const LVPoint operator*(const LVPoint &point, float factor) { return LVPoint(point)*=factor; }
inline const LVPoint operator*(const LVPoint &point, double factor){ return LVPoint(point)*=factor; }
inline const LVPoint operator*(const LVPoint &point, int factor)   { return LVPoint(point)*=factor; }
inline const LVPoint operator*(float factor, const LVPoint &point) { return LVPoint(point)*=factor; }
inline const LVPoint operator*(double factor, const LVPoint &point){ return LVPoint(point)*=factor; }
inline const LVPoint operator*(int factor, const LVPoint &point)   { return LVPoint(point)*=factor; }
inline const LVPoint operator+(const LVPoint &p1, const LVPoint &p2){ return LVPoint(p1)+=p2; }
inline const LVPoint operator+(const LVPoint &point)                { return LVPoint(point); }
inline const LVPoint operator-(const LVPoint &p1, const LVPoint &p2){ return LVPoint(p1)-=p2; }
inline const LVPoint operator-(const LVPoint &point)                { return LVPoint(-point.x,-point.y); }
inline const LVPoint operator/(const LVPoint &point, double divisor) { return LVPoint(point)/=divisor; }


class LVArea : public lv_area_t
{
    LV_MEMORY
public:

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Initialize an area
     * @param area_p pointer to an area
     * @param x1 left coordinate of the area
     * @param y1 top coordinate of the area
     * @param x2 right coordinate of the area
     * @param y2 bottom coordinate of the area
     */
    LVArea(LVCoord x1 = 0, LVCoord y1 = 0, LVCoord x2 = 0, LVCoord y2 = 0)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    /**
     * Copy an area
     * @param dest pointer to the destination area
     * @param src pointer to the source area
     */
    LVArea(const LVArea &other)
    {
        this->x1 = other.x1;
        this->y1 = other.y1;
        this->x2 = other.x2;
        this->y2 = other.y2;
    }

    LVArea(const lv_area_t &other)
    {
        this->x1 = other.x1;
        this->y1 = other.y1;
        this->x2 = other.x2;
        this->y2 = other.y2;
    }

    LVArea & operator =(const LVArea &other)
    {
        this->x1 = other.x1;
        this->y1 = other.y1;
        this->x2 = other.x2;
        this->y2 = other.y2;

        return *this;
    }

    LVArea & operator =(const lv_area_t &other)
    {
        this->x1 = other.x1;
        this->y1 = other.y1;
        this->x2 = other.x2;
        this->y2 = other.y2;

        return *this;
    }

    /**
     * Get the width of an area
     * @param area_p pointer to an area
     * @return the width of the area (if x1 == x2 -> width = 1)
     */
    inline LVCoord getWidth() const
    {
        return lv_area_get_width(this);
    }

    /**
     * Get the height of an area
     * @param area_p pointer to an area
     * @return the height of the area (if y1 == y2 -> height = 1)
     */
    inline LVCoord getHeight() const
    {
        return lv_area_get_height(this);
    }

    /**
     * Set the width of an area
     * @param area_p pointer to an area
     * @param w the new width of the area (w == 1 makes x1 == x2)
     */
    inline void setWidth(LVCoord w)
    {
        lv_area_set_width(this,w);
    }

    /**
     * Set the height of an area
     * @param area_p pointer to an area
     * @param h the new height of the area (h == 1 makes y1 == y2)
     */
    inline void setHeight(LVCoord h)
    {
        lv_area_set_height(this,h);
    }

    /**
     * Set the position of an area (width and height will be kept)
     * @param area_p pointer to an area
     * @param x the new x coordinate of the area
     * @param y the new y coordinate of the area
     */
    inline void setPos(const LVCoord x,const LVCoord y)
    {
        lv_area_set_pos(this,x,y);
    }

    /**
     * Return with area of an area (x * y)
     * @param area_p pointer to an area
     * @return size of area
     */
    inline uint32_t getSize() const
    {
        return lv_area_get_size(this);
    }

    /**
     * Get the common parts of two areas
     * @param res_p pointer to an area, the result will be stored her
     * @param a1_p pointer to the first area
     * @param a2_p pointer to the second area
     * @return false: the two area has NO common parts, res_p is invalid
     */
    inline LVArea intersect(const LVArea & a2) const
    {
        LVArea res;
        lv_area_intersect(&res,this,&a2);
        return res;
    }

    /**
     * Join two areas into a third which involves the other two
     * @param res_p pointer to an area, the result will be stored here
     * @param a1_p pointer to the first area
     * @param a2_p pointer to the second area
     */
    inline LVArea join(const LVArea & a2) const
    {
        LVArea res;
        lv_area_join(&res,this,&a2);
        return res;
    }

    /**
     * Check if a point is on an area
     * @param a_p pointer to an area
     * @param p_p pointer to a point
     * @return false:the point is out of the area
     */
    bool isPointOn(const LVPoint& p) const
    {
        return lv_area_is_point_on(this, &p);
    }

    /**
     * Check if two area has common parts
     * @param a1_p pointer to an area.
     * @param a2_p pointer to an other area
     * @return false: a1_p and a2_p has no common parts
     */
    bool isOn(const LVArea & a2) const
    {
        return lv_area_is_on(this,&a2);
    }

    /**
     * Check if an area is fully on an other
     * @param ain_p pointer to an area which could be on aholder_p
     * @param aholder pointer to an area which could involve ain_p
     * @return
     */
    bool isIn(const LVArea & aholder) const
    {
        return lv_area_is_in(this,&aholder);
    }

    /**********************
     *      ENHANCE
     **********************/

    /**
     * @brief isNull size is zero
     * @return
     */
    bool isNull() const
    {
        return x1==x2 || y1 == y2;
    }
};

/**********************
 *      MACROS
 **********************/

#endif //LVAREA_H
