#include "LVScreen.h"
#include "LVScreenTask.h"
#include <LVObjx/LVBar.h>
#include <LVObjx/LVLabel.h>
#include <LVCore/LVStyle.h>
#include <LVObjx/LVMessageBox.h>
#include <LVCore/LVDispaly.h>

LVPointer<LVScreen> LVScreen::s_lastScreen;
LVPointer<LVScreen> LVScreen::s_currScreen;

//定义几组常用的按钮组
const char * btnMap_Close_S   [2] = {LV_SYMBOL_CLOSE, ""};
const char * btnMap_Ok_S      [2] = {LV_SYMBOL_OK, ""};
const char * btnMap_No_Yes_S  [3] = {LV_SYMBOL_CLOSE , LV_SYMBOL_OK, ""};
const char * btnMap_Ok_T      [2] = {"Ok", ""};
const char * btnMap_No_Yes_T  [3] = {"No", "Yes", ""};
const char * btnMap_No_Yes_ST [3] = {LV_SYMBOL_CLOSE " No", LV_SYMBOL_OK " Yes", ""};

void memory_monitor(void * param);

bool LVScreen::isClearAfterHide() const
{
    return m_clearAfterHide;
}

void LVScreen::setClearAfterHide(bool clearAfterHide)
{
    m_clearAfterHide = clearAfterHide;
}

void LVScreen::cleanScreen()
{
    //memory_monitor(nullptr);

    //NOTE: 注意清理的先后顺序

    beforeCleanScreen();

    //清理屏幕任务
    cleanTaskList();

    //清理子对象
    cleanChildren();

    //触发子类清理动作
    afterCleanScreen();

    //重置初始化标识
    setInited(false);

    //整理内存碎片
    //lv_mem_defrag();

    lvInfo("Screen::cleanScreen()");

    //memory_monitor(nullptr);
}

int32_t LVScreen::getUsedMemorySize()
{
    static lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    return mon.total_size - mon.free_size;
}

void LVScreen::logUsedMemorySize(const char * tag)
{
    int32_t UsedMemory = getUsedMemorySize();
    char str[100];
    sprintf(str,"%s UsedMemory : %d Bytes!",tag, UsedMemory);
    lvWarn(str);
}


const char *LVScreen::name() const
{
    return m_name;
}

void LVScreen::setName(const char *name)
{
    m_name = (char*)LVMemory::reallocate(m_name,strlen(name)+1);
    strcpy(m_name,name);
}

LVBar * LVScreen::memoryDebuger()
{
    //用进度条指示内存状态
    static LVPointer<LVBar> barMem(true) ;
    static LVScopedPointer<LVTask> memTask ;
    //进度条样式
    static LVScopedPointer<LVStyle> styleProcessBar;
    static LVScopedPointer<LVStyle> styleProcessIndic;

    if(!styleProcessBar)
    {
        styleProcessBar.reset(new LVStyle(lv_style_plain));
        styleProcessBar->body.main_color = LV_COLOR_BLACK;
        styleProcessBar->body.grad_color = LV_COLOR_BLACK;
        styleProcessBar->body.radius = 0;
        styleProcessBar->body.border.width = 0;
        styleProcessBar->text.color = LV_COLOR_WHITE;
    }

    if(!styleProcessIndic)
    {
        styleProcessIndic.reset(new LVStyle(lv_style_plain));
        styleProcessIndic->body.main_color = LV_COLOR_GREEN;
        styleProcessIndic->body.grad_color = LV_COLOR_GREEN;
        styleProcessIndic->body.radius = 0;
        styleProcessIndic->body.border.width = 0;
        styleProcessIndic->body.padding.top = 0;
        styleProcessIndic->body.padding.bottom = 0;
        styleProcessIndic->body.padding.left = 0;
        styleProcessIndic->body.padding.right = 0;
        styleProcessIndic->body.padding.inner = 0;
        styleProcessIndic->text.color = LV_COLOR_WHITE;
    }

    if(!barMem)
    {
        barMem.reset(new LVBar(LVDisplay::getDefault()->getLayerSys(),nullptr));
        barMem->setStyle(styleProcessBar,LVBar::STYLE_BG);
        barMem->setStyle(styleProcessIndic,LVBar::STYLE_INDIC);
        barMem->setWidth(LVDisplay::getDefault()->getHorizontalResolution());
        barMem->setHeight(2);
        barMem->align(ALIGN_IN_TOP_LEFT);
    }

    if(!memTask)
    {
        memTask.reset(new LVTask([&](LVTask*){
            lv_mem_monitor_t mon;
            lv_mem_monitor(&mon);
            barMem->setValue(mon.used_pct,true);

            //切换警示色
            if(mon.used_pct <= 30)
            {
              styleProcessIndic->body.main_color = LV_COLOR_GREEN;
              styleProcessIndic->body.grad_color = LV_COLOR_GREEN;
            }
            else if(mon.used_pct <= 50)
            {
                styleProcessIndic->body.main_color = LV_COLOR_CYAN;
                styleProcessIndic->body.grad_color = LV_COLOR_CYAN;
            }
            else if(mon.used_pct <= 75)
            {
                styleProcessIndic->body.main_color = LV_COLOR_YELLOW;
                styleProcessIndic->body.grad_color = LV_COLOR_YELLOW;
            }
            else if(mon.used_pct <= 85)
            {
                styleProcessIndic->body.main_color = LV_COLOR_ORANGE;
                styleProcessIndic->body.grad_color = LV_COLOR_ORANGE;
            }
            else
            {
                styleProcessIndic->body.main_color = LV_COLOR_RED;
                styleProcessIndic->body.grad_color = LV_COLOR_RED;
            }
        },250));
        memTask->startAndRun();
    }

    //提示内存使用情况,检查内存泄露
    //char tempStr[16];
    //sprintf(tempStr,"Use:%dByte",screen->m_memoryUsed);
    //showBubble(tempStr,1000);

    return barMem;
}

