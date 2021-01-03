#include "LVGroup.h"

extern "C"
{
//lv_group_t * lv_group_create_custom(void * (*func)(lv_ll_t * ll_p),lv_ll_t * ll_p);
//void lv_group_del_custom(lv_group_t * group);

extern void *& new_group_addr();


lv_group_t * lv_group_create_custom(void * (*func)(lv_ll_t * ll_p),lv_ll_t * ll_p)
{
    void * new_group = nullptr;
    if(new_group_addr())
    {
        new_group =  lv_ll_ins_head_with(ll_p, new_group_addr());
        new_group_addr() = nullptr;
    }
    else
    {
        new_group =  func(ll_p);
    }

    return static_cast<lv_group_t*>(new_group);
}

void lv_group_del_custom(lv_group_t * group)
{
    if(LVGroup::isVaild(group))
    {
        if(!group->class_ptr.deleted)
        {
            group->class_ptr.deleted = true;
            LVGroup * lvGroup = static_cast<LVGroup*>(group);
            delete lvGroup;
        }
    }
    else
    {
        lv_mem_free(group);
    }
}

extern lv_group_t * (*lv_group_create_custom_ptr)(void * (*func)(lv_ll_t * ll_p),lv_ll_t * ll_p);
extern void (* lv_group_del_custom_ptr)(lv_group_t * group);

bool lv_cpp_group_init()
{
	lv_group_create_custom_ptr = lv_group_create_custom;
	lv_group_del_custom_ptr = lv_group_del_custom;
	return true;
}

static bool lv_cpp_group = lv_cpp_group_init();

}

bool LVGroup::isVaild()
{
    return class_ptr.pointer && reinterpret_cast<LVGroup*>(class_ptr.pointer) == this;
}

bool LVGroup::isVaild(lv_group_t *group)
{
    return group && reinterpret_cast<LVGroup*>(group->class_ptr.pointer) == static_cast<LVGroup*>(group);
}
