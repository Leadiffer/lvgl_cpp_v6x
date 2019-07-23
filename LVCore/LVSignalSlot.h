#ifndef LVSIGNALSLOT_H
#define LVSIGNALSLOT_H

#include <functional>
#include <LVMisc/LVLinklist.h>
#include <LVMisc/LVMemory.h>

class LVSignal;
class LVSlot;
class LVConnection;

/**
 *  槽对象列表
 */
using LVSlotList = LVLinkList<LVConnection*>;

/**
 *  信号对象列表
 */
using LVSignalList = LVLinkList<LVConnection*>;


/**
 * LVSignal 在链表中的节点对象
 */
using SignalNode = LVLLNode<LVSignal*>;

/**
 * LVSlot 在链表中的节点对象
 */
using SlotNode = LVLLNode<LVSlot*>;

/**
 * Connection 在链表中的节点对象
 */
using ConnectionNode = LVLLNode<LVConnection*>;

/**
 * 定义事件处理器
 * 可以是全局函数
 * 可以是成员函数
 * 可以是拉姆达表达式
 */
using SlotFunc = std::function<void(LVSignal*)>;

/**
 * @brief 代表一个信号与槽的连接
 */
class LVConnection
{
    LV_MEMORY
public:
    enum ConnectType : uint8_t
    {
        DirectConnect, //直接连接 立即调用槽对象
        QueueConnect, //队列连接 等待下次系统空闲时再来执行槽对象
    };

    friend class LVSignal;
    friend class LVSlot;
    friend LVConnection * connect(LVSignal *signal, LVSlot *slot, ConnectType type);
    friend LVConnection * connect(LVSignal *signal0, LVSignal *signal1, ConnectType type);

protected:
    ConnectType m_type; //!< 连接的类型
    LVSignal * m_signal0 = nullptr; //!< 信号1
    LVSignal * m_signal1 = nullptr; //!< 信号2
    LVSlot * m_slot = nullptr; //!< 槽
public:
    virtual ~LVConnection();
protected:

    LVConnection(LVSignal * signal,LVSlot * slot,ConnectType type);

    LVConnection(LVSignal * signal0,LVSignal * signal1,ConnectType type);

    /**
     * @brief 执行这个连接,等效于执行连接的槽函数
     */
    void operator()();

    /**
     * @brief 检测信号是否是发送者
     * 如果是两个信号连接需要确定发送者和接收者
     * @param signal
     * @return
     */
    bool isSender(LVSignal * signal)
    {
        if(!signal) return false;
        return m_signal0 == signal;
    }

    bool isReceiver(LVSignal * signal)
    {
        if(!signal) return false;
        return m_signal1 == signal;
    }

    bool isSignalSlotConnect()
    {
        return  m_signal0 && m_slot;
    }

    bool isSignalSignalConnect()
    {
        return  m_signal0 && m_signal1;
    }

    bool isvaild()
    {
        return (m_signal0 && m_slot) || (m_signal0 && m_signal1);
    }
};


LVConnection *connect(LVSignal * signal,LVSlot * slot,LVConnection::ConnectType type = LVConnection::DirectConnect);
LVConnection *connect(LVSignal * signal0,LVSignal * signal1,LVConnection::ConnectType type = LVConnection::DirectConnect);

void disConnect(LVSignal * signal,LVSlot * slot);
void disConnect(LVSignal * signal0,LVSignal * signal1);

void disConnectAll(LVSignal * signal);
void disConnectAll(LVSlot * slot);


/**
 * @brief 信号对象
 * 代表一种信号,
 * 能够被传播
 * 能够被关联
 * 能够被断开
 * 能够被控制
 */
class LVSignal
{
    LV_MEMORY

    friend class LVConnection;
    friend class LVSlot;
protected:
    void * m_param = nullptr; //!< 信号的参数(一个对象指针)
    LVSlotList m_slotList; //!<与信号关联的槽对象列表
public:
    LVSignal()
        :m_slotList(sizeof (LVConnection*))
    {}

    virtual ~LVSignal()
    {
        disConnectAll();
    }

    LVConnection *  connect(LVSignal * signal,LVConnection::ConnectType type = LVConnection::DirectConnect)
    {
        return ::connect(this,signal,type);
    }
    LVConnection *  connect(LVSlot * slot,LVConnection::ConnectType type = LVConnection::DirectConnect)
    {
        return ::connect(this,slot,type);
    }
    void disConnect(LVSlot * slot);
    void disConnect(LVSignal * signal);
    void disConnectAll();

    void emit(void * param = nullptr);

    void operator()(LVSignal * signal = nullptr)
    {
        (void)(signal);
        emit();
    }

    void * param()
    {
        return m_param;
    }

    bool isConnected()
    {
        return m_slotList.getHead() != nullptr;
    }

    bool isConnectedBy(LVSignal * signal);

    bool isConnectedTo(LVSignal * signal);

    bool isConnectedTo(LVSlot * slot);

protected:

    void setParam(void * param);

    void addConnection(LVConnection * connect);

    void removeConnection(LVConnection * connection);
};

/**
 * @brief 槽对象
 * 代表信号的处理器
 * 能够被传播
 * 能够被关联
 * 能够被断开
 */
class LVSlot
{
    LV_MEMORY

    friend class LVConnection;
    friend class LVSignal;
protected:
    LVSignalList m_signalList; //!<关联的信号列表
    SlotFunc m_slotFunc; //!< 具体执行的槽函数
public:
    LVSlot(SlotFunc slotFunc = SlotFunc())
        :m_signalList(sizeof (LVConnection*))
    {
        setSlotFunc(slotFunc);
    }

    ~LVSlot()
    {
        disConnectAll();
    }

    void setSlotFunc(SlotFunc slotFunc)
    {
        m_slotFunc = slotFunc;
    }

    LVConnection * connect(LVSignal * signal,LVConnection::ConnectType type = LVConnection::DirectConnect)
    {
        return ::connect(signal,this,type);
    }

    void disConnect(LVSignal * signal)
    {
        ::disConnect(signal,this);
    }

    void disConnectAll();

    void operator()(LVSignal * signal)
    {
    	if(m_slotFunc != nullptr)
    		m_slotFunc(signal);
    }

    bool isConnected()
    {
        return m_signalList.getHead() != nullptr;
    }

    bool isConnectedBy(LVSignal * signal);

protected:
    void addConnection(LVConnection * connect);

    void removeConnection(LVConnection * connection);
};


#endif // LVSIGNALSLOT_H


