/**
 * @file anim.h
 *
 */

#ifndef LVANIMATION_H
#define LVANIMATION_H

/*********************
 *      INCLUDES
 *********************/
#include <lv_misc/lv_anim.h>

#if LV_USE_ANIMATION

//#include <functional>
#include "LVMemory.h"
#include "../LVCore/LVCallBack.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

class LVAnimation;

/*Type of the animated value*/
using LVAnimValue = lv_anim_value_t;

/* Generic prototype of "animator" functions.
 * First parameter is the variable to animate.
 * Second parameter is the value to set.
 * Compatible with `lv_xxx_set_yyy(obj, value)` functions
 *
 * same as lv_anim_exec_xcb_t
 */
using LVAnimExecCallBack = LVCallBack<void(LVAnimation *, LVAnimValue),void>;
//using LVAnimExecCallBack = lv_anim_exec_xcb_t;

/* Same as `lv_anim_exec_cb_t` but receives `lv_anim_t *` as the first parameter.
 * It's more consistent but less convenient. Might be used by binding generator functions.
 *
 * same as lv_anim_custom_exec_cb_t
 */
//using LVAnimCustomExecCallBack = LVCallBack<void(struct _lv_anim_t *, lv_anim_value_t)>;
////using LVAnimCustomExecCallBack = lv_anim_custom_exec_cb_t;

/*Get the current value during an animation
 *
 * same as lv_anim_path_cb_t
 */
using LVAnimPathCallBack = LVCallBack<LVAnimValue(const LVAnimation *),LVAnimValue>;
//using LVAnimPathCallBack = lv_anim_path_cb_t;

/*Callback to call when the animation is ready
 *
 * same as lv_anim_ready_cb_t
 */
using LVAnimReadyCallBack = LVCallBack<void(LVAnimation *),void>;
//using LVAnimReadyCallBack = lv_anim_ready_cb_t;

///*Describe an animation*/

/**
 * @brief LVGL Animation 动画类
 * 由于lvgl anim的特殊实现方式,每个正在执行的动画都会有两份信息数据,
 * 虽然原生的lvgl可以在Create 后删除用户管理的动员对象,
 * 但是LVGL_CPP接口中,动画对象,一定不能删除,否则动画会出错停止
 *
 * NOTE: 由于ExecCallBack 和 CustomExecCallBack
 * 除了回调函数的形式参数不同之外,实现都一样,因此屏蔽了CustomExec的所有接口
 */
class LVAnimation : public lv_anim_t
{
    LV_MEMORY

public:

    /** Can be used to indicate if animations are enabled or disabled in a case*/
    enum State
    {
        ANIM_OFF = LV_ANIM_OFF,
        ANIM_ON = LV_ANIM_ON,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Initialize an animation variable.
     * E.g.:
     * lv_anim_t a;
     * lv_anim_init(&a);
     * lv_anim_set_...(&a);
     * lv_anim_create(&a);
     * @param a pointer to an `lv_anim_t` variable to initialize
     */
    LVAnimation()
    {
        lv_anim_init(this);
    }

    LVAnimation(const lv_anim_t& anim)
    {
        memcpy(this,&anim,sizeof(lv_anim_t));
    }

    LVAnimation(const LVAnimation& anim)
    {
        memcpy(this,&anim,sizeof(LVAnimation));
    }

    //static LVAnimation * fromAnim(const lv_anim_t * anim)
    //{
    //    return (LVAnimation *) anim;
    //    return new(anim) LVAnimation;
    //}

    ~LVAnimation()
    {
        //首先清理掉在动画框架中的副本数据
        lv_anim_del(this->user_data,lvAnimationExecCallBackAgent);
    }

    /**
     * Init. the animation module
     */
    static inline void coreInit(void)
    {
        lv_anim_core_init();
    }

    /**
     * Set a variable to animate function to execute on `var`
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param var pointer to a variable to animate
     * @param exec_cb a function to execute.
     *                LittelvGL's built-in functions can be used.
     *                E.g. lv_obj_set_x
     */
    void setExecCallBack(LVAnimExecCallBack exec_cb)
    {
        m_exec_cb = exec_cb;
        lv_anim_set_exec_cb(this,this,lvAnimationExecCallBackAgent);
    }

