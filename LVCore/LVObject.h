/**
 * @file lv_obj.h
 *
 */

#ifndef LVOBJECT_H
#define LVOBJECT_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_core/lv_obj.h>
#include "../LVMisc/LVMemory.h"
#include "../LVMisc/LVLinkList.h"
#include "../LVMisc/LVTypes.h"
#include "../LVMisc/LVArea.h"
#include "../LVMisc/LVColor.h"
#include "../LVMisc/LVLog.h"
#include "LVCallBack.h"
#include "LVStyle.h"

class LVDisplay;

/*********************
 *      DEFINES
 *********************/

//使用智能指针
#define LV_USE_POINTER 1

#if LV_USE_POINTER >= 1
class LVPointerBase;
#endif


/**********************
 *      TYPEDEFS
 **********************/

#if LV_USE_OBJ_REALIGN
class LVReailgn : public lv_reailgn_t
{
public:
    LVReailgn() {}
};
#endif

class LVObjectType : public lv_obj_type_t
{
public:
    LVObjectType() {}
};

// 禁止对象的拷贝和赋值操作
#define LV_NOCOPY(CLASS) \
    private: \
    CLASS(const CLASS&) = delete; \
    CLASS(CLASS&&) = delete; \
    CLASS& operator = (const CLASS&) = delete;

// LV对象的先祖属性,这里特指几种回调函数
#define LV_ANCESTOR \
    protected: \
    virtual lv_design_cb_t & ancestorDesignCB()override \
    { static lv_design_cb_t l_designCB = nullptr; return l_designCB; } \
    virtual lv_signal_cb_t & ancestorSignalCB()override \
    { static lv_signal_cb_t l_signalCB = nullptr; return l_signalCB; } \
    virtual lv_event_cb_t & ancestorEventCB()override \
    { static lv_event_cb_t l_evenCB = nullptr; return l_evenCB; }

// 定义一个派生类的默认构造函数
/*
    virtual void destroyer() override \
    { \
        lv_mem_free(this);  \
        LV_LOG_INFO(#CLASS" destroyed."); \
    } \
*/

