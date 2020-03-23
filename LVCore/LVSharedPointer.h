#ifndef LVSHAREDPOINTER_H
#define LVSHAREDPOINTER_H

#include "../LVMisc/LVLog.h"

 template<typename T>
/**
 * @brief 当LVSharedPointer对象销毁时，会自动将引用计数减1，只有当引用计数为0时才会释放堆空间对象。
 */
class SharedPointer
{
protected:
    T* m_pointer;
    int* m_ref;
public:
    SharedPointer(T* p = nullptr)
        :m_pointer(nullptr)
        ,m_ref(nullptr)
    {
       assign(p);
    }

    SharedPointer(const SharedPointer<T>& obj)
        :m_pointer(nullptr)
    {
        assign(obj);
    }

    SharedPointer<T>& operator = (const SharedPointer<T>& obj)
    {
        if(&obj != this)
        {
            clear();
            assign(obj);
        }
        return *this;
    }

    T* operator ->()
    { return  m_pointer; }

    T& operator * ()
    { return *m_pointer;}

    operator bool()
    {
        return m_pointer != nullptr;
    }

    operator const T*()
    {
        return m_pointer;
    }

    bool isNull()
    { return (m_pointer == nullptr); }

    T* get() const
    { return m_pointer;}

    void reset(T* p = nullptr)
    {
        clear();
        assign(p);
    }

    ~SharedPointer()
    {
        clear();
    }

    int useCount() const
    {
        return (m_ref == nullptr) ? 0 : *m_ref;
    }

    bool unique() const
    {
        return useCount() == 1;
    }

private:
    void assign(const SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)
        {
            (*this->m_ref)++;
        }
    }

    void assign(T* p)
    {
        if(p)
        {
            this->m_ref = static_cast<int*>(new int(0));
            if(this->m_ref)
            {
                this->m_pointer = p;
                *(this->m_ref) = 1;
            }
            else
            {
                lvError("no memory to reate LVSharedPointer object ..");
            }
        }
    }

    void clear()
    {
        T* toDel =this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = nullptr;
        this->m_ref = nullptr;

        if(ref)
        {
            (*ref)--;
            if(*ref == 0)
            {
                delete ref;
                delete toDel;
            }
        }
    }
};

template <typename T>
bool operator ==(const SharedPointer<T>& l,const SharedPointer<T>& r)
{
    return (l.get() == r.get());
}

template <typename T>
bool operator !=(const SharedPointer<T>& l,const SharedPointer<T>& r)
{
    return !(l == r);
}

#endif // LVSHAREDPOINTER_H
