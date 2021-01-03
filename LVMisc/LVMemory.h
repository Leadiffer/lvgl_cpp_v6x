/**
 * @file lv_mem.h
 *
 */

#ifndef LVMEMORY_H_
#define LVMEMORY_H_

/*********************
 *      INCLUDES
 *********************/

#include <stdlib.h>
#include <new>
#include <lv_misc/lv_mem.h>
#include "../LVMisc/LVLog.h"

/*********************
 *      DEFINES
 *********************/

//BUG:造成内存管理混乱破裂

//class LVMemoryHeader //: public lv_mem_header_t
//{
//public:

//    /*The size of this class must be 4 bytes (uint32_t)*/
//    union
//    {
//        struct
//        {
//            uintptr_t used : 1;    // 1: if the entry is used
//            uintptr_t d_size : 31; // Size off the data (1 means 1 bytes)
//        } s;
//        uintptr_t header; // The header (used + d_size)
//    };

//    LVMemoryHeader(uint32_t size = 0,bool use = true)
//    {
//        s.d_size = size;
//        s.used = use;
//    }

//    static void setMemHeader(void *data_p, uint32_t size = 0,bool use = true)
//    {
//        LVMemoryHeader * memHeader = (LVMemoryHeader*)((uint8_t*)data_p)-sizeof(LVMemoryHeader);
//        memHeader->s.d_size = size;
//        memHeader->s.used = use;
//    }

//    uint32_t getSize(){ return s.d_size; }
//    bool isUsed(){ return s.used == 1; }
////protected:
//    void setSize(uint32_t size){ s.d_size = size; }
//    void setUsed(bool use){ s.used = use; }
//};

//template<typename T = uint32_t>
//class LVFakeMemHeader
//{
//public:
//    LVMemoryHeader m_header;
//    LVFakeMemHeader(bool use = true)
//        :m_header(sizeof(T),use)
//    {}
//    LVFakeMemHeader(uint32_t size ,bool use = true)
//        :m_header(size,use)
//    {}

//    bool isUsed(){ return m_header.s.used == 1; }
//};


//class LVMemoryEntry : public LVMemoryHeader //: public lv_mem_ent_t
//{
//public:
//    //LVMemoryHeader header;
//    uint8_t first_data; /*First data byte in the allocated data (Just for easily create a pointer)*/
//};


//实现LVGL对内存的管理
//自定义类的new和delete函数
//类中第一行使用下面的宏即可

#define LV_MEMORY_NEW \
static void* operator new(size_t sz) \
{ \
    return lv_mem_alloc(sz); \
}

#define LV_MEMORY_DELETE \
static void operator delete(void* p) \
{ \
    lv_mem_free(p); \
}

#define LV_MEMORY_NEW_ARRAY \
static void *operator new[](size_t sz) \
{ \
    return lv_mem_alloc(sz); \
}

#define LV_MEMORY_DELETE_ARRAY \
static void operator delete[](void *p) \
{ \
    lv_mem_free(p); \
}

//placement new
#define LV_MEMORY_PLACE \
static void * operator new(size_t /*size*/,void * addr) \
{ \
    return addr; \
}

/**
 * @brief 将自定义类的内存分配交由LVGL管理
 */
#define LV_MEMORY \
    public: \
    LV_MEMORY_NEW \
    LV_MEMORY_DELETE \
    LV_MEMORY_NEW_ARRAY \
    LV_MEMORY_DELETE_ARRAY \
    LV_MEMORY_PLACE \
    private:

/**********************
 *      TYPEDEFS
 **********************/

class LVMemory;

class LVMemoryMonitor : public lv_mem_monitor_t
{
    LV_MEMORY
public:
    LVMemoryMonitor()
    {
        updateMonitor();
    }

    /**
     * @brief update memory monitor information
     */
    void updateMonitor();

    uint32_t totalSize(){ return total_size; }
    uint32_t freeCount(){ return free_cnt; }
    uint32_t freeSize(){ return free_size; }
    uint32_t freeBiggestSize(){ return free_biggest_size; }
    uint32_t usedCount(){ return free_cnt; }
    uint8_t usedPercent(){ return used_cnt; }
    uint8_t fragmentPercent(){ return frag_pct; }
};

class LVMemory
{
    LVMemory() = delete;
    ~LVMemory() = delete;
public:
    /**********************
     * PROTOTYPES
     **********************/

    /**
     * Initiaize the dyn_mem module (work memory and other variables)
     */
    static void init(void)
    {
        lv_mem_init();
    }

    /**
     * Allocate a memory dynamically
     * @param size size of the memory to allocate in bytes
     * @return pointer to the allocated memory
     */
    static void * allocate(uint32_t size)
    {
        return lv_mem_alloc(size);
    }

    /**
     * Free an allocated data
     * @param data pointer to an allocated memory
     */
    static void free(const void * data)
    {
        lv_mem_free(data);
    }

    /**
     * Reallocate a memory with a new size. The old content will be kept.
     * @param data pointer to an allocated memory.
     * Its content will be copied to the new memory block and freed
     * @param new_size the desired new size in byte
     * @return pointer to the new memory
     */
    static void * reallocate(void * data_p, uint32_t new_size)
    {
        return lv_mem_realloc(data_p, new_size);
    }

    /**
     * Join the adjacent free memory blocks
     */
    static void defrag(void)
    {
        lv_mem_defrag();
    }

    /**
     * Give information about the work memory of dynamic allocation
     * @param mon_p pointer to a dm_mon_p variable,
     *              the result of the analysis will be stored here
     */
    static void monitor(lv_mem_monitor_t * mon_p)
    {
        lv_mem_monitor(mon_p);
    }

    /**
     * Give the size of an allocated memory
     * @param data pointer to an allocated memory
     * @return the size of data memory in bytes
     */
    static uint32_t getSize(const void * data)
    {
        return lv_mem_get_size(data);
    }

    /*******************
     *     ENHANCE
     *******************/

//    static LVMemoryEntry * getMemoryEntry(void * data_p)
//    {
//        return (LVMemoryEntry *)((uint8_t *)data_p - sizeof(LVMemoryHeader));
//    }



//    static void setMemHeader(void *data_p, uint32_t size = 0,bool use = true)
//    {
//        LVMemoryHeader::setMemHeader(data_p,size,use);
//    }

    /**
     * @brief 得到由lvgl开辟的对象大小
     * @param data_p
     * @return
     */
//    static uint32_t sizeof_(void *data_p)
//    {
//        return LVMemory::getMemoryEntry(data_p)->getSize();
//    }

    /**
     * @brief 设置新建对象的地址
     * @param obj 对象地址
     * @param attr 属性地址
     */
    static void setNewObjectAddr(void * obj , void * attr = nullptr);
    static void unsetNewObjectAddr();

    /**
     * @brief 设置新建任务的地址
     * @param task
     */
    static void setNewTaskAddr(void *task);
    static void unsetNewTaskAddr();

    /**
     * @brief 设置新建动画对象地址
     * @param anim
     */
    static void setNewAnimAddr(void * anim);
    static void unsetNewAnimAddr();

    /**
     * @brief 设置新建对象组的地址
     * @param group
     */
    static void setNewGroupAddr(void *group);
    static void unsetNewGroupAddr();
};

/**********************
 *      MACROS
 **********************/

#endif /*LVMEMORY_H_*/
