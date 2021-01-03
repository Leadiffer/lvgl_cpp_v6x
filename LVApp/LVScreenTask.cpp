#include "LVScreenTask.h"
#include "LVScreen.h"

LVScreenTask::LVScreenTask(LVScreen * screen ,uint32_t period, Priority prio)
    : LVTask(nullptr,period, prio)
      ,m_runWithScreen(true)
      ,m_stopWithScreen(true)
{
    //关联所属屏幕
    if(screen != nullptr)
        setScreen(screen);
}

LVScreenTask::~LVScreenTask()
{
    logoutTask();
}

void LVScreenTask::setScreen(LVScreen * screen)
{
    //注册任务到任务列表
    if(m_screen != screen)
    {
        //先注销
        if(m_screen != nullptr && m_nodeId != nullptr)
            m_screen->logoutTask(this);

        //再注册
        if(screen != nullptr)
            screen->loginTask(this);
        m_screen = screen;
    }
}

void LVScreenTask::onScreenShow()
{
    if(m_runWithScreen)
    {
        start();
    }
}

void LVScreenTask::onScreenHide()
{
    if(m_stopWithScreen)
        this->stop();
}

void LVScreenTask::loginTask()
{
    if(m_screen != nullptr && m_nodeId == nullptr)
        m_screen->loginTask(this);
}

void LVScreenTask::logoutTask()
{
    if(m_screen != nullptr && m_nodeId != nullptr)
    {
        m_screen->logoutTask(this);
        m_nodeId = nullptr;
    }
}