    /**
     * Set the duration and delay of an animation
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param duration duration of the animation in milliseconds
     * @param delay delay before the animation in milliseconds
     */
    inline void setTime(uint16_t duration, uint16_t delay)
    {
        lv_anim_set_time(this,duration,delay);
    }

    /**
     * Set the start and end values of an animation
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param start the start value
     * @param end the end value
     */
    inline void setValues(LVAnimValue start, LVAnimValue end)
    {
        lv_anim_set_values(this,start,end);
    }

    /**
     * Similar to `lv_anim_set_var_and_cb` but `lv_anim_custom_exec_cb_t` receives
     * `lv_anim_t * ` as its first parameter instead of `void *`.
     * This function might be used when LittlevGL is binded to other languages because
     * it's more consistent to have `lv_anim_t *` as first parameter.
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param exec_cb a function to execute.
     */
    //void setCustomExecCallBack(LVAnimCustomExecCallBack exec_cb)
    //{
    //    lv_anim_set_custom_exec_cb(this,exec_cb);
    //}

    /**
     * Set the path (curve) of the animation.
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param path_cb a function the get the current value of the animation.
     *                The built in functions starts with `lv_anim_path_...`
     */
    void setPathCallBack(const LVAnimPathCallBack& path_cb)
    {
        m_path_cb = path_cb;
        lv_anim_set_path_cb(this,lvAnimationPathCallBackAgent);
    }

    /**
     * Set a function call when the animation is ready
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param ready_cb a function call when the animation is ready
     */
    void setReadyCallBack(const LVAnimReadyCallBack& ready_cb)
    {
        if(ready_cb.isStdFunc())
        {
            m_ready_cb = ready_cb;
            lv_anim_set_ready_cb(this,(lv_anim_ready_cb_t)lvAnimationReadyCallBackAgent);
        }
        else
        {
            lv_anim_set_ready_cb(this,(lv_anim_ready_cb_t)ready_cb.getFuncPtr());
        }

    }

    /**
     * Make the animation to play back to when the forward direction is ready
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param wait_time time in milliseconds to wait before starting the back direction
     */
    void setPlayback(uint16_t wait_time)
    {
        lv_anim_set_playback(this,wait_time);
    }

    /**
     * Disable playback. (Disabled after `lv_anim_init()`)
     * @param a pointer to an initialized `lv_anim_t` variable
     */
    void clearPlayback()
    {
        lv_anim_clear_playback(this);
    }

    /**
     * Make the animation to start again when ready.
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param wait_time time in milliseconds to wait before starting the animation again
     */
    void setRepeat(uint16_t wait_time)
    {
        lv_anim_set_repeat(this,wait_time);
    }

    /**
     * Disable repeat. (Disabled after `lv_anim_init()`)
     * @param a pointer to an initialized `lv_anim_t` variable
     */
    void clearRepeat()
    {
        lv_anim_clear_repeat(this);
    }

    /**
     * Set a user specific data for the animation
     * @param a pointer to an initialized `lv_anim_t` variable
     * @param user_data the user data
     */
    void setUserData(lv_anim_user_data_t user_data)
    {
        lv_anim_set_user_data(this,user_data);
    }

    /**
     * Get the user data
     * @param a pointer to an initialized `lv_anim_t` variable
     * @return the user data
     */
    lv_anim_user_data_t getUserData()
    {
        return lv_anim_get_user_data(this);
    }

    /**
     * Get pointer to the user data
     * @param a pointer to an initialized `lv_anim_t` variable
     * @return pointer to the user data
     */
    lv_anim_user_data_t * getUserDataPtr()
    {
        return lv_anim_get_user_data_ptr(this);
    }

    /**
     * Create an animation
     * @param a an initialized 'anim_t' variable. Not required after call.
     */
    static void create(lv_anim_t * a)
    {
        lv_anim_create(a);
    }

    void create()
    {
        lv_anim_create(this);
    }

