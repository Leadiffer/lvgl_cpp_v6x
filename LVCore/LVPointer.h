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

    union
    {
        struct
        {
            uintptr_t m_obj :sizeof(uintptr_t)*8 - 1 ; //!< 对象指针
            uintptr_t m_scoped : 1; //!< 是否具有区域指针的特性,自动清理对象
        };
        uintptr_t m_data;
    };

    LVPointerBase(LVObject * obj = nullptr,bool scoped = false)
    {
        m_obj = 0;
        m_scoped = scoped;
        if(obj != nullptr)
            setObject(obj);
    }

public:

    ~LVPointerBase()
    {
        clean();
    }

    /**
     * @brief 获取指向的对象
     * @return
     */
    inline LVObject * object() const
    {
        return reinterpret_cast<LVObject *>(m_obj);
    }

    /**
     * @brief 智能指针是否是空指向
     * @return
     */
    bool isNull() const
    {
        return !m_obj;
    }

    /**
     * @brief 设置指针关联的对象
     * @param obj
     */
    void setObject(LVObject * obj)
    {
        auto old_obj = object();
        if(old_obj != obj)
        {
            clean();
            if(obj != nullptr)
                obj->addPointer(this);
            m_obj = reinterpret_cast<uintptr_t>(obj);
        }
    }

    bool scoped() const
    {
        return m_scoped;
    }

    void setScoped(bool value)
    {
        m_scoped = value;
    }

    /**
     * @brief 清除指针的对象关联
     */
    void clean()
    {
        //断开关联
        if(m_obj)
        {
            auto obj = object();
            obj->removePointer(this);
            m_obj = 0;

            //删除对象
            if(m_scoped)
                delete obj;
        }
    }

protected:

    /**
     * @brief 交换智能指针的对象
     * @param other
     */
    void swap(LVPointerBase & other)
    {
        if(m_data != other.m_data)
        {
            LVObject * thisObj = this->object();
            bool       thisScoped = this->m_scoped;
            LVObject * otherObj = other.object();
            bool       otherScoped = other.m_scoped;

            //先清除对象绑定(避免不必要的内存申请)
            if(thisObj != nullptr)
                this->setObject(nullptr);
            //再设置交换后的对象
            other.setObject(thisObj);
            other.setScoped(thisScoped);
            this->setObject(otherObj);
            this->setScoped(otherScoped);
        }
    }
};

template<class T>
class LVPointer : public LVPointerBase
{
    //NOTE:将该类加入到LV内存管理中,代价太大
    LV_MEMORY

public:
    explicit LVPointer(T * obj = nullptr,bool scoped = false)
        :LVPointerBase(obj,scoped)
    {
    }

    explicit LVPointer(bool scoped)
        :LVPointerBase(nullptr,scoped)
    {
    }

    //NOTE:禁止拷贝构造
    LVPointer(const LVPointer<T>& other)
        :LVPointerBase(other.object(),other.scoped())
    {
    }

//    //NOTE:禁止赋值操作
    LVPointer<T>& operator =(const LVPointer<T>& other) = delete;
//    {
//        if(m_obj != other.m_obj)
//            setObject(other.m_obj);
//        return *this;
//    }

    LVPointer<T>& operator =(T * obj) = delete;
//    {
//        if(m_obj != obj)
//            setObject(obj);
//        return *this;
//    }

    ~LVPointer()
    {
        clean();
    }

    bool operator ==(const LVPointer<T>& other) const
    {
        return this->m_obj == other.m_obj;
    }

    bool operator ==(const T * obj) const
    {
        return static_cast<T *>(object()) == obj;
    }

    bool operator !=(const LVPointer<T>& other) const
    {
        return this->m_obj != other.m_obj;
    }

    bool operator !=(const T * obj) const
    {
        return static_cast<T *>(object()) != obj;
    }

    operator T *() const
    {
        return static_cast<T*>(object());
    }

    T* get() const
    { return static_cast<T*>(object());}

    T & operator*() const
    {
        return *(static_cast<T*>(object()));
    }

    operator bool()
    {
        return !isNull();
    }

    T * operator->() const
    {
        return static_cast<T*>(object());
    }

    void reset(T* p = nullptr)
    {
        setObject(p);
    }

    void swap(LVPointer<T>& other)
    {
        LVPointerBase::swap(other);
    }
};

#endif

#endif // LVPOINTER_H
