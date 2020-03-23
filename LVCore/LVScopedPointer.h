#ifndef LVSCOPEDPOINTER_H
#define LVSCOPEDPOINTER_H

/**
 * @brief 当LVScopedPoniter对象销毁时，会自动释放所指堆空间对象。
 */
template<typename T>
class LVScopedPointer
{
private:
    T* m_pointer;

    //类不可拷贝复制赋值
    LVScopedPointer(const LVScopedPointer<T>&);
    LVScopedPointer<T>& operator = (const LVScopedPointer<T>&);

    void operator==( LVScopedPointer const& ) const;
    void operator!=( LVScopedPointer const& ) const;

public:
    LVScopedPointer(T* p = nullptr)
        : m_pointer (p)
    {}

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
        if(m_pointer != nullptr)
            delete m_pointer;
        m_pointer = p;
    }

    void swap(LVScopedPointer & b)
    {
        T * tmp = b.m_pointer;
        b.m_pointer = this->m_pointer;
        this->m_pointer = tmp;
    }

    ~LVScopedPointer()
    {
        delete m_pointer;
    }

};

#endif // LVSCOPEDPOINTER_H
