#ifndef LVSCREENTASK_H
#define LVSCREENTASK_H

#include <LVMisc/LVTask.h>
#include <LVMisc/LVLinkList.h>
#include <LVMisc/LVMemory.h>

class LVScreen;

/**
 * @brief 与屏幕密切相关的任务
 * 屏幕显示默认就运行
 * 屏幕隐藏默认就停止
 */
class LVScreenTask
        : public LVTask
{
    LV_MEMORY

    friend class LVScreen;
protected:
    LVScreen * m_screen = nullptr; //!< 所属的屏幕
    bool m_runWithScreen; //!< 屏幕显示时就运行
    bool m_stopWithScreen;//!< 屏幕隐藏时就停止
    LVLLNode<LVScreenTask*> * m_nodeId = nullptr; //!< 在任务列表中的指针
public:
    /**
     * @brief ScreenTask 屏幕任务构造函数
     * @param screen 任务所属的屏幕
     * @param period 任务周期 默认500毫秒
     * @param prio 任务优先级 默认中等优先级
     */
    LVScreenTask(LVScreen * screen , uint32_t period = 500, Priority prio = PRIO_LOWEST);

    virtual ~LVScreenTask();

    LVScreen * screen() { return m_screen; }
    void setScreen(LVScreen * screen);

    void setRunWithScreen(bool value = true) { m_runWithScreen = value; }
    void setStopWithScreen(bool value = true) { m_stopWithScreen = value; }

    bool isRunWithScreen() { return m_runWithScreen; }
    bool isStopWithScreen() { return m_stopWithScreen; }

protected:
    /**
     * @brief 屏幕显示时调用
     */
    virtual void onScreenShow();
    /**
     * @brief 屏幕隐藏时调用
     */
    virtual void onScreenHide();

    /**
     * @brief 注册任务到屏幕的任务列表
     */
    void loginTask();

    /**
     * @brief 从屏幕的任务列表中注销任务
     */
    void logoutTask();
};

#endif // LVSCREENTASK_H
