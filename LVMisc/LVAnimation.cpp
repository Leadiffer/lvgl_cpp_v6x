#include "LVAnimation.h"
#include <lv_misc/lv_ll.h>

extern "C"
{
//    lv_anim_t * lv_anim_create_custom(lv_anim_t * anim, void * (*func)(lv_ll_t * ll_p), lv_ll_t * ll_p);
//    void lv_anim_del_custom(lv_anim_t * anim);

    extern void *& new_anim_addr();

lv_anim_t * lv_anim_create_custom(lv_anim_t * anim, void * (*func)(lv_ll_t * ll_p), lv_ll_t * ll_p)
{
    void * new_anim = nullptr;
    if(new_anim_addr())
    {
        new_anim = lv_ll_ins_head_with(ll_p,anim);
        new_anim_addr() = nullptr;
    }
    else
    {
        new_anim = func(ll_p);
    }
    return static_cast<lv_anim_t *>(new_anim);
}

void lv_anim_del_custom(lv_anim_t * anim)
{
    if(LVAnimation::isVaild(anim))
    {
        if(!anim->class_ptr.deleted)
        {
            anim->class_ptr.deleted = true;
            LVAnimation * lvAnim = static_cast<LVAnimation *>(anim);
            delete lvAnim;
        }
    }
    else
    {
        lv_mem_free(anim);
    }
}

extern lv_anim_t * (*lv_anim_create_custom_ptr)(lv_anim_t * anim, void * (*func)(lv_ll_t * ll_p), lv_ll_t * ll_p);
extern void(* lv_anim_del_custom_ptr)(lv_anim_t * anim);

bool lv_cpp_anim_init()
{
	lv_anim_create_custom_ptr = lv_anim_create_custom;
	lv_anim_del_custom_ptr = lv_anim_del_custom;
	return true;
}

static bool lv_cpp_anim = lv_cpp_anim_init();

}

bool LVAnimation::isVaild()
{
    return class_ptr.pointer && reinterpret_cast<LVAnimation*>(class_ptr.pointer) == this;
}

bool LVAnimation::isVaild(lv_anim_t *anim)
{
    return anim && reinterpret_cast<LVAnimation*>(anim->class_ptr.pointer) == static_cast<LVAnimation*>(anim);
}
