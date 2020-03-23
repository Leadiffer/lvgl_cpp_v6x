#ifndef LVPOINTERARRAY_H
#define LVPOINTERARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LVMisc/LVLog.h"
#include "LVMisc/LVMemory.h"

/**
 * @brief 指针数组基类
 */
class LVPointerArrayBase
{
protected:
    size_t size_ = 0;
    void* * buffer_ = nullptr;

    void abort(const char * mesg = "")
    {
        lvError("LVPointerArray(%p) - %s",this,mesg);
        while (1) {}
    }
public:
    LVPointerArrayBase(){}

    /**
     * @brief 能够存储指针的能力大小
     * @return
     */
    inline uint32_t capacity() const { bufferSize()/sizeof(void*);}

    /**
     * @brief 已经存储的指针个数
     * @return
     */
    inline uint32_t size(){ return size_;}

    /**
     * @brief 重置指针容量大小
     * @param size
     */
    void resize(uint32_t size)
    {
        if(size > capacity())
        {
            buffer_ = lv_mem_realloc(buffer_,size*sizeof(void*));
            memset(buffer_+size_,0,bufferSize()-size_*sizeof(void*));
        }
        else
        {
            memset(buffer_+size,0,bufferSize()-size*sizeof(void*));
        }
        size_ = size;
    }
protected:

    /**
     * @brief 缓冲的字节数大小
     * @return
     */
    inline uint32_t bufferSize() { lv_mem_get_size(buffer_); }

    /**
     * @brief 扩大指针数组容量大小
     * @param size 扩大指针容量个数
     */
    void expand(uint32_t size)
    {
        uint32_t new_size = (size_+size)*sizeof(void*); //容器需要的字节数
        if(bufferSize() < new_size)
        {
            buffer_ = lv_mem_realloc(buffer_,new_size);
            memset(buffer_+size_,0,bufferSize()-size_*sizeof(void*));
        }
    }

    /**
     * @brief 缩小指针数组容量大小
     * @param size 减少指针容量个数
     */
    void shrink(uint32_t size)
    {
        uint32_t new_size = (size_-size)*sizeof(void*); //容器需要的字节数
        if(bufferSize() > new_size)
        {
            buffer_ = lv_mem_realloc(buffer_,new_size);
            memset(buffer_+(size_-size),0,bufferSize()-new_size);
        }

        if(size<size_)
            size_ = size;
    }
};

/**
 * @brief 指针数组
 */
template<class T>
class LVPointerArray : public LVPointerArrayBase
{
    LV_MEMORY

public:
    typedef T* ptr_type;

private:


public:

    LVPointerArray()
    {}
    LVPointerArray(size_t size)
    {
        expand(size);
    }
    LVPointerArray(const LVPointerArray & other)
    {
        expand(other.size_ - size_);
        memcpy(buffer_,other.buffer_,other.size_*sizeof(ptr_type));
        size_ = other.size_;
    }
    LVPointerArray(LVPointerArray && other)
    {
        buffer_ = other.buffer_;
        size_ = other.size_;
        other.buffer_ = nullptr;
        other.size_ = 0;
    }
    ~LVPointerArray()
    {
        lv_mem_free(buffer_);
        size_ = 0;
    }

    void append(T * ptr)
    {
        expand(1);
        buffer_[size_] = ptr;
        size_ += 1;
    }

    void prepend(T * ptr)
    {
        expand(1);
        //向后挪动数据
        for (int i = size_; i > 0; --i) {
            buffer_[i] = buffer_[i-1];
        }
        buffer_[0] = ptr;
        size_ += 1;
    }

    void insert(T * ptr,int pos)
    {
        if(pos == 0)
            prepend(ptr);
        else if(pos == size_)
            append(ptr);
        else if(pos>0 && pos<size_)
        {
            //TODO:插入数据
        }
    }

private:


};

#endif // LVPOINTERARRAY_H
