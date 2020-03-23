/**
 * @file lv_task.c
 * An 'lv_task'  is a void (*fp) (void* param) type function which will be called periodically.
 * A priority (5 levels + disable) can be assigned to lv_tasks.
 */

#ifndef LVTASK_H
#define LVTASK_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_misc/lv_task.h>
#include "LVMemory.h"
#include "LVLinkList.h"
#include "../LVCore/LVCallBack.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
class LVTask;

/**
 * Tasks execte this type of functions.
 * same as  lv_task_cb_t but changed param.
 */
using LVTaskCallBack =  LVCallBack<void(LVTask*),void>;

/**
 * Descriptor of a lv_task
 */

/**
 * @brief LVGL中的任务类
 * 增加了以下功能:
 * 任务启停控制
 * 任务次数控制
 * 任务停止后自动清除
 * 快捷单次运行任务
 */
class LVTask
        : public lv_task_t
        , public LVLLNodeMeta<lv_task_t>
{
    LV_MEMORY

protected:
    LVTaskCallBack m_callBack; //!< 任务执行函数

    int m_times = -1;          //!< 任务需要运行的次数 0~0xEFFFFFFF ; -1 表示无次数限制
    int m_count = 0;           //!< 记录任务的运行次数

    uint8_t m_deleteAfterStop :1;//!< 任务停止时清除任务
    uint8_t m_priority:3;       //!< 任务优先级

public:
    /**
     * Possible priorities for lv_tasks
     */
    enum Priority : lv_task_prio_t
    {
        PRIO_OFF     = LV_TASK_PRIO_OFF    ,
        PRIO_LOWEST  = LV_TASK_PRIO_LOWEST ,
        PRIO_LOW     = LV_TASK_PRIO_LOW    ,
        PRIO_MID     = LV_TASK_PRIO_MID    ,
        PRIO_HIGH    = LV_TASK_PRIO_HIGH   ,
        PRIO_HIGHEST = LV_TASK_PRIO_HIGHEST,
        _PRIO_NUM    = _LV_TASK_PRIO_NUM   ,
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Init the lv_task module
     */
    static void coreInit(void)
    {
        lv_task_core_init();
    }

    /**
     * Call it  periodically to handle lv_tasks.
     */
    static LV_ATTRIBUTE_TASK_HANDLER void handler(void)
    {
        lv_task_handler();
    }

    /**
     * Create an "empty" task. It needs to initialzed with at least
     * `lv_task_set_cb` and `lv_task_set_period`
     * @return pointer to the craeted task
     */

    /**
     * Create a new lv_task
     * @param task a function which is the task itself
     * @param period call period in ms unit
     * @param prio priority of the task (LV_TASK_PRIO_OFF means the task is stopped)
     * @param user_data custom parameter
     * @return pointer to the new task
     */
    LVTask(const LVTaskCallBack& task_cb = LVTaskCallBack(), uint32_t period = 500,Priority prio = PRIO_MID/*, void * user_data = nullptr*/)
    {
        m_count =0;
        m_deleteAfterStop = 0;

        //默认任务创建后不会运行,直到调用了start().
        LVMemory::setNewTaskAddr(static_cast<lv_task_t*>(this));
        lv_task_create((lv_task_cb_t)callBackAgency,period,PRIO_OFF,this);
        class_ptr.pointer = reinterpret_cast<uintptr_t>(this); //关联对象
        class_ptr.deleted = false;
        LVMemory::unsetNewTaskAddr();
        m_callBack = task_cb;
        m_priority = prio;

        lvInfo("LVTask(0x%p) Created. ",this);
    }

    /**
     * Delete a lv_task
     * @param task pointer to task_cb created by task
     */

    virtual ~LVTask()
    {
        if(!class_ptr.deleted)
        {
            class_ptr.deleted = true;
            lv_task_del(this);
        }
        lvInfo("LVTask(0x%p) Destroyed.",this);
    }

    /**
     * @brief check task is vailed
     * @return
     */
    bool isVaild();

    /**
     * @brief check task is vailed task instance
     * @param obj
     * @return
     */
    static bool isVaild(lv_task_t * task);

    /**
     * Set the callback the task (the function to call periodically)
     * @param task pointer to a task
     * @param task_cb the function to call periodically
     */
    void setCallBack(const LVTaskCallBack & task_cb)
    {
        m_callBack = task_cb;
    }

    /**
     * Set new priority for a lv_task
     * @param task pointer to a lv_task
     * @param prio the new priority
     */
    void setPriority(Priority prio)
    {
        if(m_priority != prio)
        {
            m_priority = prio;
            if(isRunning())
            {
                lv_task_set_prio(this, prio);
            }
        }
    }

    /**
     * Set new period for a lv_task
     * @param task pointer to a lv_task
     * @param period the new period
     */
    void setPeriod(uint32_t period)
    {
        lv_task_set_period(this,period);
    }

    /**
     * Make a lv_task ready. It will not wait its period.
     * @param task pointer to a lv_task.
     */
    void readyToRun()
    {
        lv_task_ready(this);
    }

    /**
     * Delete the lv_task after one call
     * @param task pointer to a lv_task.
     */
    void once()
    {
        lv_task_once(this);
    }

    /**
     * Reset a lv_task.
     * It will be called the previously set period milliseconds later.
     * @param task pointer to a lv_task.
     */
    void reset()
    {
        lv_task_reset(this);
    }

    /**
     * Enable or disable the whole  lv_task handling
     * @param en: true: lv_task handling is running, false: lv_task handling is suspended
     */
    static void setWholeTaskEnable(bool en)
    {
        lv_task_enable(en);
    }

    /**
     * Get idle percentage
     * @return the lv_task idle in percentage
     */
    static uint8_t getIdlePercentage(void)
    {
        return lv_task_get_idle();
    }

    /*******************
     *     ENHANCE
     *******************/

    /**
     * @brief set User custom parameter or data
     * @param user_data
     */
    void setUserData(void * user_data)
    {
        this->user_data = user_data;
    }

    /**
     * @brief get User Data
     */
    void * getUserData()
    {
        return this->user_data;
    }

    //////////////////// 增强功能  //////////////////////////////////

    /**
     * @brief 开始任务
     */
    void start()
    {
        lv_task_set_prio(this, m_priority);
        reset();
    }

    void start(Priority prio)
    {
        setPriority(prio);
        lv_task_set_prio(this, m_priority);
    }

    /**
     * @brief 开始任务
     * @param period 指定任务周期
     * @param times 指定任务次数
     */
    void start(uint32_t period,int times = -1)
    {
        setPeriod(period);
        setTimes(times);
        start();
    }

    /**
     * @brief 开始任务, 同时执行一遍任务
     */
    void startAndRun()
    {
        start();
        //不等待直接执行一遍任务
        checkAndRun();
    }

    /**
     * @brief 停止任务
     *
     */
    void stop()
    {
        lv_task_set_prio(this, LV_TASK_PRIO_OFF);
        resetCount();

        if(isDeleteAfterStop())
            delete this;
    }

    void restart()
    {
        if(!isDeleteAfterStop())
        {
           stop();
           start();
        }
        else
        {
           //FIXME:对于运行后清除的任务,无法再次启动
           stop();
        }
    }

    bool isRunning()
    {
        return  this->prio != LV_TASK_PRIO_OFF;
    }

    /**
     * @brief 任务的优先级
     * @return
     */
    Priority getPriority(){ return Priority(m_priority); }

    /**
     * @brief 任务运行的总次数
     * @return
     */
    int getTimes(){ return m_times;  }

    /**
     * @brief 设置任务运行次数
     * 更改运行次数后,之前的运行次数统计需要手动清除
     * @param n 0~0xEFFFFFFF ; -1 表示无次数限制
     * @return
     */
    void setTimes(int n = -1){ m_times = n; }

    /**
     * @brief 任务的剩余运行次数
     * @return
     */
    int getSurplusTimes(){ return m_times == -1 ? -1: m_times - m_count; }

    /**
     * @brief 任务的从上一次运行后执行的次数
     * @return
     */
    int getCount(){ return m_count; }

    /**
     * @brief 重置任务计数
     */
    void resetCount(){ m_count = 0; }

    /**
     * @brief 是否停止后就清除任务
     * @return
     */
    bool isDeleteAfterStop(){ return  m_deleteAfterStop; }

    /**
     * @brief 设置停止后就清除任务
     * @param value
     */
    void setDeleteAfterStop(bool value){ m_deleteAfterStop = value; }

    /**
     * @brief 快捷方便的函数,执行一次任务函数
     * @param period 时间间隔
     * @param func 任务函数
     */
    static void once(uint32_t period ,const LVTaskCallBack & callback)
    {
        LVTask * onceTask = new LVTask(callback);
        onceTask->setPeriod(period);
        onceTask->setDeleteAfterStop(true);
        onceTask->start(period,1);
    }

    /**
     * @brief 当前任务的函数
     * @return
     */
    LVTaskCallBack getCallBack()
    {
        return m_callBack;
    }

    /**
     * @brief 任务运行前的条件检查
     *
     * //NOTE: 应该将该函数保护起来的
     */
    //virtual
    void checkAndRun()
    {
        //检查任务运行的条件
        if(isRunning())
        {
            //检查可运行次数
            if(getSurplusTimes())
            {
                //统计任务运行次数
                ++m_count;
                run();

                if(!getSurplusTimes())
                {
                    stop();
                }
            }
            else
            {
                stop();
            }
        }
    }

    /**
     * @brief LVTask 任务回调函数的代理函数
     * @param param
     */
    static void callBackAgency(struct _lv_task_t * t)
    {
        LVTask * task = (LVTask *)t;

        if(task)
        {
            task->checkAndRun();
        }
    }

protected:

    /**
     * @brief 具体的任务函数,需要子类去实现
     * 一定注意,函数内不能存在阻塞
     */
    //virtual
    void run()
    {
        if(m_callBack)
            m_callBack(this);
        else
            lvWarn("LVTask::run : m_callBack is null.");
    }

} LV_ATTRIBUTE_MEM_ALIGN ;
/**********************
 *      MACROS
 **********************/


#endif
