#ifndef LVSCREEN_H
#define LVSCREEN_H

#include <LVCore/LVObject.h>
#include <LVCore/LVPointer.h>
#include <LVCore/LVScopedPointer.h>
#include <LVCore/LVSharedPointer.h>
#include <LVMisc/LVLinkList.h>
#include <LVMisc/LVColor.h>
#include <LVObjx/LVMessageBox.h>
#include <LVObjx/LVBar.h>
#include "LVScreenTask.h"
#include "i18n.h"

/**
 * @brief 定义一个屏幕界面的基类
 * 屏幕管理
 *
 * 控制显示
 * 控制隐藏
 *
 * 管理与屏幕相关的任务
 *
 */
class LVScreen
        : public LVObject
{
    LV_MEMORY

    friend class MarlinGUI;
    friend class LVScreenTask;
protected:

    //////////// 基本属性 //////////////////////
    char* m_name = nullptr; //!< 界面名称
    bool m_inited = false; //!< 标识屏幕是否初始化
    bool m_deleteAfterHide = false; //!< 隐藏后清理屏幕数据
    bool m_clearAfterHide = true; //!< 隐藏后清理屏幕(子对象)数据
    int32_t m_memoryUsed = -1; //!< 统计内存消耗

    //////////// 外观属性 /////////////////
    LVColor m_screenColor; //!< 屏幕颜色

    ////////// 形成屏幕的显示链 ////////////////
    LVPointer<LVScreen> m_preScreen ; //!< 前一个屏幕
    LVPointer<LVScreen> m_nextScreen ; //!< 后一个屏幕

    static LVPointer<LVScreen> s_lastScreen; //!< 之前显示的屏幕
    static LVPointer<LVScreen> s_currScreen; //!< 当前显示的屏幕

    /////////// 任务列表 ////////////
    LVLinkList<LVScreenTask*> m_taskList; //!< 屏幕拥有的任务列表


    //////////// 内存调试 //////////////////

    /**
     * @brief 内存调试器
     * 一个简单的线条指示内存状态
     * @return
     */
    static LVBar *memoryDebuger();

    /**
     * @brief 气泡消息
     * @return
     */
    static LVLabel *bubble();

    /**
     * @brief 消息提示框
     * @return
     */
    static LVMessageBox * messageBox();

public:

    /**
     * @brief The CustomSignal enum
     */
    enum CustomSignal : lv_signal_t
    {
        /* 语言变化 */
        SIGNAL_LANG_CHG             = SIGNAL_GET_EDITABLE+10 , //语言变化信号
        SIGNAL_SCREEN_CHG           = SIGNAL_GET_EDITABLE+11   //屏幕变化信号(屏幕尺寸, 屏幕方向)
    };

    LVScreen(const char* name = "" ,LVObject * parent = nullptr);

    ~LVScreen();

    /**
     * @brief 显示屏幕
     * @return true 显示成功 ; false 显示失败
     */
    bool show();

    /**
     * @brief 显示之前运行的函数
     * 可用来判断屏幕是否能够显示
     * @return true 可以显示 ; false 不能显示
     */
    virtual bool beforeShow();

    /**
     * @brief 显示之后
     */
    virtual void afterShow(){}

    /**
     * @brief 隐藏屏幕
     * 跳转到上一个屏幕或者主屏幕
     * @return true 显示成功 ; false 显示失败
     */
    bool hide();

    /**
     * @brief 隐藏之前
     * 可用来判断屏幕是否能够隐藏
     * @return true 可以显示 ; 不能隐藏
     */
    virtual bool beforeHide(){return true;}

    /**
     * @brief 隐藏之后
     */
    virtual void afterHide(){}

    /**
     * @brief 当前正在显示的屏幕
     * @return
     */
    static LVScreen * currScreen();
    static bool hasCurrScreen();

    /**
     * @brief 上一个显示的屏幕
     * 如果屏幕删除了,就没有了
     */
    static LVScreen * lastScreen();
    static bool hasLastScreen();

    /**
     * @brief 显示屏幕链的前一个屏幕
     */
    LVScreen * preScreen();
    bool hasPreScreen();
    void setPreScreen(LVScreen * screen);

    /**
     * @brief 显示屏幕链的后一个屏幕
     */
    LVScreen *  nextScreen();
    bool hasNextScreen();
    void setNextScreen(LVScreen * screen);

    /**
     * @brief 在屏幕上是否可见
     * @return
     */
    bool isVisible();

    /**
     * @brief 设置屏幕的显隐
     * @param value
     */
    void setVisible(bool value);

    /**
     * @brief 最后显示的一个屏幕界面
     * @return
     */
    static LVScreen * LastScreen();

    /**
     * @brief 当前显示的屏幕界面
     * @return
     */
    static LVScreen * CurrScreen();

    /**
     * @brief 屏幕的背景颜色
     * @return
     */\
    LVColor screenColor();

    /**
     * @brief 设置屏幕的背景颜色
     * @param color
     */
    void setScreenColor(LVColor color);

    bool isDeleteAfterHide();
    void setDeleteAfterHide(bool value);

    bool isInited(){ return m_inited; }

    /**
     * @brief 获取屏幕宽度
     * @return
     */
    static uint16_t width();

    /**
     * @brief 获取屏幕高度
     * @return
     */
    static uint16_t height();

    /**
     * @brief 获取屏幕像素密度
     * @return
     */
    static uint16_t dpi();

    /**
     * @brief 获取界面名称
     * @return
     */
    const char *name() const;
    /**
     * @brief 设置界面名称
     * @param name
     * @param copyStr 是否拷贝字符串
     */
    void setName(const char *name);

    bool isClearAfterHide() const;
    void setClearAfterHide(bool isClearAfterHide);

    /**
     * @brief 清除屏幕界面的数据,但是不删除屏幕本身
     */
    void cleanScreen();

    /**
     * @brief 获取已用内存
     * @return
     */
    static int32_t getUsedMemorySize();


   ////////////////// 通用图形组件 ///////////////////////////////

    /**
     * @brief 显示气泡消息
     * @param mesg 消息内容
     * @param period 默认停留显示3秒.-1表示一直显示
     */
    static void showBubble(const char * mesg , int32_t period = 3000);

    //TODO:添加中部图标提示

    /**
     * @brief 显示消息框
     * @param mesg 消息文本
     * @param buts 按钮文本
     * @param action 回调函数
     * @param period 显示的周期  -1表示不自动关闭
     */
    static void showMessageBox(const char * mesg , const char ** buts ,
                               const LVEventCallBack &callback , int32_t period = -1);

    static void messageBoxHide(){ messageBox()->setHidden(true); }

    /**
     * @brief 安装透明遮罩
     * 默认覆盖父对象的全部区域
     * @param parent 遮罩的父对象
     * @return 返回遮罩对象,由调用者负责遮罩的生命
     */
    static LVObject * setupMask(LVObject * parent);


protected:

    /**
     * @brief 事件信号处理函数
     * @param sign
     * @param param
     * @return
     */
    static LVResult signalCallBack(LVObject * obj, SignalType sign, void * param);

    /**
     * @brief 处理语言切换
     * @param param 参数
     */
    virtual void onLangChanged(void * param);

    /**
     * @brief 处理主题切换
     * @param param 参数
     */
    virtual void onThemeChanged(void * param);

    /**
     * @brief 处理屏幕变化
     * @param param 参数
     */
    virtual void onScreenChanged(void * param);

    /**
     * @brief 屏幕清理前
     */
    virtual void beforeCleanScreen();

    /**
     * @brief 屏幕清理后
     */
    virtual void afterCleanScreen();

    /**
     * @brief 初始化屏幕
     * 初始化屏幕显示和任务
     * @return
     */
    virtual bool setupScreen();

    /**
     * @brief 设置之前显示的屏幕
     * @param screen
     */
    static void setLastScreen(LVScreen * screen);

    /**
     * @brief 设置当前显示的屏幕
     * @param screen
     */
    static void setCurrScreen(LVScreen * screen);

    /**
     * @brief 开始屏幕任务
     */
    virtual void startScreenTask();

    /**
     * @brief 关闭屏幕任务
     */
    virtual void stopScreenTask();

    /**
     * @brief 注册任务
     */
    void loginTask(LVScreenTask * task);

    /**
     * @brief 注销任务
     */
    void logoutTask(LVScreenTask *task);

    /**
     * @brief 清除任务列表
     */
    void cleanTaskList();

    /**
     * @brief 设置屏幕初始化标识
     * @param value
     */
    void setInited(bool value);
};

#endif // LVSCREEN_H