LVLabel *LVScreen::bubble(bool create)
{
    static LVPointer<LVLabel> bubble(true);
    static LVScopedPointer<LVStyle> styleBubble;

    if(!styleBubble && create)
    {
        //NOTE:主题刷新时无法更新样式
        styleBubble.reset(new LVStyle());
        *styleBubble = lv_style_plain;
        //TODO:气泡的颜色应该跟着主题切换
        styleBubble->body.main_color = LV_COLOR_MAKE(0x17,0x28,0x45);
        styleBubble->body.grad_color = LV_COLOR_MAKE(0x17,0x28,0x45);
        styleBubble->text.color = LV_COLOR_WHITE;
        styleBubble->body.opa = 170; //增加透明效果
        styleBubble->body.padding.left = 8;
        styleBubble->body.padding.right = 8;
        styleBubble->body.padding.top = 6;
        styleBubble->body.padding.bottom = 4;
    }


    if(!bubble && create)
    {
        //气泡提示
        bubble.reset(new LVLabel(LVDisplay::getDefault()->getLayerTop(),nullptr));
        bubble->align(ALIGN_IN_TOP_MID);
        bubble->setAutoRealign(true);
        bubble->setBodyDraw(true);
        bubble->setHidden(true); //隐藏,需要时再显示
        bubble->setStyle(styleBubble);
    }

    return bubble;
}

void LVScreen::showBubble(const char *mesg, int32_t period)
{
    //BUG: 消息会闪跳

    static LVScopedPointer<LVTask> bubbleTask;
    if(!bubbleTask)
    {
        bubbleTask.reset(new LVTask(
        [&](LVTask*){
            bubble()->setHidden(true);
            bubbleTask->stop();
        },period));
    }

    auto * bubbleLab = bubble();
    bubbleLab->setText(mesg);
    bubbleLab->moveForeground(); //顶端显示
    bubbleLab->setHidden(false);

    //一会自动隐藏
    if(period>0)
        bubbleTask->start(period);
}

void LVScreen::showMessageBox(const char *mesg, const char **buts, const LVEventCallBack& callback, int32_t period, bool masked)
{
    static LVPointer<LVObject> mask(true);
    LVMessageBox * mbox = messageBox();

    //配置消息框遮罩
    if(masked && !mask)
    {
        mask.reset(setupMask(mbox->getParent()));

        mbox->setSignalCallBack([&](LVObject * obj, SignalType sign, void * param)->LVResult
        {
            //消息框关闭时,自动清理遮罩
            if(obj && mask && sign == SIGNAL_CLEANUP)
                delete mask.get();
            //消息框隐藏时,遮罩也隐藏
            else if(obj && mask && sign == SIGNAL_HIDDEN_CHG)
                mask->setHidden(obj->hidden);
            return (LVResult)(obj->ancestorSignalCB()(obj,sign,param));
        });
    }

    mbox->setText(mesg);
    mbox->addButtons(buts);
    mbox->setEventCallBack(callback);
    if(period!=-1)
        mbox->startAutoClose(period);
    else
        mbox->stopAutoClose();

    mbox->align(ALIGN_CENTER);
    mbox->setHidden(false);
    if(mask)
    {
        mask->setHidden(false);
        mbox->moveForeground();
    }
}

void LVScreen::hideMessageBox()
{
    if(messageBox(false))
        messageBox(false)->setHidden(true);
}

void LVScreen::deleteMessageBox()
{
    if(messageBox(false))
        delete messageBox(false);
}

