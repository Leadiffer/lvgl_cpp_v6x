#include "LVObject.h"
#include "LVPointer.h"
#include "LVDispaly.h"

extern "C"
{

lv_obj_t * lv_obj_create_custom(void*(*func)(lv_ll_t *), lv_ll_t * ll_p);
void lv_obj_del_custom(lv_obj_t * obj);
void * lv_obj_allocate_ext_attr_custom(lv_obj_t * obj,void * (*func)(void *, size_t), void *data_p, size_t new_size);

extern lv_obj_t *& new_obj_addr();
extern void *& new_obj_attr_addr();
extern void *& new_obj_attr_obj_addr();

}

/**
 * @brief 自定义对象创建函数
 */
lv_obj_t * lv_obj_create_custom(void*(*func)(lv_ll_t *), lv_ll_t * ll_p)
{
    void * new_obj = nullptr;
    //判断是否有新的对象类建立,并拦截
    if(new_obj_addr())
    {
        new_obj = lv_ll_ins_head_with(ll_p,new_obj_addr());
        new_obj_addr() = nullptr; //使用一次后就重置地址
    }
    else
    {
        //默认的实现
        new_obj = func(ll_p);
    }
    return static_cast<lv_obj_t*>(new_obj);
}

/**
 * @brief 自定义对象删除函数
 */
void lv_obj_del_custom(lv_obj_t * obj)
{
    if(LVObject::isVaild(obj)) //LVOnjecct类实例
    {
        if(!obj->class_ptr.deleted)
        {
            obj->class_ptr.deleted = true;
            //删除对象
            LVObject * lvObj = static_cast<LVObject*>(obj);
            delete lvObj;
        }
    }
    else //原始的lv_obj_t 数据
    {
        /*Delete the base objects*/
        if(obj->ext_attr != NULL) lv_mem_free(obj->ext_attr);
        lv_mem_free(obj); /*Free the object itself*/
    }
}

/**
 * @brief 自定义对象属性创建函数
 */
void *lv_obj_allocate_ext_attr_custom(lv_obj_t * obj,void * (*func)(void *, size_t),void * data_p, size_t new_size)
{
    if(new_obj_attr_obj_addr() == obj)
    {
        return new_obj_attr_addr();
    }
    else
    {
        return func(data_p,new_size);
    }
}


bool LVObject::isVaild()
{
    //回环检查是否是一个有效的类对象
    return class_ptr.pointer && this == reinterpret_cast<LVObject*>(class_ptr.pointer);
}

bool LVObject::isVaild(lv_obj_t *obj)
{
    //回环检查obj是否是一个有效的类对象
    return obj && reinterpret_cast<LVObject*>(obj->class_ptr.pointer) == static_cast<LVObject*>(obj);
}

void LVObject::loadScreen()
{
    lv_disp_load_scr(this);
}

#if LV_USE_POINTER

void LVObject::addPointer(LVPointerBase *pointer)
{
    //初始化智能指针列表
    if(m_pointers == nullptr)
    {
        //默认开辟
        //BUG:实际分配的内存块可能大于指定数
        m_pointers = (LVPointerBase **)LVMemory::allocate(sizeof(LVPointerBase*));
        memset(m_pointers,0,LVMemory::getMemoryEntry(m_pointers)->getSize());
    }
    //寻找可用的空间
    uint32_t size = LVMemory::getMemoryEntry(m_pointers)->getSize();
    uint32_t ptrSize = size/sizeof(LVPointerBase*);
    //lvInfo("objrct(0x%p) add Pointer(0x%p) size:%d",this,m_pointers,size);
    for (uint32_t i = 0; i < ptrSize; ++i)
    {
        if(m_pointers[i] == pointer)
        {
            //NOTE:禁止重复关联
            return;
        }
        else if(m_pointers[i] == nullptr)
        {
            m_pointers[i] = pointer;
            return;
        }
    }
    //开辟新空间
    m_pointers = (LVPointerBase **)LVMemory::reallocate(m_pointers,size+sizeof(LVPointerBase*));
    //BUG:实际分配的内存块可能大于指定数
    memset(m_pointers+(ptrSize),0,LVMemory::getMemoryEntry(m_pointers)->getSize()-size);
    m_pointers[ptrSize] = pointer;
}

