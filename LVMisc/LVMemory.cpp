#include "LVMemory.h"
#include "LVLog.h"


#ifdef __cplusplus
extern "C" {
#endif

//NOTE: add By RenShen
static void ** placement_alloc = NULL; /*redirect memory allocate action, return redirect_alloc as result;*/
static uint32_t placement_alloc_count = 0;

static void ** skip_free = NULL;
static uint32_t skip_free_count = 0;

void * placementAllocCheck()
{
    if(placement_alloc_count > 0)
    {
        placement_alloc_count--;
        void * alloc = *(placement_alloc++);
        lvTrace("placementAlloc : %p",alloc);
        return alloc;
    }
    return NULL;
}

uint8_t skipFree(const void * data_p)
{
    if(skip_free_count > 0)
    {
        for (uint32_t i = 0; i < skip_free_count; ++i)
        {
            //跳过这个地址,不释放此处内存
            if(skip_free[i] == data_p)
            {
                skip_free[i] = NULL;
                return 1;
            }
        }
    }
    return 0;
}

#ifdef __cplusplus
}
#endif

static void * alloc_list[2];
static void * free_list[2];

void LVMemory::placementAlloc(void *data_p)
{
    alloc_list[0] = data_p;
    placementAlloc(alloc_list,1);
    lvTrace("LVMemory::placementAlloc : %p",data_p);
}

void LVMemory::placementAlloc(void *data1_p, void *data2_p)
{
    alloc_list[0] = data1_p;
    alloc_list[1] = data2_p;
    placementAlloc(alloc_list,2);
    lvTrace("LVMemory::placementAlloc : %p , %p",data1_p,data2_p);
}

void LVMemory::placementAlloc(void ** datas_p, uint32_t count)
{
    placement_alloc = datas_p;
    placement_alloc_count = count;
}

void LVMemory::resetPlacementAlloc()
{
    placement_alloc = NULL;
    placement_alloc_count = 0;
    lvTrace("LVMemory::resetPlacementAlloc ");
}

void LVMemory::skipFree(void *data_p)
{
    free_list[0] = data_p;
    skipFree(free_list,1);
}

void LVMemory::skipFree(void ** datas_p,uint32_t count)
{
    skip_free = datas_p;
    skip_free_count = count;
}

void LVMemory::resetSkipFree()
{
    skip_free = NULL;
    skip_free_count = 0;
}

void LVMemoryMonitor::updateMonitor()
{
    LVMemory::monitor(this);
}
