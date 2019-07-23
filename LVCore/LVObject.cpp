#include "LVObject.h"
#include "LVPointer.h"

#if LV_USE_POINTER

void LVObject::addPointer(LVPointerBase *pointer)
{
    //初始化智能指针列表
    if(m_pointers == nullptr)
    {
        //默认开辟
        m_pointers = (LVPointerBase **)LVMemory::allocate(sizeof(LVPointerBase*));
        m_pointers[0] = nullptr;
    }
    //寻找可用的空间
    uint8_t size = LVMemory::getMemoryEntry(m_pointers)->getSize();
    for (uint8_t i = 0, n = size/sizeof(LVPointerBase*) ; i < n; ++i)
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
    m_pointers[size/sizeof(LVPointerBase*)] = pointer;
}

bool LVObject::removePointer(LVPointerBase *pointer)
{
    if(m_pointers == nullptr)
        return false; //NOTE:一种错误的情况,不该发生
    uint8_t size = LVMemory::getMemoryEntry(m_pointers)->getSize();
    for (uint8_t i = 0, n = size/sizeof(LVPointerBase*) ; i < n; ++i)
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
    if(m_pointers == nullptr) return;
    uint8_t size = LVMemory::getMemoryEntry(m_pointers)->getSize();
    for (uint8_t i = 0, n = size/sizeof(LVPointerBase*) ; i < n; ++i)
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

#endif