bool LVObject::removePointer(LVPointerBase *pointer)
{
    if(m_pointers == nullptr)
        return false; //NOTE:一种错误的情况,不该发生
    uint32_t size = LVMemory::getMemoryEntry(m_pointers)->getSize();
    //lvInfo("objrct(0x%p) remove Pointer(0x%p) size:%d",this,m_pointers,size);
    for (uint32_t i = 0, n = size/sizeof(LVPointerBase*) ; i < n; ++i)
    {
        if(m_pointers[i] == pointer)
        {
            //抹除智能指针关联
            pointer->m_obj = nullptr;
            m_pointers[i] = nullptr;
            return true;
        }
    }
    return false;
}

void LVObject::cleanPointers()
{
    if(m_pointers == nullptr)
        return;
    uint32_t size = LVMemory::getMemoryEntry(m_pointers)->getSize();
    //lvInfo("objrct(0x%p) clean Pointer(0x%p) size:%d",this,m_pointers,size);
    for (uint32_t i = 0, n = size/sizeof(LVPointerBase*) ; i < n; ++i)
    {
        if(m_pointers[i] != nullptr)
        {
            m_pointers[i]->m_obj = nullptr;
            m_pointers[i] = nullptr;
        }
    }
    //清理指针列表
    LVMemory::free(m_pointers);
    m_pointers = nullptr;
}

void LVObject::initAncestorCB()
{
    //记住类对象的先祖属性
    if(ancestorDesignCB() == nullptr) ancestorDesignCB() = lv_obj_get_design_cb(this);
    if(ancestorSignalCB() == nullptr) ancestorSignalCB() = lv_obj_get_signal_cb(this);
    if(ancestorEventCB() == nullptr) ancestorEventCB() = lv_obj_get_event_cb(this);

    //替换信号回调函数
    //lv_obj_set_signal_cb(this,(lv_signal_cb_t)signalCallBackAgency);
}

void LVObject::resetDesignCB()
{
    lv_obj_set_design_cb(this,ancestorDesignCB());
}

void LVObject::resetSignalCB()
{
    lv_obj_set_signal_cb(this,ancestorSignalCB());
}

void LVObject::resetEventCB()
{
    lv_obj_set_event_cb(this,ancestorEventCB());
}

void LVObject::resetAncestorCB()
{
    resetDesignCB();
    resetSignalCB();
    resetEventCB() ;
}

bool LVObject::designCallBackAgency(_lv_obj_t *obj, const lv_area_t *mask_p, lv_design_mode_t mode)
{
    LVObject * lvObj = lvobject_cast<LVObject*>(obj);
    if(lvObj == nullptr)
    {
        lvError("designCallBackAgency : LVObject is nullptr !");
        return false;
    }

    if(lvObj->m_designCallback)
    {
        return lvObj->m_designCallback(lvObj,(LVArea*)mask_p,DesignMode(mode));
    }
    else
    {
        lvWarn( "designCallBackAgency : LVObject->m_designCallback is not set yet ! call default Design callback.");
        lvObj->resetDesignCB();
        return (*lvObj->ancestorDesignCB())(obj,mask_p,mode);
    }
}

lv_res_t LVObject::signalCallBackAgency(_lv_obj_t *obj, lv_signal_t sign, void *param)
{
    LVObject * lvObj = lvobject_cast<LVObject*>(obj);
    if(lvObj == nullptr)
    {
        lvError("signalCallBackAgency : LVObject is nullptr !");
        return LV_RES_INV;
    }

    lv_res_t ret = LV_RES_OK;

    if(lvObj->m_signalCallback)
    {
        ret =  lvObj->m_signalCallback(lvObj,SignalType(sign),param);
    }
    else
    {
        lvWarn("signalCallBackAgency : LVObject->m_SignalCallback is not set yet ! default signal callback.");
        lvObj->resetSignalCB();
        ret = (*lvObj->ancestorSignalCB())(obj,sign,param);
    }
    return ret;
}

#endif

void LVObject::evenCallBackAgency(_lv_obj_t *obj, lv_event_t event)
{
    LVObject * lvObj = lvobject_cast<LVObject*>(obj);
    if(lvObj == nullptr)
    {
        lvError("evenCallBackAgency : LVObject is nullptr !");
    }

    if(lvObj->m_eventCallback)
    {
        lvObj->m_eventCallback(lvObj,EventType(event));
    }
    else
    {
        lvError("evenCallBackAgency : LVObject->m_eventCallback is not set yet ! call ancestor Event callback.");
        lvObj->resetEventCB();
        (lvObj->ancestorEventCB())(obj,event);
    }
}