LVMessageBox *LVScreen::messageBox(bool create)
{
    static LVPointer<LVMessageBox> mbox(true);
    if(!mbox && create)
    {
        mbox.reset(new LVMessageBox(LVDisplay::getDefault()->getLayerTop()));
        //增加消息框的宽度
        mbox->setWidth(LVDisplay::getDefault()->getHorizontalResolution() - 40);
        mbox->align(ALIGN_CENTER);
        mbox->setHidden(true);
    }
    return mbox;
}


LVObject * LVScreen::setupMask(LVObject *parent)
{
    static LVScopedPointer<LVStyle> maskStyle;
    if(!maskStyle)
    {
        //NOTE:切换主题时可能无法更新样式
        maskStyle.reset(new LVStyle());
        *maskStyle = lv_style_plain;
        maskStyle->body.opa = 200;
        maskStyle->body.main_color = LV_COLOR_GRAY;
        maskStyle->body.grad_color = LV_COLOR_GRAY;
    }

    LVObject * mask = new LVObject(parent);
    mask->setStyle(maskStyle);
    mask->setSizeFill();

    return mask;
}


LVScreen::LVScreen(const char *name, LVObject *parent)
    : LVObject(parent)
    ,m_taskList(sizeof (LVScreenTask *))
{
    setName(name);
    //设置事件处理函数
    setEventCallBack((void(*)(LVObject * obj, EventType event))LVScreen::signalCallBack);
    lvInfo("Screen::Screen() [%s]",m_name);
}

LVScreen::~LVScreen()
{
    //清理掉数据和任务
    cleanScreen();

    //清除自己在其他地方的记录
    if(LastScreen() == this)
        setLastScreen(nullptr);
    if(CurrScreen() == this)
        setCurrScreen(nullptr);
    lvInfo("Screen::~Screen() [%s]",m_name);

    //清理名字文本
    LVMemory::free(m_name);
}


LVResult LVScreen::signalCallBack(LVObject * obj, SignalType sign, void * param)
{
    LVScreen * screen = static_cast<LVScreen*>(obj);
    //处理事件,比如语言发生了变化
    uint8_t signal = sign;
    lv_res_t ret = RES_Invalid;
    if(screen)
    {
        ret = (*screen->ancestorSignalCB())(obj,sign,param);
        if(ret != RES_Invalid)
        {
            if(signal == SIGNAL_LANG_CHG) screen->onLangChanged(param);
            else if(signal == SIGNAL_STYLE_CHG) screen->onThemeChanged(param);
            else if(signal == SIGNAL_SCREEN_CHG) screen->onScreenChanged(param);
        }
    }
    return LVResult(ret);
}

void LVScreen::onLangChanged(void * /*param*/)
{
    //NOTE: 子类中完成处理语言切换时更新界面文本的操作
}

void LVScreen::onThemeChanged(void * /*param*/)
{
    //NOTE: 子类中完成处理主题切换时界面刷新
}

void LVScreen::onScreenChanged(void * /*param*/)
{
    //NOTE: 子类中完成处理屏幕大小方向变化时时界面刷新
}

void LVScreen::beforeCleanScreen()
{
    //NOTE: 子类中完成屏幕清理动作
}

void LVScreen::afterCleanScreen()
{
    //NOTE: 子类中完成屏幕清理动作
}

bool LVScreen::setupScreen()
{
    lvInfo("Screen::initScreen() empty function");
    return false;
}

bool LVScreen::show()
{
    bool ret = false;

    //如果存在其他的屏幕界面正在显示,需要先隐藏当前的界面
    if(CurrScreen())
    {
        if(!CurrScreen()->hide())
        {
            //界面未隐藏成功,当前界面无法显示
            return ret;
        }
    }

    if(beforeShow())
    {
        loadScreen();
        setCurrScreen(this);
        //开启相关任务
        startScreenTask();
        afterShow();
        ret = true;
    }

    return ret;
}

bool LVScreen::show(LVScreen *prev)
{
    setPrevScreen(prev);
    return show();
}

bool LVScreen::beforeShow()
{

    //初始化界面
    //将初始化放到这理执行,有助于减少内存占用情况
    //没有用到的界面就不会消耗内存了
    if(!m_inited)
    {
        //统计初始化屏幕用了多少内存
        //方便在屏幕清理的时候发现内存泄露
        //memory_monitor(nullptr);
        m_memoryUsed = getUsedMemorySize();
        m_inited = setupScreen();
        m_memoryUsed = getUsedMemorySize() - m_memoryUsed;
        //memory_monitor(nullptr);

        {
            char str[40];
            //警告内存有泄露
            sprintf(str,"Memory used : %d Bytes!", m_memoryUsed);
            lvWarn(str);
        }

        if(!m_inited)
            lvInfo("Screen::beforeShow() setupScreen false");
    }

    return true;
}