    /**
     * Delete an animation of a variable with a given animator function
     * @param var pointer to variable
     * @param exec_cb a function pointer which is animating 'var',
     *           or NULL to ignore it and delete all the animations of 'var
     * @return true: at least 1 animation is deleted, false: no animation is deleted
     */
    //static bool delete_(void * var, LVAnimExecCallBack exec_cb)
    //{
    //    return lv_anim_del(var,exec_cb);
    //}

    /**
     * Delete an aniamation by getting the animated variable from `a`.
     * Only animations with `exec_cb` will be deleted.
     * This function exist becasue it's logical that all anim functions receives an
     * `lv_anim_t` as their first parameter. It's not practical in C but might makes
     * the API more conequent and makes easier to genrate bindings.
     * @param a pointer to an animation.
     * @param exec_cb a function pointer which is animating 'var',
     *           or NULL to ignore it and delete all the animations of 'var
     * @return true: at least 1 animation is deleted, false: no animation is deleted
     */
    //bool customDelete(LVAnimCustomExecCallBack exec_cb)
    //{
    //    return lv_anim_del(this->var, (lv_anim_exec_cb_t)exec_cb);
    //}

    /**
     * Get the number of currently running animations
     * @return the number of running animations
     */
    static uint16_t countRunning(void)
    {
        return lv_anim_count_running();
    }

    /**
     * Calculate the time of an animation with a given speed and the start and end values
     * @param speed speed of animation in unit/sec
     * @param start start value of the animation
     * @param end end value of the animation
     * @return the required time [ms] for the animation with the given parameters
     */
    static uint16_t speedToTime(uint16_t speed, LVAnimValue start, LVAnimValue end)
    {
        return lv_anim_speed_to_time(speed,start,end);
    }

    /**
     * Calculate the current value of an animation applying linear characteristic
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathLinear()
    {
        return lv_anim_path_linear(this);
    }

    /**
     * Calculate the current value of an animation slowing down the start phase
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathEaseIn()
    {
        return lv_anim_path_ease_in(this);
    }

    /**
     * Calculate the current value of an animation slowing down the end phase
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathEaseOut()
    {
        return lv_anim_path_ease_out(this);
    }

    /**
     * Calculate the current value of an animation applying an "S" characteristic (cosine)
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathEaseInOut()
    {
        return lv_anim_path_ease_in_out(this);
    }

    /**
     * Calculate the current value of an animation with overshoot at the end
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathOverShoot()
    {
        return lv_anim_path_overshoot(this);
    }

    /**
     * Calculate the current value of an animation with 3 bounces
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathBounce()
    {
        return lv_anim_path_bounce(this);
    }

    /**
     * Calculate the current value of an animation applying step characteristic.
     * (Set end value on the end of the animation)
     * @param a pointer to an animation
     * @return the current value to set
     */
    LVAnimValue pathStep()
    {
        return lv_anim_path_step(this);
    }

    /*******************
     *     ENHANCE
     *******************/


    static void lvAnimationExecCallBackAgent(void * a, lv_anim_value_t value)
    {
        LVAnimation * anim = (LVAnimation*)((lv_anim_t*)a);
        if(anim&&anim->m_exec_cb)
        {
            anim->m_exec_cb(anim,value);
        }
    }

    static LVAnimValue lvAnimationPathCallBackAgent(const lv_anim_t * a)
    {
        LVAnimation * anim = (LVAnimation *)a;
        if(anim&&anim->m_path_cb)
        {
            return anim->m_path_cb(anim);
        }
        return 0;
    }

    static void lvAnimationReadyCallBackAgent(lv_anim_t * a)
    {
        LVAnimation * anim = static_cast<LVAnimation *>(a);
        if(anim&&anim->m_ready_cb)
        {
            anim->m_ready_cb(anim);
        }
    }


protected:
    LVAnimExecCallBack       m_exec_cb;   /*Function to execute to animate*/
    LVAnimPathCallBack       m_path_cb;   /*An array with the steps of animations*/
    LVAnimReadyCallBack      m_ready_cb;  /*Call it when the animation is ready*/

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_ANIMATION == 0*/

#endif /*LVANIMATION_H*/


