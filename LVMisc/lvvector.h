#ifndef LVVECTOR_H
#define LVVECTOR_H

#include <stdlib.h>
#include "LVMemory.h"
#include "LVMisc/LVLog.h"

//TODO:实现向量表的功能
//erase()
//emplace
//emplace_back
//swap
//emplace_back

template<class T>
class LVVector {
    LV_MEMORY

    void abort(const char * mesg = "");

public:
    typedef size_t size_type;
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;

private:
    size_type size_ = 0;
    size_type capacity_ = 0; // 2^n
    value_type* buffer_ = nullptr;

public:
    LVVector();
    LVVector(size_type n, const value_type& val = value_type());
    LVVector(const LVVector& x);
    ~LVVector();

    void reserve(size_type n);
    size_type capacity() const;
    size_type size() const;
    bool empty() const;

    value_type* data();
    const value_type* data() const;

    value_type& at(size_type n);
    const value_type& at(size_type n) const;
    value_type& operator [] (size_type n);
    const value_type& operator [] (size_type n) const;
    LVVector& operator = (const LVVector& x);

    void clear();
    value_type& back();
    const value_type& back() const;
    value_type& front();
    const value_type& front() const;

    void push_back(const value_type& val);
    void pop_back();

    void resize(size_type n, value_type val = value_type());

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

}; // class vector


template<class T>
void LVVector<T>::abort(const char * mesg)
{
    lvError("LVVector(%p) - %s",this,mesg);
    while (1) {}
}

template<class T> inline
LVVector<T>::LVVector() : size_(0), capacity_(0), buffer_(nullptr)
{
}

template<class T> inline
LVVector<T>::LVVector(size_type n, const value_type& val)
{
    reserve(n);

    size_ = n;
    for (size_t i = 0; i < n; ++i)
        buffer_[i] = val;
}

template<class T> inline
LVVector<T>::LVVector(const LVVector& x)
{
    reserve(x.size_);

    size_ = x.size_;
    for (size_t i = 0; i < x.size_; ++i)
        buffer_[i] = x.buffer_[i];
}

template<class T> inline
LVVector<T>::~LVVector()
{
    if (buffer_)
        delete [] buffer_;
}

template<class T> inline
void LVVector<T>::reserve(size_type n)
{
    if (capacity_ < n) {
        delete [] buffer_;

        capacity_ = 1;
        if (capacity_ < n) {
            capacity_ = 2;
            while (capacity_ < n) {
                capacity_ *= 2;
            }
        }
        buffer_ = new value_type[capacity_];
    }
}

template<class T> inline
size_t LVVector<T>::capacity() const
{
    return capacity_;
}

template<class T> inline
size_t LVVector<T>::size() const
{
    return size_;
}

template<class T> inline
bool LVVector<T>::empty() const
{
    return size_ == 0 ? true : false;
}

template<class T> inline
T* LVVector<T>::data()
{
    return buffer_;
}

template<class T> inline
const T* LVVector<T>::data() const
{
    return buffer_;
}

template<class T> inline
T& LVVector<T>::at(size_type n)
{
    if (size_ <= n)
        abort("LVVector<T>::at index out-of-bounds");
    return buffer_[n];
}

template<class T> inline
const T& LVVector<T>::at(size_type n) const
{
    if (size_ <= n)
        abort("LVVector<T>::at index out-of-bounds");
    return buffer_[n];
}

template<class T> inline
T& LVVector<T>::operator [] (size_type n)
{
    if (size_ <= n)
        abort("LVVector<T>::operator [] index out-of-bounds");
    return buffer_[n];
}

template<class T> inline
const T& LVVector<T>::operator [] (size_type n) const
{
    if (size_ <= n) abort();
    return buffer_[n];
}

template<class T> inline
LVVector<T>& LVVector<T>::operator = (const LVVector& x)
{
    reserve(x.size_);

    size_ = x.size_;
    for (size_t i = 0; i < size_; ++i)
        buffer_[i] = x.buffer_[i];

    return *this;
}

template<class T> inline
void LVVector<T>::clear()
{
    size_ = 0;
}

template<class T> inline
T& LVVector<T>::back()
{
    if (size_ == 0)
        abort("LVVector<T>::back() empty vector");
    return buffer_[size_-1];
}

