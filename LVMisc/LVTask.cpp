#include "LVTask.h"

extern "C"
{
//lv_task_t * lv_task_create_basic_custom(void * func,lv_ll_t * ll_p,void * n_pos);
//void lv_task_del_custom(lv_task_t * task);

extern void *& new_task_addr();


lv_task_t * lv_task_create_basic_custom(void * func,lv_ll_t * ll_p,void * n_pos)
{
    static void * func_head = reinterpret_cast<void *>(lv_ll_ins_head);
    static void * func_prev = reinterpret_cast<void *>(lv_ll_ins_prev);
    //static void * func_tail = reinterpret_cast<void *>(lv_ll_ins_tail);

    void * new_task = nullptr;
    //判断函数
    if(new_task_addr())
    {
        if(func == func_head)
            new_task = lv_ll_ins_head_with(ll_p,new_task_addr());
        else if(func == func_prev)
            new_task =  lv_ll_ins_prev_with(ll_p,n_pos,new_task_addr());
        else
            new_task = lv_ll_ins_tail_with(ll_p,new_task_addr());
        new_task_addr() = nullptr;
    }
    else
    {
        if(n_pos == nullptr)
            new_task = reinterpret_cast<void* (*) (lv_ll_t * )>(func)(ll_p);
        else
            new_task =  reinterpret_cast<void* (*) (lv_ll_t *,void *)>(func)(ll_p,n_pos);
    }

    return static_cast<lv_task_t*>(new_task);
}

void lv_task_del_custom(lv_task_t * task)
{
    if(LVTask::isVaild(task))
    {
        if(!task->class_ptr.deleted)
        {
            task->class_ptr.deleted = true;
            LVTask * lvTask = static_cast<LVTask*>(task);
            delete lvTask;
        }
    }
    else
    {
        lv_mem_free(task);
    }
}


extern lv_task_t * (*lv_task_create_basic_custom_ptr)(void * func,lv_ll_t * ll_p,void * n_pos);
extern void (*lv_task_del_custom_ptr)(lv_task_t * task);

bool lv_cpp_task_init()
{
	lv_task_create_basic_custom_ptr = lv_task_create_basic_custom;
	lv_task_del_custom_ptr = lv_task_del_custom;
	return true;
}

static bool lv_cpp_task = lv_cpp_task_init();

}

bool LVTask::isVaild()
{
    return class_ptr.pointer && reinterpret_cast<LVTask*>(class_ptr.pointer) == this;
}

bool LVTask::isVaild(lv_task_t *task)
{
    if(task)
    {
        return task->class_ptr.pointer && reinterpret_cast<LVTask*>(task->class_ptr.pointer) == static_cast<LVTask*>(task);
    }
    else
    {
        return false;
    }

}