#define LV_OBJX(CLASS,FUNC,ATTR) \
    protected: \
    CLASS(){} \
    virtual uint32_t creator(LVObject * par, const LVObject * copy) override \
    { \
        LVMemory::placementAlloc((lv_obj_t*)this,(ATTR*)this); \
        FUNC(par,copy); \
        LVMemory::resetPlacementAlloc(); \
        if(ext_attr != (ATTR*)this) lvError(#CLASS"::creator : ext_attr(%p) != "#ATTR"(%p)",ext_attr,(ATTR*)this); \
        callbackInit();\
        LV_LOG_INFO(#CLASS" created."); \
        return sizeof(ATTR); \
    } \
    public: \
    CLASS(LVObject* parent,const CLASS* copy = nullptr){creator(parent,copy);} \
    ~CLASS(){destroyer();} \
    private:

// implement object`s comment attribute
// 必须将这个宏放在派生类中的第一行
#define LV_OBJECT(CLASS,FUNC,ATTR) \
    LV_MEMORY \
    LV_NOCOPY(CLASS) \
    LV_ANCESTOR \
    LV_OBJX(CLASS,FUNC,ATTR)


enum DesignMode : lv_design_mode_t
{
    DESIGN_DRAW_MAIN = LV_DESIGN_DRAW_MAIN,
    DESIGN_DRAW_POST = LV_DESIGN_DRAW_POST,
    DESIGN_COVER_CHK = LV_DESIGN_COVER_CHK,
};

enum EventType : lv_event_t
{
    EVENT_PRESSED             = LV_EVENT_PRESSED,               /*The object has been pressed*/
    EVENT_PRESSING            = LV_EVENT_PRESSING,              /*The object is being pressed (called continuously while pressing)*/
    EVENT_PRESS_LOST          = LV_EVENT_PRESS_LOST,            /*Still pressing but slid from the objects*/
    EVENT_SHORT_CLICKED       = LV_EVENT_SHORT_CLICKED,         /*Released before long press time. Not called if dragged.*/
    EVENT_LONG_PRESSED        = LV_EVENT_LONG_PRESSED,          /*Pressing for `LV_INDEV_LONG_PRESS_TIME` time.  Not called if dragged.*/
    EVENT_LONG_PRESSED_REPEAT = LV_EVENT_LONG_PRESSED_REPEAT,   /*Called after `LV_INDEV_LONG_PRESS_TIME` in every
                                                                `LV_INDEV_LONG_PRESS_REP_TIME` ms.  Not called if dragged.*/
    EVENT_CLICKED             = LV_EVENT_CLICKED,               /*Called on release if not dragged (regardless to long press)*/
    EVENT_RELEASED            = LV_EVENT_RELEASED,              /*Called in every cases when the object has been released*/
    EVENT_DRAG_BEGIN          = LV_EVENT_DRAG_BEGIN,
    EVENT_DRAG_END            = LV_EVENT_DRAG_END,
    EVENT_DRAG_THROW_BEGIN    = LV_EVENT_DRAG_THROW_BEGIN,
    EVENT_KEY                 = LV_EVENT_KEY,
    EVENT_FOCUSED             = LV_EVENT_FOCUSED,
    EVENT_DEFOCUSED           = LV_EVENT_DEFOCUSED,
    EVENT_VALUE_CHANGED       = LV_EVENT_VALUE_CHANGED,
    EVENT_INSERT              = LV_EVENT_INSERT,
    //EVENT_SELECTED            = LV_EVENT_SELECTED,
    EVENT_REFRESH             = LV_EVENT_REFRESH,
    EVENT_APPLY               = LV_EVENT_APPLY,                 /*"Ok", "Apply" or similar specific button has clicked*/
    EVENT_CANCEL              = LV_EVENT_CANCEL,                /*"Close", "Cancel" or similar specific button has clicked*/
    EVENT_DELETE              = LV_EVENT_DELETE,
};

enum SignalType : lv_signal_t
{
    /*General signals*/              /*General signals*/
    SIGNAL_CLEANUP                 = LV_SIGNAL_CLEANUP,
    SIGNAL_CHILD_CHG               = LV_SIGNAL_CHILD_CHG,
    SIGNAL_CORD_CHG                = LV_SIGNAL_CORD_CHG,
    SIGNAL_PARENT_SIZE_CHG         = LV_SIGNAL_PARENT_SIZE_CHG,
    SIGNAL_STYLE_CHG               = LV_SIGNAL_STYLE_CHG,
    SIGNAL_REFR_EXT_DRAW_PAD       = LV_SIGNAL_REFR_EXT_DRAW_PAD,
    SIGNAL_GET_TYPE                = LV_SIGNAL_GET_TYPE,

    /*Input device related*/         /*Input device related*/
    SIGNAL_PRESSED                 = LV_SIGNAL_PRESSED,
    SIGNAL_PRESSING                = LV_SIGNAL_PRESSING,
    SIGNAL_PRESS_LOST              = LV_SIGNAL_PRESS_LOST,
    SIGNAL_RELEASED                = LV_SIGNAL_RELEASED,
    SIGNAL_LONG_PRESS              = LV_SIGNAL_LONG_PRESS,
    SIGNAL_LONG_PRESS_REP          = LV_SIGNAL_LONG_PRESS_REP,
    SIGNAL_DRAG_BEGIN              = LV_SIGNAL_DRAG_BEGIN,
    SIGNAL_DRAG_END                = LV_SIGNAL_DRAG_END,

    /*Group related*/                /*Group related*/
    SIGNAL_FOCUS                   = LV_SIGNAL_FOCUS,
    SIGNAL_DEFOCUS                 = LV_SIGNAL_DEFOCUS,
    SIGNAL_CONTROL                 = LV_SIGNAL_CONTROL,
    SIGNAL_GET_EDITABLE            = LV_SIGNAL_GET_EDITABLE,
};

enum AlignType : lv_align_t
{
    ALIGN_CENTER           = LV_ALIGN_CENTER,
    ALIGN_IN_TOP_LEFT      = LV_ALIGN_IN_TOP_LEFT,
    ALIGN_IN_TOP_MID       = LV_ALIGN_IN_TOP_MID,
    ALIGN_IN_TOP_RIGHT     = LV_ALIGN_IN_TOP_RIGHT,
    ALIGN_IN_BOTTOM_LEFT   = LV_ALIGN_IN_BOTTOM_LEFT,
    ALIGN_IN_BOTTOM_MID    = LV_ALIGN_IN_BOTTOM_MID,
    ALIGN_IN_BOTTOM_RIGHT  = LV_ALIGN_IN_BOTTOM_RIGHT,
    ALIGN_IN_LEFT_MID      = LV_ALIGN_IN_LEFT_MID,
    ALIGN_IN_RIGHT_MID     = LV_ALIGN_IN_RIGHT_MID,
    ALIGN_OUT_TOP_LEFT     = LV_ALIGN_OUT_TOP_LEFT,
    ALIGN_OUT_TOP_MID      = LV_ALIGN_OUT_TOP_MID,
    ALIGN_OUT_TOP_RIGHT    = LV_ALIGN_OUT_TOP_RIGHT,
    ALIGN_OUT_BOTTOM_LEFT  = LV_ALIGN_OUT_BOTTOM_LEFT,
    ALIGN_OUT_BOTTOM_MID   = LV_ALIGN_OUT_BOTTOM_MID,
    ALIGN_OUT_BOTTOM_RIGHT = LV_ALIGN_OUT_BOTTOM_RIGHT,
    ALIGN_OUT_LEFT_TOP     = LV_ALIGN_OUT_LEFT_TOP,
    ALIGN_OUT_LEFT_MID     = LV_ALIGN_OUT_LEFT_MID,
    ALIGN_OUT_LEFT_BOTTOM  = LV_ALIGN_OUT_LEFT_BOTTOM,
    ALIGN_OUT_RIGHT_TOP    = LV_ALIGN_OUT_RIGHT_TOP,
    ALIGN_OUT_RIGHT_MID    = LV_ALIGN_OUT_RIGHT_MID,
    ALIGN_OUT_RIGHT_BOTTOM = LV_ALIGN_OUT_RIGHT_BOTTOM,
};

enum DragDirection : lv_drag_dir_t
{
    DRAG_HOR = LV_DRAG_DIR_HOR,
    DRAG_VER = LV_DRAG_DIR_VER,
    DRAG_ALL = LV_DRAG_DIR_ALL, /* Should be the bitwise OR of the above */
};

/*Protect some attributes (max. 8 bit)*/
enum ProtectType : lv_protect_t
{
    PROTECT_NONE        = LV_PROTECT_NONE        ,
    PROTECT_CHILD_CHG   = LV_PROTECT_CHILD_CHG   ,   /*Disable the child change signal. Used by the library*/
    PROTECT_PARENT      = LV_PROTECT_PARENT      ,   /*Prevent automatic parent change (e.g. in lv_page)*/
    PROTECT_POS         = LV_PROTECT_POS         ,   /*Prevent automatic positioning (e.g. in lv_cont layout)*/
    PROTECT_FOLLOW      = LV_PROTECT_FOLLOW      ,   /*Prevent the object be followed in automatic ordering (e.g. in
                                                     lv_cont PRETTY layout)*/
    PROTECT_PRESS_LOST  = LV_PROTECT_PRESS_LOST  ,   /*If the `indev` was pressing this object but swiped out while
                                                     pressing do not search other object.*/
    PROTECT_CLICK_FOCUS = LV_PROTECT_CLICK_FOCUS ,   /*Prevent focusing the object by clicking on it*/
};



class LVObject;
using LVDesignCallBack = LVCallBack<bool(LVObject * obj, const LVArea * mask_p, DesignMode mode),bool>;
using LVSignalCallBack = LVCallBack<LVResult(LVObject * obj, SignalType sign, void * param),LVResult>;
using LVEventCallBack = LVCallBack<void(LVObject * obj, EventType event),void>;


/**
 * @brief LVObject的扩展数据成员
 * 由于要配合lvgl的内存布局,所以扩展数据都放在单独的数据类中
 */
class LVObjectEnhance
{
protected:
    LVObjectEnhance()
    {
        m_destructByDelete = 0;
    }

#if LV_USE_POINTER
    /**
     * @brief 智能指针对象数组
     * template< class T> class LVPointer;
     * [p,p,p,p,p,p,p,...]
     */
    LVPointerBase ** m_pointers = nullptr;
#endif

    LVDesignCallBack m_designCallback;
    LVSignalCallBack m_signalCallback;
    LVEventCallBack  m_eventCallback;

    struct
    {
        uint32_t m_destructByDelete:1; //!< 是否被delete操作符清理的
        uint32_t _reserve_:31; //!< 保留
    };
};

/**
 * @brief lv_obj_t 在lvll中的数据节点
 */
class LVObjectNode
        : public lv_obj_t       //!< 实际的lvObj 对象数据
        , public LVLLNodeMeta  //!< lvObj在链表中的元数据
{
protected:
    LVObjectNode() {}
};


/**
 * @brief The LVObject class
 * //NOTE: 禁止LVObject在栈上建立对象,
 * 虽然可以禁止外界访问析构函数,但是使用起来太不方便了,
 * 就靠编程人员来记住这个原则吧
 *
 * LVObject 内存布局
 *                 LVObject                       LVObjectNode         lv_obj_t
 *                 |                              |                    |
 *                 V                              V                    V
 * {LVMemoryHeader:[ (VTable){LVMemoryHeader:[ (lv_obj_t) (LVLLNodeMeta) (LVObjectEnhance) ] } (LVMemoryHeader) ] }
 */
class LVObject
        : public LVObjectEnhance //!< lvgl的扩展属性,放在类继承的第一位
        , public LVFakeMemHeader<LVObjectNode>  //!< LVObjectNode 的假内存块信息,模拟lvgl的内存布局
        , public LVObjectNode   //!< lvObj的数据节点
{
    LV_MEMORY
    LV_NOCOPY(LVObject)

protected:

    //给派生类调用
    LVObject()
    {
        //初始化隐形的 LVMemoryHeader
        LVMemoryEntry * ent = LVMemory::getMemoryEntry(this);
        //虚表指针,再加上LVObjectEnhance的大小
        ent->setSize( (uintptr_t)((LVFakeMemHeader<LVObjectNode>*)this) - (uintptr_t)this );
    }

    virtual uint32_t creator(LVObject * par, const LVObject * copy)
    {
        LVMemory::placementAlloc((lv_obj_t*)this);
        lv_obj_create(par,copy);
        LVMemory::resetPlacementAlloc();
        //记录先祖回调函数
        callbackInit();
        LV_LOG_INFO("LVObject created.");
        return 0;
    }

    virtual void destroyer()
    {
        if(isDestructByDelete()) return;
        setDestructByDelete();
        resetAncestorCB();

        onSignalCleanUp();
        lv_obj_del(this);
    #if LV_USE_POINTER
        //清理智能指针
        cleanPointers();
    #endif

        LV_LOG_INFO("LVObject destroyed.");
    }

    virtual lv_design_cb_t & ancestorDesignCB()
    { static lv_design_cb_t l_designCB = nullptr; return l_designCB; }

    virtual lv_signal_cb_t & ancestorSignalCB()
    { static lv_signal_cb_t l_signalCB = nullptr; return l_signalCB; }

    virtual lv_event_cb_t & ancestorEventCB()
    { static lv_event_cb_t l_evenCB = nullptr; return l_evenCB; }
public:

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Init. the 'lv' library.
     */
    static void init(void)
    {
        lv_init();
    }

    /*--------------------
     * Create and delete
     *-------------------*/

    /**
     * Create a basic object
     * @param parent pointer to a parent object.
     *                  If NULL then a screen will be created
     * @param copy pointer to a base object, if not NULL then the new object will be copied from it
     * @return pointer to the new object
     */
    LVObject(LVObject * parent, const LVObject * copy = nullptr)
        :LVObject()
    {
        //NOTE:此时调用虚拟函数,由于派生类并未初始化好,永远只会调用基类的抽象函数
        //NOTE: 在构造函数中调用虚函数是禁忌
        creator(parent,copy);
    }

    /**
     * Delete 'obj' and all of its children
     * @param obj pointer to an object to delete
     * @return LV_RES_INV because the object is deleted
     */
    virtual ~LVObject()
    {
        //NOTE: 此时调用虚拟函数,由于派生类已经析构了,永远只会调用基类的抽象函数
        //NOTE: 在析构函数中调用虚函数是禁忌
        //NOTE: 在对象清理的过程中,会调用到虚函数
        destroyer();
    }

    /**
     * Delete all children of an object
     * @param obj pointer to an object
     */
    void cleanChildren()
    {
        lv_obj_clean(this);
    }

    /**
     * Mark the object as invalid therefore its current position will be redrawn by 'lv_refr_task'
     * @param obj pointer to an object
     */
    void invalidate()
    {
        lv_obj_invalidate(this);
    }

    /*=====================
     * Setter functions
     *====================*/

    /*--------------------
     * Parent/children set
     *--------------------*/

    /**
     * Set a new parent for an object. Its relative position will be the same.
     * @param obj pointer to an object. Can't be a screen.
     * @param parent pointer to the new parent object. (Can't be NULL)
     */
    void setParent(LVObject * parent)
    {
        lv_obj_set_parent(this, parent);
    }

    /**
     * Move and object to the foreground
     * @param obj pointer to an object
     */
    void moveForeground()
    {
        lv_obj_move_foreground(this);
    }

    /**
     * Move and object to the background
     * @param obj pointer to an object
     */
    void moveBackground()
    {
        lv_obj_move_background(this);
    }

    /*--------------------
     * Coordinate set
     * ------------------*/

    /**
     * Set relative the position of an object (relative to the parent)
     * @param obj pointer to an object
     * @param x new distance from the left side of the parent
     * @param y new distance from the top of the parent
     */
    void setPos(LVCoord x, LVCoord y)
    {
        lv_obj_set_pos(this,x,y);
    }

    /**
     * Set the x coordinate of a object
     * @param obj pointer to an object
     * @param x new distance from the left side from the parent
     */
    void setX(LVCoord x)
    {
        lv_obj_set_x(this,x);
    }

    /**
     * Set the y coordinate of a object
     * @param obj pointer to an object
     * @param y new distance from the top of the parent
     */
    void setY(LVCoord y)
    {
        lv_obj_set_y(this,y);
    }

    /**
     * Set the size of an object
     * @param obj pointer to an object
     * @param w new width
     * @param h new height
     */
    void setSize(LVCoord w, LVCoord h)
    {
        lv_obj_set_size(this,w,h);
    }

    /**
     * Set the width of an object
     * @param obj pointer to an object
     * @param w new width
     */
    void setWidth(LVCoord w)
    {
        lv_obj_set_width(this,w);
    }

    /**
     * Set the height of an object
     * @param obj pointer to an object
     * @param h new height
     */
    void setHeight(LVCoord h)
    {
        lv_obj_set_height(this,h);
    }

    /**
     * Align an object to an other object.
     * @param obj pointer to an object to align
     * @param base pointer to an object (if NULL the parent is used). 'obj' will be aligned to it.
     * @param align type of alignment (see 'lv_align_t' enum)
     * @param x_mod x coordinate shift after alignment
     * @param y_mod y coordinate shift after alignment
     */
    void align(const LVObject * base, AlignType align, LVCoord x_mod = 0, LVCoord y_mod = 0)
    {
        lv_obj_align(this, base, align, x_mod,y_mod);
    }

    void align(AlignType align, LVCoord x_mod = 0, LVCoord y_mod = 0)
    {
        lv_obj_align(this, nullptr, align, x_mod,y_mod);
    }

    /**
     * Align an object to an other object.
     * @param obj pointer to an object to align
     * @param base pointer to an object (if NULL the parent is used). 'obj' will be aligned to it.
     * @param align type of alignment (see 'lv_align_t' enum)
     * @param x_mod x coordinate shift after alignment
     * @param y_mod y coordinate shift after alignment
     */
    void alignOrigo(const LVObject * base, AlignType align, LVCoord x_mod = 0, LVCoord y_mod = 0)
    {
        lv_obj_align_origo(this, base, align, x_mod,y_mod);
    }

    void alignOrigo(AlignType align, LVCoord x_mod = 0, LVCoord y_mod = 0)
    {
        lv_obj_align_origo(this, nullptr, align, x_mod,y_mod);
    }

    /**
     * Realign the object based on the last `lv_obj_align` parameters.
     * @param obj pointer to an object
     */
    void realign()
    {
        lv_obj_realign(this);
    }

    /**
     * Enable the automatic realign of the object when its size has changed based on the last
     * `lv_obj_align` parameters.
     * @param obj pointer to an object
     * @param en true: enable auto realign; false: disable auto realign
     */
    void setAutoRealign(bool en)
    {
        lv_obj_set_auto_realign(this, en);
    }

    #if LV_USE_EXT_CLICK_AREA == LV_EXT_CLICK_AREA_TINY
    /**
     * Set the size of an extended clickable area
     * @param obj pointer to an object
     * @param w extended width to both sides
     * @param h extended height to both sides
     */
    void setExtendedClickableArea(uint8_t w, uint8_t h)
    {
        lv_obj_set_ext_click_area(this, w, h);
    }
    #endif

    #if LV_USE_EXT_CLICK_AREA == LV_EXT_CLICK_AREA_FULL
    /**
     * Set the size of an extended clickable area
     * @param obj pointer to an object
     * @param left extended clickable are on the left [px]
     * @param right extended clickable are on the right [px]
     * @param top extended clickable are on the top [px]
     * @param bottom extended clickable are on the bottom [px]
     */
    void setExtendedClickableArea(LVCoord left, LVCoord right, LVCoord top, LVCoord bottom)
    {
        lv_obj_set_ext_click_area(this, left, right, top, bottom);
    }
    #endif

    /*---------------------
     * Appearance set
     *--------------------*/

    /**
     * Set a new style for an object
     * @param obj pointer to an object
     * @param style_p pointer to the new style
     */
    void setStyle(const LVStyle * style)
    {
        lv_obj_set_style(this , style);
    }

    /**
     * Notify an object about its style is modified
     * @param obj pointer to an object
     */
    void refreshStyle()
    {
        lv_obj_refresh_style(this);
    }

    /**
     * Notify all object if a style is modified
     * @param style pointer to a style. Only the objects with this style will be notified
     *               (NULL to notify all objects)
     */
    static void reportStyleModified(LVStyle * style)
    {
        lv_obj_report_style_mod(style);
    }

    /*-----------------
     * Attribute set
     *----------------*/

    /**
     * Hide an object. It won't be visible and clickable.
     * @param obj pointer to an object
     * @param en true: hide the object
     */
    void setHidden(bool en)
    {
        lv_obj_set_hidden(this, en);
    }

    /**
     * Enable or disable the clicking of an object
     * @param obj pointer to an object
     * @param en true: make the object clickable
     */
    void setClickEnable( bool en)
    {
        lv_obj_set_click(this, en);
    }

    /**
     * Enable to bring this object to the foreground if it
     * or any of its children is clicked
     * @param obj pointer to an object
     * @param en true: enable the auto top feature
     */
    void setTop(bool en)
    {
        lv_obj_set_top(this, en);
    }

    /**
     * Enable the dragging of an object
     * @param obj pointer to an object
     * @param en true: make the object dragable
     */
    void setDrag( bool en)
    {
        lv_obj_set_drag(this, en);
    }

    /**
     * Set the directions an object can be dragged in
     * @param obj pointer to an object
     * @param drag_dir bitwise OR of allowed drag directions
     */
    void setDragDir(DragDirection drag_dir)
    {
        lv_obj_set_drag_dir(this , drag_dir);
    }

    /**
     * Enable the throwing of an object after is is dragged
     * @param obj pointer to an object
     * @param en true: enable the drag throw
     */
    void setDragThrow(bool en)
    {
        lv_obj_set_drag_throw(this, en);
    }

    /**
     * Enable to use parent for drag related operations.
     * If trying to drag the object the parent will be moved instead
     * @param obj pointer to an object
     * @param en true: enable the 'drag parent' for the object
     */
    void setDragParent(bool en)
    {
        lv_obj_set_drag_parent(this, en);
    }

    /**
     * Propagate the events to the parent too
     * @param obj pointer to an object
     * @param en true: enable the event propagation
     */
    void setParentEvent(bool en)
    {
        lv_obj_set_parent_event(this,en);
    }

    /**
     * Set the opa scale enable parameter (required to set opa_scale with `lv_obj_set_opa_scale()`)
     * @param obj pointer to an object
     * @param en true: opa scaling is enabled for this object and all children; false: no opa scaling
     */
    void setOpaScaleEnable(bool en)
    {
        lv_obj_set_opa_scale_enable(this,en);
    }

    /**
     * Set the opa scale of an object
     * @param obj pointer to an object
     * @param opa_scale a factor to scale down opacity [0..255]
     */
    void setOpaScale(LVOpacity opa_scale)
    {
        lv_obj_set_opa_scale(this,opa_scale);
    }

    /**
     * Set a bit or bits in the protect filed
     * @param obj pointer to an object
     * @param prot 'OR'-ed values from `lv_protect_t`
     */
    void setProtect(uint8_t prot)
    {
        lv_obj_set_protect(this , prot);
    }

    /**
     * Clear a bit or bits in the protect filed
     * @param obj pointer to an object
     * @param prot 'OR'-ed values from `lv_protect_t`
     */
    void clearProtect(uint8_t prot)
    {
        lv_obj_clear_protect(this , prot);
    }

    /**
     * Set a an event handler function for an object.
     * Used by the user to react on event which happens with the object.
     * @param obj pointer to an object
     * @param event_cb the new event function
     */
    void setEventCallBack(LVEventCallBack event_cb)
    {
        m_eventCallback = event_cb;
        lv_obj_set_event_cb(this,(lv_event_cb_t)lvObjectEvenCallBackAgency);
    }

    /**
     * Send an event to the object
     * @param obj pointer to an object
     * @param event the type of the event from `lv_event_t`.
     * @param data arbitrary data depending on the object type and the event. (Usually `NULL`)
     * @return LV_RES_OK: `obj` was not deleted in the event; LV_RES_INV: `obj` was deleted in the event
     */
    LVResult eventSend(EventType event, const void * data)
    {
        return (LVResult)lv_event_send(this, event, data);
    }

    /**
     * Call an event function with an object, event, and data.
     * @param event_cb an event callback function
     * @param obj pointer to an object to associate with the event (can be `NULL` to simply call the `event_cb`)
     * @param event an event
     * @param data pointer to a custom data
     * @return LV_RES_OK: `obj` was not deleted in the event; LV_RES_INV: `obj` was deleted in the event
     */
    static LVResult evenSendFunc(lv_event_cb_t event_cb, LVObject * obj, EventType event, const void * data)
    {
        return (LVResult)lv_event_send_func(event_cb, obj, event, data);
    }

    /**
     * Get the `data` parameter of the current event
     * @return the `data` parameter
     */
    static const void * eventGetData()
    {
        return lv_event_get_data();
    }

    /**
     * Set the a signal function of an object. Used internally by the library.
     * Always call the previous signal function in the new.
     * @param obj pointer to an object
     * @param signal_cb the new signal function
     */
    void setSignalCallBack(LVSignalCallBack signal_cb)
    {
        m_signalCallback = signal_cb;
        lv_obj_set_signal_cb(this,(lv_signal_cb_t)lvObjectSignalCallBackAgency);
    }
    //void setSignalCallBack(lv_signal_cb_t signal_cb)
    //{
    //    lv_obj_set_signal_cb(this,signal_cb);
    //}

    /**
     * Send an event to the object
     * @param obj pointer to an object
     * @param event the type of the event from `lv_event_t`.
     */
    void signalSend(lv_signal_t signal, void * param)
    {
        lv_signal_send(this, signal, param);
    }

    /**
     * Set a new design function for an object
     * @param obj pointer to an object
     * @param design_cb the new design function
     */
    void setDesignCallBack(LVDesignCallBack design_cb)
    {
        m_designCallback = design_cb;
        lv_obj_set_design_cb(this,(lv_design_cb_t)lvObjectDesignCallBackAgency);
    }
    //void setDesignCallBack(lv_design_cb_t design_cb)
    //{
    //    lv_obj_set_design_cb(this,design_cb);
    //}

    /*----------------
     * Other set
     *--------------*/

    /**
     * Allocate a new ext. data for an object
     * @param obj pointer to an object
     * @param ext_size the size of the new ext. data
     * @return pointer to the allocated ext
     */
    void * allocateExtAttr(uint16_t ext_size)
    {
        return lv_obj_allocate_ext_attr(this, ext_size);
    }

    /**
     * Send a 'LV_SIGNAL_REFR_EXT_SIZE' signal to the object
     * @param obj pointer to an object
     */
    void refreshExtDrawPad()
    {
        lv_obj_refresh_ext_draw_pad(this);
    }

    /*=======================
     * Getter functions
     *======================*/

    /**
     * Return with the screen of an object
     * @param obj pointer to an object
     * @return pointer to a screen
     */
    LVObject * getScreen()
    {
        return (LVObject *)lv_obj_get_screen(this);
    }

    /**
     * Get the display of an object
     * @param scr pointer to an object
     * @return pointer the object's display
     */
    LVDisplay * getDisplay()
    {
        return (LVDisplay *)lv_obj_get_disp(this);
    }

    /*---------------------
     * Parent/children get
     *--------------------*/

    /**
     * Returns with the parent of an object
     * @param obj pointer to an object
     * @return pointer to the parent of  'obj'
     */
    LVObject * getParent()
    {
        return (LVObject *)lv_obj_get_parent(this);
    }

    /**
     * Iterate through the children of an object (start from the "youngest, lastly created")
     * @param obj pointer to an object
     * @param child NULL at first call to get the next children
     *                  and the previous return value later
     * @return the child after 'act_child' or NULL if no more child
     */
    LVObject * getChild(const LVObject * child)
    {
        return (LVObject *)lv_obj_get_child(this,child);
    }

    /**
     * Iterate through the children of an object (start from the "oldest", firstly created)
     * @param obj pointer to an object
     * @param child NULL at first call to get the next children
     *                  and the previous return value later
     * @return the child after 'act_child' or NULL if no more child
     */
    LVObject * getChildBack(const LVObject * child)
    {
        return (LVObject *)lv_obj_get_child_back(this,child);
    }

    /**
     * Count the children of an object (only children directly on 'obj')
     * @param obj pointer to an object
     * @return children number of 'obj'
     */
    uint16_t countChildren()
    {
        return lv_obj_count_children(this);
    }

    /** Recursively count the children of an object
     * @param obj pointer to an object
     * @return children number of 'obj'
     */
    uint16_t countChildrenRecursive()
    {
        return lv_obj_count_children_recursive(this);
    }

    /*---------------------
     * Coordinate get
     *--------------------*/

    /**
     * Copy the coordinates of an object to an area
     * @param obj pointer to an object
     * @param cords_p pointer to an area to store the coordinates
     */
    LVArea getCoords()
    {
        LVArea cords_p;
        lv_obj_get_coords(this, &cords_p);
        return cords_p;
    }

    /**
     * Get the x coordinate of object
     * @param obj pointer to an object
     * @return distance of 'obj' from the left side of its parent
     */
    LVCoord getX()
    {
        return lv_obj_get_x(this);
    }

    /**
     * Get the y coordinate of object
     * @param obj pointer to an object
     * @return distance of 'obj' from the top of its parent
     */
    LVCoord getY()
    {
        return lv_obj_get_y(this);
    }

    /**
     * Get the width of an object
     * @param obj pointer to an object
     * @return the width
     */
    LVCoord getWidth()
    {
        return lv_obj_get_width(this);
    }

    /**
     * Get the height of an object
     * @param obj pointer to an object
     * @return the height
     */
    LVCoord getHeight()
    {
        return lv_obj_get_height(this);
    }

    /**
     * Get that width reduced by the left and right padding.
     * @param obj pointer to an object
     * @return the width which still fits into the container
     */
    LVCoord getWidthFit()
    {
        return lv_obj_get_width_fit(this);
    }

    /**
     * Get that height reduced by the top an bottom padding.
     * @param obj pointer to an object
     * @return the height which still fits into the container
     */
    LVCoord getHeightFit()
    {
        return lv_obj_get_height_fit(this);
    }

    /**
     * Get the automatic realign property of the object.
     * @param obj pointer to an object
     * @return  true: auto realign is enabled; false: auto realign is disabled
     */
    bool getAutoRealign()
    {
        return lv_obj_get_auto_realign(this);
    }


    #if LV_USE_EXT_CLICK_AREA == LV_EXT_CLICK_AREA_TINY
    /**
     * Get the horizontal padding of extended clickable area
     * @param obj pointer to an object
     * @return the horizontal padding
     */
    uint8_t lv_obj_get_ext_click_pad_hor(const lv_obj_t * obj);

    /**
     * Get the vertical padding of extended clickable area
     * @param obj pointer to an object
     * @return the vertical padding
     */
    uint8_t getExtClickPadVer()
    {
        return lv_obj_get_ext_click_pad_ver(this);
    }

    #endif

    #if LV_USE_EXT_CLICK_AREA == LV_EXT_CLICK_AREA_FULL
    /**
     * Get the horizontal padding of extended clickable area
     * @param obj pointer to an object
     * @return the horizontal padding
     */
    const LVArea * getExtClickPad()
    {
        return lv_obj_get_ext_click_pad(this);
    }
    #endif

    /**
     * Get the extended size attribute of an object
     * @param obj pointer to an object
     * @return the extended size attribute
     */
    LVCoord getExtDrawPad()
    {
        return lv_obj_get_ext_draw_pad(this);
    }

    /*-----------------
     * Appearance get
     *---------------*/

    /**
     * Get the style pointer of an object (if NULL get style of the parent)
     * @param obj pointer to an object
     * @return pointer to a style
     */
    const LVStyle * getStyle()
    {
        return (const LVStyle *)lv_obj_get_style(this);
    }

    /*-----------------
     * Attribute get
     *----------------*/

    /**
     * Get the hidden attribute of an object
     * @param obj pointer to an object
     * @return true: the object is hidden
     */
    bool getHidden()
    {
        return lv_obj_get_hidden(this);
    }

    /**
     * Get the click enable attribute of an object
     * @param obj pointer to an object
     * @return true: the object is clickable
     */
    bool getClickEnable()
    {
        return lv_obj_get_click(this);
    }

    /**
     * Get the top enable attribute of an object
     * @param obj pointer to an object
     * @return true: the auto top feature is enabled
     */
    bool getTop()
    {
        return lv_obj_get_top(this);
    }

    /**
     * Get the drag enable attribute of an object
     * @param obj pointer to an object
     * @return true: the object is dragable
     */
    bool getDrag()
    {
        return lv_obj_get_drag(this);
    }

    /**
     * Get the directions an object can be dragged
     * @param obj pointer to an object
     * @return bitwise OR of allowed directions an object can be dragged in
     */
    DragDirection getDragDir()
    {
        return (DragDirection)lv_obj_get_drag_dir(this);
    }

    /**
     * Get the drag throw enable attribute of an object
     * @param obj pointer to an object
     * @return true: drag throw is enabled
     */
    bool getDragThrow()
    {
        return lv_obj_get_drag_throw(this);
    }

    /**
     * Get the drag parent attribute of an object
     * @param obj pointer to an object
     * @return true: drag parent is enabled
     */
    bool getDragParent()
    {
        return lv_obj_get_drag_parent(this);
    }

    /**
     * Get the drag parent attribute of an object
     * @param obj pointer to an object
     * @return true: drag parent is enabled
     */
    bool getParentEvent()
    {
        return lv_obj_get_parent_event(this);
    }

    /**
     * Get the opa scale enable parameter
     * @param obj pointer to an object
     * @return true: opa scaling is enabled for this object and all children; false: no opa scaling
     */
    bool getOpaScaleEnable()
    {
        return lv_obj_get_opa_scale_enable(this);
    }

    /**
     * Get the opa scale parameter of an object
     * @param obj pointer to an object
     * @return opa scale [0..255]
     */
    LVOpacity getOpaScale()
    {
        return lv_obj_get_opa_scale(this);
    }

    /**
     * Get the protect field of an object
     * @param obj pointer to an object
     * @return protect field ('OR'ed values of `lv_protect_t`)
     */
    uint8_t getProtect()
    {
        return lv_obj_get_protect(this);
    }

    /**
     * Check at least one bit of a given protect bitfield is set
     * @param obj pointer to an object
     * @param prot protect bits to test ('OR'ed values of `lv_protect_t`)
     * @return false: none of the given bits are set, true: at least one bit is set
     */
    bool isProtected(uint8_t prot)
    {
        return lv_obj_is_protected(this, prot);
    }

    /**
     * Get the signal function of an object
     * @param obj pointer to an object
     * @return the signal function
     */
    LVSignalCallBack getSignalCallBack()
    {
        return m_signalCallback;
    }

    /**
     * Get the design function of an object
     * @param obj pointer to an object
     * @return the design function
     */
    LVDesignCallBack getDesignCallBack()
    {
        return m_designCallback;
    }

    /**
     * Get the event function of an object
     * @param obj pointer to an object
     * @return the event function
     */
    LVEventCallBack getEventCallBack()
    {
        return m_eventCallback;
    }

    /*------------------
     * Other get
     *-----------------*/

    /**
     * Get the ext pointer
     * @param obj pointer to an object
     * @return the ext pointer but not the dynamic version
     *         Use it as ext->data1, and NOT da(ext)->data1
     */
    void * getExtAttr()
    {
        return lv_obj_get_ext_attr(this);
    }

    /**
     * Get object's and its ancestors type. Put their name in `type_buf` starting with the current type.
     * E.g. buf.type[0]="lv_btn", buf.type[1]="lv_cont", buf.type[2]="lv_obj"
     * @param obj pointer to an object which type should be get
     * @param buf pointer to an `lv_obj_type_t` buffer to store the types
     */
    void getType(LVObjectType * buf)
    {
        lv_obj_get_type(this, buf);
    }

    #if LV_USE_USER_DATA
    /**
     * Get the object's user data
     * @param obj pointer to an object
     * @return user data
     */
    lv_obj_user_data_t getUserData()
    {
        return lv_obj_get_user_data(this);
    }

    /**
     * Get a pointer to the object's user data
     * @param obj pointer to an object
     * @return pointer to the user data
     */
    lv_obj_user_data_t * getUserDataPtr()
    {
        return lv_obj_get_user_data_ptr(this);
    }

    /**
     * Set the object's user data. The data will be copied.
     * @param obj pointer to an object
     * @param data user data
     */
    void setUserData(lv_obj_user_data_t data)
    {
        lv_obj_set_user_data(this, data);
    }

    #endif

    #if LV_USE_GROUP
    /**
     * Get the group of the object
     * @param obj pointer to an object
     * @return the pointer to group of the object
     */
    void * getGroup()
    {
        return lv_obj_get_group(this);
    }

    /**
     * Tell whether the object is the focused object of a group or not.
     * @param obj pointer to an object
     * @return true: the object is focused, false: the object is not focused or not in a group
     */
    bool isFocused()
    {
        return lv_obj_is_focused(this);
    }

    #endif

#if LV_USE_POINTER

protected:
    friend class LVPointerBase;

    /**
     * @brief 添加指针对象
     * @param pointer
     */
    void addPointer(LVPointerBase * pointer);

    /**
     * @brief 移除指针对象
     * @param pointer
     * @return
     */
    bool removePointer(LVPointerBase * pointer);

    /**
     * @brief 清除指针对象,将所有指向这个对象的指针置空
     */
    void cleanPointers();

#endif

    /**
     * @brief 清除回调函数,找回占用的空间
     */
    void cleanCallBacks()
    {
        m_signalCallback = nullptr;
        m_designCallback = nullptr;
        m_eventCallback = nullptr;
        //恢复默认的回调函数
        resetAncestorCB();
    }
protected:
    /**
     * @brief 初始化回调函数
     */
    void callbackInit()
    {
        //记住类对象的先祖属性
        if(ancestorDesignCB() == nullptr) ancestorDesignCB() = lv_obj_get_design_cb(this);
        if(ancestorSignalCB() == nullptr) ancestorSignalCB() = lv_obj_get_signal_cb(this);
        if(ancestorEventCB() == nullptr) ancestorEventCB() = lv_obj_get_event_cb(this);

        //替换回调函数
        lv_obj_set_signal_cb(this,(lv_signal_cb_t)lvObjectSignalCallBackAgency);
    }

    void resetDesignCB()
    {
        lv_obj_set_design_cb(this,ancestorDesignCB());
    }
    void resetSignalCB()
    {
        lv_obj_set_signal_cb(this,ancestorSignalCB());
    }
    void resetEventCB()
    {
        lv_obj_set_event_cb(this,ancestorEventCB());
    }

    void resetAncestorCB()
    {
        resetDesignCB();
        resetSignalCB();
        resetEventCB() ;
    }


    //析构函数是否在运行过
    bool isDestructByDelete()
    {
        return m_destructByDelete == 1;
    }

    void setDestructByDelete(bool value = true)
    {
        m_destructByDelete = value?1:0;
    }

    void resetDestructByDelete()
    {
        setDestructByDelete(false);
    }

    virtual void onSignalCleanUp()
    {

    }


    static bool lvObjectDesignCallBackAgency(struct _lv_obj_t * obj, const lv_area_t * mask_p, lv_design_mode_t mode)
    {
        LVObject * lvObj = (LVObject*)obj;
        if(lvObj == nullptr)
        {
            lvError("lvObjectDesignCallBackAgency : LVObject is nullptr !");
            return false;
        }

        if(lvObj->m_designCallback)
        {
            return lvObj->m_designCallback(lvObj,(LVArea*)mask_p,DesignMode(mode));
        }
        else
        {
            lvError( "lvObjectDesignCallBackAgency : LVObject->m_designCallback is not set yet ! call default Design callback.");
            return (*lvObj->ancestorDesignCB())(obj,mask_p,mode);
        }
    }


    static lv_res_t lvObjectSignalCallBackAgency(struct _lv_obj_t * obj, SignalType sign, void * param)
    {
        LVObject * lvObj = (LVObject*)obj;
        if(lvObj == nullptr)
        {
            lvError("lvObjectSignalCallBackAgency : LVObject is nullptr !");
            return LV_RES_OK;
        }

        lv_res_t ret = LV_RES_OK;

        if(lvObj->m_signalCallback)
        {
            ret =  lvObj->m_signalCallback(lvObj,sign,param);
        }
        else
        {
            lvTrace("lvObjectSignalCallBackAgency : LVObject->m_SignalCallback is not set yet ! default signal callback.");
            ret = (*lvObj->ancestorSignalCB())(obj,sign,param);
        }

        if(sign == SIGNAL_CLEANUP)
        {
            //清理数据
            lvInfo("lvObjectSignalCallBackAgency : LV_SIGNAL_CLEANUP ");

            lvObj->onSignalCleanUp();
        #if LV_USE_POINTER
            //清理智能指针
            lvObj->cleanPointers();
        #endif

            //清理回调函数信息
            lvObj->cleanCallBacks();
            //释放LVObject实例对象的内存
            LVMemory::free(lvObj);

            LV_LOG_INFO("LVObject destroyed.");
        }

        return ret;
    }

    static void lvObjectEvenCallBackAgency(struct _lv_obj_t * obj, EventType event)
    {
        LVObject * lvObj = (LVObject*)obj;
        if(lvObj == nullptr)
        {
            lvError("lvObjectEvenCallBackAgency : LVObject is nullptr !");
        }

        if(lvObj->m_eventCallback)
        {
            lvObj->m_eventCallback(lvObj,event);
        }
        else
        {
            lvError("lvObjectEvenCallBackAgency : LVObject->m_eventCallback is not set yet ! call ancestor Event callback.");
            (lvObj->ancestorEventCB())(obj,event);
        }
    }

};

/**********************
 *      MACROS
 **********************/


#endif /*LVOBJECT_H*/