template<class T> inline
const T& LVVector<T>::back() const
{
    if (size_ == 0)
        abort("LVVector<T>::back() empty vector");
    return buffer_[size_-1];
}

template<class T> inline
T& LVVector<T>::front()
{
    if (size_ == 0)
        abort("LVVector<T>::front() empty vector");
    return buffer_[0];
}

template<class T> inline
const T& LVVector<T>::front() const
{
    if (size_ == 0)
        abort("T& LVVector<T>::front() empty vector");
    return buffer_[0];
}

template<class T> inline
void LVVector<T>::push_back(const value_type& val)
{
    if (size_ >= capacity_) {
        T* tmp = new T[size_];
        for (size_t i = 0; i < size_; ++i)
            tmp[i] = buffer_[i];

        reserve(size_+1);

        for (size_t i = 0; i < size_; ++i)
            buffer_[i] = tmp[i];

        delete [] tmp;
    }

    buffer_[size_] = val;
    size_ += 1;
}

template<class T> inline
void LVVector<T>::pop_back()
{
    if (size_ == 0)
        abort("LVVector<T>::pop_back() empty vector");
    --size_;
}

template<class T> inline
void LVVector<T>::resize(size_type n, value_type val)
{
    if (size_ < n) {
        if (n > capacity_) {
            T* tmp = new T[size_];
            for (size_t i = 0; i < size_; ++i)
                tmp[i] = buffer_[i];

            reserve(n);

            for (size_t i = 0; i < size_; ++i)
                buffer_[i] = tmp[i];

            delete [] tmp;
        }

        for (size_t i = size_; i < n; ++i)
            buffer_[i] = val;
    }

    size_ = n;
}

template<class T> inline
T* LVVector<T>::begin()
{
    return buffer_;
}

template<class T> inline
const T* LVVector<T>::begin() const
{
    return buffer_;
}

template<class T> inline
T* LVVector<T>::end()
{
    return buffer_ + size_;
}

template<class T> inline
const T* LVVector<T>::end() const
{
    return buffer_ + size_;
}

template<class T> static inline
bool operator == (const LVVector<T>& lhs, const LVVector<T>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    for (size_t i = 0; i < lhs.size(); ++i)	{
        if (lhs[i] != rhs[i])
            return false;
    }

    return true;
}

template<class T> static inline
bool operator != (const LVVector<T>& lhs, const LVVector<T>& rhs)
{
    return !(lhs == rhs);
}

template<class T> static inline
bool operator < (const LVVector<T>& lhs, const LVVector<T>& rhs)
{
    bool flag = true;
    if (lhs.size() == rhs.size()) {
        if (lhs == rhs) {
            flag = false;
        } else {
            for (size_t i = 0; i < lhs.size(); ++i) {
                if (lhs[i] > rhs[i]) {
                    flag = false;
                    break;
                }
            }
        }
    } else if (lhs.size() < rhs.size()) {
        LVVector<T> vec(lhs.size());
        for (size_t i = 0; i < lhs.size(); ++i)
            vec[i] = rhs[i];
        if (lhs == vec) {
            flag = true;
        } else {
            for (size_t i = 0; i < lhs.size(); ++i) {
                if (lhs[i] > rhs[i]) {
                    flag = false;
                    break;
                }
            }
        }
    } else {
        LVVector<T> vec(rhs.size());
        for (size_t i = 0; i < rhs.size(); ++i)
            vec[i] = lhs[i];
        if (vec == rhs) {
            flag = false;
        } else {
            for (size_t i = 0; i < rhs.size(); ++i) {
                if (lhs[i] > rhs[i]) {
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}
template<class T> static inline
bool operator <= (const LVVector<T>& lhs, const LVVector<T>& rhs)
{
    return !(rhs < lhs);
}
template<class T> static inline
bool operator > (const LVVector<T>& lhs, const LVVector<T>& rhs)
{
    return (rhs < lhs);
}
template<class T> static inline
bool operator >= (const LVVector<T>& lhs, const LVVector<T>& rhs)
{
    return !(lhs < rhs);
}

#endif // LVVECTOR_H
