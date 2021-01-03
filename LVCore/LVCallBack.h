#ifndef LVCALLBACK_H
#define LVCALLBACK_H

#include <functional>
#include <type_traits>
#include <lv_misc/lv_mem.h>

/**
 * @brief 可选函数指针或者可执行对象的回调函数
 * 由于使用std:functional耗内存,但是能够加快开发,
 * 为了同时兼容使用函数指针或者可执行对象来做回调函数,
 * 灵活控制内存占用,才写了这样一个中间类
 */
template<typename MethodSignature,typename ReturnType>
class LVCallBack
{
    //加入内存管理,代价昂贵
    static void* operator new(size_t sz)
    {
        return lv_mem_alloc(sz);
    }
    static void operator delete(void* p)
    {
        lv_mem_free(p);
    }
    static void *operator new[](size_t sz)
    {
        return lv_mem_alloc(sz);
    }
    static void operator delete[](void *p)
    {
        lv_mem_free(p);
    }
    //placement new
    static void * operator new(size_t /*size*/,void * addr)
    {
        return addr;
    }

public:
    /**
     * @brief 可选类型
     */
    enum Type : uint8_t
    {
        FUNC_PTR = 0, //!> 函数指针
        STD_FUNC = 1, //!> 可执行对象
    };

    /**
     *  为 std::function 取别名
     */
    using StdFunc = std::function<MethodSignature>;
    using FuncPtr = MethodSignature* ;

private:
    //使用位域减少内存使用,限制就是,仅支持31位地址寻址
    struct
    {
        uintptr_t m_pointer :sizeof(uintptr_t)*8-1 ; //!< 可执行对象 (StdFunc*) (MethodSignature*)
        uintptr_t m_type     :1  ; //!< 内部数据类型
    };

public:

    LVCallBack(MethodSignature * funcPtr = nullptr)
    {
        m_pointer = (uintptr_t)(funcPtr);
        m_type = FUNC_PTR;
    }

    //TODO:解决Lambda的初始化问题
    template<typename T>
    LVCallBack(const T & t)
        :LVCallBack(StdFunc(t))
    {}

    LVCallBack(const StdFunc & callable)
    {
        if(callable)
        {
            m_pointer = (uintptr_t)(new StdFunc(callable));
            m_type = STD_FUNC;
        }
        else
        {
            m_pointer = (uintptr_t)(nullptr);
            m_type = FUNC_PTR;
        }
    }

    LVCallBack(const LVCallBack<MethodSignature,ReturnType> & other)
    {
        if(!other.isNull())
        {
            m_type = other.m_type;
            //deep copy
            if(other.m_type == STD_FUNC)
                m_pointer = (uintptr_t)(new StdFunc(other.getStdFunc()));
            else
                m_pointer = other.m_pointer;
        }
        else
        {
            m_pointer = (uintptr_t)(nullptr);
            m_type = FUNC_PTR;
        }
    }

    LVCallBack(LVCallBack<MethodSignature,ReturnType> && other)
    {
        if(!other.isNull())
        {
            m_type = other.m_type;
            m_pointer = other.m_pointer;
            //take other`s data,then reset it
            other.m_type = FUNC_PTR;
            other.m_pointer = (uintptr_t)(nullptr);
        }
        else
        {
            m_pointer = (uintptr_t)(nullptr);
            m_type = FUNC_PTR;
        }
    }

    ~LVCallBack() {clear();}

    LVCallBack& operator =(StdFunc & callable)
    {
        clear();
        if(callable)
        {
            m_pointer = (uintptr_t)(new StdFunc(callable));
            m_type = STD_FUNC;
        }
        return *this;
    }

    LVCallBack& operator =(MethodSignature * funcPtr)
    {
        clear();
        m_pointer = (uintptr_t)(funcPtr);
        m_type = FUNC_PTR;
        return *this;
    }

    LVCallBack& operator =(const LVCallBack<MethodSignature,ReturnType> & other)
    {
        clear();

        if(!other.isNull())
        {
            m_type = other.m_type;
            //deep copy
            if(other.m_type == STD_FUNC)
                m_pointer = (uintptr_t)(new StdFunc(other.getStdFunc()));
            else
                m_pointer = other.m_pointer;
        }
        else
        {
            m_pointer = (uintptr_t)(nullptr);
            m_type = FUNC_PTR;
        }
        return *this;
    }

    LVCallBack& operator =(LVCallBack<MethodSignature,ReturnType> && other)
    {
        clear();
        if(!other.isNull())
        {
            m_type = other.m_type;
            m_pointer = other.m_pointer;
            //take other`s data,then reset it
            other.m_type = FUNC_PTR;
            other.m_pointer = 0;
        }
        else
        {
            m_pointer = 0;
            m_type = FUNC_PTR;
        }
        return *this;
    }

    LVCallBack& operator =(std::nullptr_t)
    {
        clear();
        return *this;
    }

    bool operator ==(std::nullptr_t)
    {
        return isNull();
    }

    bool operator !=(std::nullptr_t)
    {
        return !isNull();
    }

    /**
     * @brief 转 bool类型,同isNull()
     */
    operator bool() const
    {
        return !isNull();
    }

    /**
     * @brief 是否是可执行对象
     * @return
     */
    bool isStdFunc() const
    {
        return m_type == STD_FUNC;
    }

    /**
     * @brief 清空对象中的数据
     */
    void clear()
    {
        if (isStdFunc())
        {
            delete reinterpret_cast<StdFunc*>(m_pointer);
        }
        m_pointer = (uintptr_t)nullptr;
        m_type = FUNC_PTR;
    }

    /**
     * @brief 判断是否为空对象,表示无法执行
     * @return
     */
    bool isNull() const
    {
        if(m_pointer == (uintptr_t)nullptr)
        {
            return true;
        }
        else if (m_type==STD_FUNC)
        {
            return (*(reinterpret_cast<StdFunc*>(m_pointer)))?false:true;
        }
        else
        {
            return false;
        }
    }

    template<class... Args>
    ReturnType operator ()(Args&&... args)
    {
        if(isNull())
        {
        	//需要开启异常处理,不适合嵌入式
            //throw std::bad_function_call();
        	LV_LOG_ERROR("LVCallBack: bad_function_call");
        	assert(false);
        }
        switch (m_type)
        {
        case FUNC_PTR: return (*(reinterpret_cast<MethodSignature*>(m_pointer)))(std::forward<Args>(args)...); break;
        case STD_FUNC: return (*(reinterpret_cast<StdFunc*>(m_pointer)))(std::forward<Args>(args)...); break;
        }
    }

    MethodSignature* getFuncPtr() const
    {
        return m_type==FUNC_PTR?reinterpret_cast<MethodSignature*>(m_pointer):nullptr;
    }

    StdFunc getStdFunc() const
    {
        return m_type==STD_FUNC?(*(reinterpret_cast<StdFunc*>(m_pointer))):StdFunc(nullptr);
    }

    //TODO: 实现数据获取方法
} LV_ATTRIBUTE_MEM_ALIGN ;

#endif // LVCALLBACK_H