bool LVScreen::hide()
{
    bool ret = false;
    if(beforeHide())
    {
        //关闭相关任务
        stopScreenTask();

        setCurrScreen(nullptr);
        setLastScreen(this);

        //隐藏后清理屏幕
        if(isClearAfterHide())
        {
            int32_t memoryRecovery = getUsedMemorySize();
            cleanScreen();
            memoryRecovery = memoryRecovery - getUsedMemorySize();

            if(m_memoryUsed != memoryRecovery)
            {
                char str[40];
                //警告内存有泄露
                sprintf(str,"Memory leak deteted : %d Bytes!", m_memoryUsed - memoryRecovery);
                lvWarn(str);
            }
        }

        afterHide();

        //隐藏后删除屏幕
        if(isDeleteAfterHide())
        {
            setLastScreen(nullptr);
            delete this;
        }

        ret = true;
    }

    return ret;
}

LVScreen *LVScreen::currScreen()
{
    return s_currScreen;
}

bool LVScreen::hasCurrScreen()
{
    return s_currScreen != nullptr;
}

LVScreen *LVScreen::lastScreen()
{
    return s_lastScreen;
}

bool LVScreen::hasLastScreen()
{
    return s_lastScreen != nullptr && s_lastScreen.get() != s_currScreen.get();
}

LVScreen *LVScreen::prevScreen()
{
    return m_prevScreen;
}

bool LVScreen::hasPrevScreen()
{
    return m_prevScreen != nullptr;
}

void LVScreen::setPrevScreen(LVScreen *screen)
{
    m_prevScreen.reset(screen);
}

LVScreen *LVScreen::nextScreen()
{
    return m_nextScreen;
}

bool LVScreen::hasNextScreen()
{
    return m_nextScreen != nullptr;
}

void LVScreen::setNextScreen(LVScreen *screen)
{
    m_nextScreen.reset(screen);
}

bool LVScreen::isVisible()
{
    return lv_scr_act() == static_cast<lv_obj_t*>(this);
}

void LVScreen::setVisible(bool value)
{
    value ? show(): hide();
}

LVScreen *LVScreen::LastScreen()
{
    return s_lastScreen;
}

LVScreen *LVScreen::CurrScreen()
{
    return s_currScreen;
}

LVColor LVScreen::screenColor()
{
    return m_screenColor;
}

void LVScreen::setScreenColor(LVColor color)
{
    m_screenColor = color;

    //TODO: 完成屏幕颜色设置
}

bool LVScreen::isDeleteAfterHide()
{
    return m_deleteAfterHide;
}

void LVScreen::setDeleteAfterHide(bool value)
{
    m_deleteAfterHide = value;
}

uint16_t LVScreen::width()
{
    return LV_HOR_RES_MAX;
}

uint16_t LVScreen::height()
{
    return LV_VER_RES_MAX;
}

uint16_t LVScreen::dpi()
{
    return LV_DPI;
}

void LVScreen::setLastScreen(LVScreen *screen)
{
    s_lastScreen.reset(screen);
}

void LVScreen::setCurrScreen(LVScreen *screen)
{
    s_currScreen.reset(screen);
}

void LVScreen::startScreenTask()
{
    auto node = m_taskList.getHead();
    while (node)
    {
        LVScreenTask * task = node->data();
        task->onScreenShow();
        node = m_taskList.getNext(node);
    }
}

void LVScreen::stopScreenTask()
{
    auto node = m_taskList.getHead();
    while (node)
    {
        LVScreenTask * task = node->data();
        task->onScreenHide();
        node = m_taskList.getNext(node);
    }
}

void LVScreen::loginTask(LVScreenTask *task)
{
    if(task && !task->m_nodeId)
    {
        auto newNode =  m_taskList.insertTail();
        //保存节点指针
        task->m_nodeId = newNode;
        //保存任务指针
        newNode->data() = task;
    }
}

void LVScreen::logoutTask(LVScreenTask *task)
{
    if(task && task->m_nodeId)
    {
        m_taskList.remove(task->m_nodeId);
        task->m_screen = nullptr;
        task->m_nodeId = nullptr;
    }
}

void LVScreen::cleanTaskList()
{
    auto node = m_taskList.getHead();
    while (node)
    {
        LVScreenTask * task = node->data();
        task->m_nodeId = nullptr;
        task->m_screen = nullptr;
        delete task;
        node = m_taskList.getNext(node);
    }

    m_taskList.clear();
}

void LVScreen::setInited(bool value)
{
    m_inited = value;
}
