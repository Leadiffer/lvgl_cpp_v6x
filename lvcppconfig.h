
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

#ifndef assert
#define assert(b)
#endif

#define LV_OBJ_CREATE(OBJ,FUNC,LIST) \
    OBJ = lv_obj_create_custom(FUNC,LIST);

#define LV_OBJ_DEL(OBJ) \
    lv_obj_del_custom(OBJ);

#define LV_OBJ_ALLOCATE_EXT_ATTR(OBJ,FUNC,ATTR,SIZE) \
    ATTR = lv_obj_allocate_ext_attr_custom(OBJ,FUNC,ATTR,SIZE);



#define LV_TASK_CREATE_BASIC(TASK,FUNC,LIST,POS) \
    TASK = lv_task_create_basic_custom((void*)FUNC,LIST,POS);

#define LV_TASK_DEL(TASK) \
    lv_task_del_custom(TASK);



#define LV_ANIM_CREATE(ANIM,THIS,FUNC,LIST) \
    ANIM = lv_anim_create_custom(THIS,FUNC,LIST);

#define LV_ANIM_DEL(ANIM) \
    lv_anim_del_custom(ANIM);



#define LV_GROUP_CREATE(GROUP,FUNC,LIST) \
    GROUP = lv_group_create_custom(FUNC,LIST);

#define LV_GROUP_DEL(GROUP) \
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
