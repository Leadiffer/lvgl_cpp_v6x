#ifndef LVPOINTER_H
#define LVPOINTER_H

#include "LVObject.h"

#if LV_USE_POINTER

class LVObject;


/**
 * @brief LVObject对象的智能指针,
 * 可以用来感知对象是否存在,避免野指针调用
 * 例子:
 * LVPointer<LVLed> led = new LVLed(xx,xx);
 * ...
 * 在其他使用的地方:
 * if(led)
 * {
 *      led->setStyle(xxxxx);
 *      ...
 * }
 */

class LVPointerBase
{
    friend class LVObject;
protected:
    LVPointerBase(LVObject * obj = nullptr):m_obj(obj){}
public:
    LVObject * m_obj = nullptr;

    /**
     * @brief 智能指针是否是空指向
     * @return
     */
    bool isNull() const
    {
        return m_obj == nullptr;
    }

    /**
     * @brief 设置指针关联的对象
     * @param obj
     */
    void setObject(LVObject * obj)
    {
        if(m_obj != obj)
        {
            if(m_obj != nullptr)
            {
                m_obj->removePointer(this);
                m_obj = nullptr;
            }

            if(obj != nullptr) obj->addPointer(this);
            m_obj = obj;
        }
    }

    /**
     * @brief 清除指针的对象关联
     */
    void clear()
    {
        setObject(nullptr);
    }

    /**
     * @brief 交换智能指针的对象
     * @param other
     */
    void swap(LVPointerBase & other)
    {
        if(m_obj != other.m_obj)
        {
            LVObject * thisObj = m_obj;
            LVObject * otherObj = other.m_obj;

            //先清除对象绑定(避免不必要的内存申请)
            if(thisObj != nullptr)
                this->setObject(nullptr);
            //再设置交换后的对象
            other.setObject(thisObj);
            this->setObject(otherObj);
        }
    }
};

template<class T>
class LVPointer : public LVPointerBase
{
    //NOTE:将该类加入到LV内存管理中,代价太大
    LV_MEMORY

public:
    LVPointer(T * obj = nullptr)
        :LVPointerBase()
    {
        setObject(obj);
    }

    LVPointer(const LVPointer<T>& other)
        :LVPointerBase()
    {
        setObject(other.m_obj);
    }

    ~LVPointer()
    {
        clear();
    }

    bool operator ==(const LVPointer<T>& other) const
    {
        return m_obj == other.m_obj;
    }

    bool operator ==(const T * obj) const
    {
        return m_obj == obj;
    }

    bool operator !=(const LVPointer<T>& other) const
    {
        return m_obj != other.m_obj;
    }

    bool operator !=(const T * obj) const
    {
        return m_obj != obj;
    }

    LVPointer<T>& operator =(const LVPointer<T>& other)
    {
        if(m_obj != other.m_obj)
            setObject(other.m_obj);
        return *this;
    }

    LVPointer<T>& operator =(T * obj)
    {
        if(m_obj != obj)
            setObject(obj);
        return *this;
    }

    operator T *() const
    {
        return static_cast<T*>(m_obj);
    }

    T* get() const
    { return static_cast<T*>(m_obj);}

    T & operator*() const
    {
        return *(static_cast<T*>(m_obj));
    }

    operator bool()
    {
        return m_obj != nullptr;
    }

    T * operator->() const
    {
        return static_cast<T*>(m_obj);
    }

    void reset(T* p = nullptr)
    {
        if(m_obj != p)
            setObject(p);
    }
};

#endif

#endif // LVPOINTER_H
