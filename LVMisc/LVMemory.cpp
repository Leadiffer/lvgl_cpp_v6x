#include "LVMemory.h"
#include "LVLog.h"

extern "C"
{
    void *& new_obj_addr()
    {
        static void * obj = nullptr;
        return obj;
    }

    void *& new_obj_attr_addr()
    {
        static void * attr = nullptr;
        return attr;
    }

    void *& new_obj_attr_obj_addr()
    {
        static void * obj = nullptr;
        return obj;
    }

    void *& new_task_addr()
    {
        static void * task = nullptr;
        return task;
    }

    void *& new_anim_addr()
    {
        static void * anim = nullptr;
        return anim;
    }

    void *& new_group_addr()
    {
        static void * group = nullptr;
        return group;
    }
}

void LVMemoryMonitor::updateMonitor()
{
    LVMemory::monitor(this);
}

void LVMemory::setNewObjectAddr(void *obj, void *attr)
{
    new_obj_addr() = obj;
    new_obj_attr_addr() = attr;
    new_obj_attr_obj_addr() = obj;
}

void LVMemory::unsetNewObjectAddr()
{
    new_obj_addr() = nullptr;
    new_obj_attr_addr() = nullptr;
    new_obj_attr_obj_addr() = nullptr;
}

void LVMemory::setNewTaskAddr(void *task)
{
    new_task_addr() = task;
}

void LVMemory::unsetNewTaskAddr()
{
    new_task_addr() = nullptr;
}

void LVMemory::setNewAnimAddr(void * anim)
{
    new_anim_addr() = anim;
}

void LVMemory::unsetNewAnimAddr()
{
    new_anim_addr() = nullptr;
}

void LVMemory::setNewGroupAddr(void *group)
{
    new_group_addr() = group;
}

void LVMemory::unsetNewGroupAddr()
{
    new_group_addr() = nullptr;
}
