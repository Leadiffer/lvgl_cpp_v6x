
/**
 * @file lvcppConfig.h
 * @version 6.1.1
 *
 */

#ifndef LVCPPCONFIG_H
#define LVCPPCONFIG_H

/*==================
 *  LV CPP USAGE
 *================*/
/*Modify some interface functions*/

#define LV_OBJ_CREATE(OBJ,FUNC,LIST) \
    extern lv_obj_t * lv_obj_create_custom(void*(*func)(lv_ll_t *),lv_ll_t * ll_p);\
    OBJ = lv_obj_create_custom(FUNC,LIST);

#define LV_OBJ_DEL(OBJ) \
    extern void lv_obj_del_custom(lv_obj_t * obj); \
    lv_obj_del_custom(OBJ);

#define LV_OBJ_ALLOCATE_EXT_ATTR(OBJ,FUNC,ATTR,SIZE) \
    extern void * lv_obj_allocate_ext_attr_custom(lv_obj_t * obj, void * (*func)(void *, size_t),void * data_p, size_t new_size); \
    ATTR = lv_obj_allocate_ext_attr_custom(OBJ,FUNC,ATTR,SIZE);



#define LV_TASK_CREATE_BASIC(TASK,FUNC,LIST,POS) \
    extern lv_task_t * lv_task_create_basic_custom(void * func,lv_ll_t * ll_p,void * n_pos); \
    TASK = lv_task_create_basic_custom((void*)FUNC,LIST,POS);

#define LV_TASK_DEL(TASK) \
    extern void lv_task_del_custom(lv_task_t * task); \
    lv_task_del_custom(TASK);



#define LV_ANIM_CREATE(ANIM,THIS,FUNC,LIST) \
    extern lv_anim_t * lv_anim_create_custom(lv_anim_t * anim, void * (*func)(lv_ll_t * ll_p), lv_ll_t * ll_p); \
    ANIM = lv_anim_create_custom(THIS,FUNC,LIST);

#define LV_ANIM_DEL(ANIM) \
    extern void lv_anim_del_custom(lv_anim_t * anim); \
    lv_anim_del_custom(ANIM);


#define LV_GROUP_CREATE(GROUP,FUNC,LIST) \
    extern lv_group_t * lv_group_create_custom(void * (*func)(lv_ll_t * ll_p),lv_ll_t * ll_p); \
    GROUP = lv_group_create_custom(FUNC,LIST);


#define LV_GROUP_DEL(GROUP) \
    extern void lv_group_del_custom(lv_group_t * group); \
    lv_group_del_custom(GROUP);

//添加一个类对象指针到数据结构中
#define LV_USE_CLASS_PTR 1
#if LV_USE_CLASS_PTR
//定义用户数据指针类型
typedef struct _class_ptr
{
    union
    {
        struct
        {
            uintptr_t pointer:(sizeof(uintptr_t)*8-1); //!< 数据地址
            uintptr_t deleted:1; //!< 数据是否有效
        };
        void * full;
    };
} lv_class_ptr;
#endif

#endif // LVCPPCONFIG_H
