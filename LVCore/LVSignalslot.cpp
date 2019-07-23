#include "LVSignalSlot.h"
#include <LVMisc/LVTask.h>


LVConnection * connect(LVSignal *signal, LVSlot *slot, LVConnection::ConnectType type)
{
    return  new LVConnection(signal,slot,type);
}
LVConnection * connect(LVSignal *signal0, LVSignal *signal1, LVConnection::ConnectType type)
{
    return new LVConnection(signal0,signal1,type);
}

void disConnect(LVSignal *signal, LVSlot *slot)
{
    if(signal && slot)
    {
        signal->disConnect(slot);
    }

}
void disConnect(LVSignal *signal0, LVSignal *signal1)
{
    if(signal0 && signal1)
    {
        signal0->disConnect(signal1);
    }
}

void disConnectAll(LVSlot *slot)
{
    if(slot)
        slot->disConnectAll();
}
void disConnectAll(LVSignal *signal)
{
    if(signal)
        signal->disConnectAll();
}

LVConnection::~LVConnection()
{
    if(m_signal0)
        m_signal0->removeConnection(this);
    if(m_signal1)
        m_signal1->removeConnection(this);
    if(m_slot)
        m_slot->removeConnection(this);
}

LVConnection::LVConnection(LVSignal *signal, LVSlot *slot, ConnectType type)
    :m_type(type)
	,m_signal0(signal)
    ,m_slot(slot)
{
    if(isSignalSlotConnect())
    {
        m_signal0->addConnection(this);
        m_slot->addConnection(this);
    }
}

LVConnection::LVConnection(LVSignal *signal0, LVSignal *signal1, ConnectType type)
    :m_type(type)
    ,m_signal0(signal0)
    ,m_signal1(signal1)

{
    if(isSignalSignalConnect())
    {
        m_signal0->addConnection(this);
        m_signal1->addConnection(this);
    }
}

void LVConnection::operator()()
{
    if(isvaild())
    {
        if(isSignalSlotConnect())
        {
            if(m_type == DirectConnect)
                (*m_slot)(m_signal0);
            else if(m_type == QueueConnect)
                LVTask::once(1,[this](LVTask*){ (*m_slot)(m_signal0); }); //LVTaskCallBack::StdFunc(
        }
        else if(isSignalSignalConnect())
        {
            if(m_type == DirectConnect)
                (*m_signal1)(m_signal0);
            else if(m_type == QueueConnect)
                LVTask::once(1,[this](LVTask*){ (*m_signal1)(m_signal0); });//LVTaskCallBack::StdFunc(
        }
    }
}

void LVSignal::disConnect(LVSlot *slot)
{
    if(slot)
    {
        ConnectionNode * node = m_slotList.getHead();
        while (node)
        {
            LVConnection * connecttion = node->data();
            if(connecttion->m_slot == slot) //connecttion &&
            {
                connecttion->m_slot->removeConnection(connecttion);
                connecttion->m_slot = nullptr;
                connecttion->m_signal0 = nullptr;
                m_slotList.remove(node);
                delete connecttion;
                return;
            }
            //执行连接
            node = m_slotList.getNext(node);
        }
    }
}

void LVSignal::disConnect(LVSignal *signal)
{
    if(signal)
    {
        ConnectionNode * node = m_slotList.getHead();
        while (node)
        {
            LVConnection * connecttion = node->data();
            //if(connecttion)
            //{
                if(connecttion->m_signal1 == signal)
                {
                    connecttion->m_signal1->removeConnection(connecttion);
                    connecttion->m_signal1 = nullptr;
                    connecttion->m_signal0 = nullptr;
                    m_slotList.remove(node);
                    delete connecttion;
                }
                else if(connecttion->m_signal0 == signal)
                {
                    connecttion->m_signal0->removeConnection(connecttion);
                    connecttion->m_signal1 = nullptr;
                    connecttion->m_signal0 = nullptr;
                    m_slotList.remove(node);
                    delete connecttion;
                }
                return;
            //}
            //执行连接
            node = m_slotList.getNext(node);
        }
    }
}

void LVSignal::disConnectAll()
{
    ConnectionNode * node = m_slotList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        //if(connect)
        //{
            if(connect->isSignalSlotConnect())
            {
                connect->m_slot->removeConnection(connect);
                connect->m_signal0 = nullptr;
                connect->m_slot = nullptr;
            }
            else if(connect->isSignalSignalConnect())
            {
                if(connect->isSender(this))
                {
                    connect->m_signal1->removeConnection(connect);
                    connect->m_signal0 = nullptr;
                    connect->m_signal1 = nullptr;
                }
                else
                {
                    connect->m_signal0->removeConnection(connect);
                    connect->m_signal0 = nullptr;
                    connect->m_signal1 = nullptr;
                }
            }
            delete connect;
        //}
        node = m_slotList.getNext(node);
    }
    m_slotList.clear();
}

void LVSignal::emit(void * param)
{
    setParam(param);
    ConnectionNode * node = m_slotList.getHead();
    while (node)
    {
        LVConnection * connecttion = node->data();
        if(connecttion)
            //执行连接
            (*connecttion)();
        node = m_slotList.getNext(node);
    }
}

bool LVSignal::isConnectedBy(LVSignal *signal)
{
    ConnectionNode * node = m_slotList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(signal == connect->m_signal0 && this == connect->m_signal1 )
            return true;
        node = m_slotList.getNext(node);
    }
    return false;
}

bool LVSignal::isConnectedTo(LVSignal *signal)
{
    ConnectionNode * node = m_slotList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(signal == connect->m_signal1 && this == connect->m_signal0 )
            return true;
        node = m_slotList.getNext(node);
    }
    return false;
}

bool LVSignal::isConnectedTo(LVSlot *slot)
{
    ConnectionNode * node = m_slotList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(slot == connect->m_slot && this == connect->m_signal0)
            return true;
        node = m_slotList.getNext(node);
    }
    return false;
}

void LVSignal::setParam(void *param)
{
    m_param = param;
}

void LVSignal::addConnection(LVConnection *connect)
{
    ConnectionNode * newNode = m_slotList.insertTail();
    newNode->data() = connect;
}

void LVSignal::removeConnection(LVConnection *connection)
{
    ConnectionNode * node = m_slotList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(connect == connection)
        {
            m_slotList.remove(node);
            return;
        }
        node = m_slotList.getNext(node);
    }
}

void LVSlot::disConnectAll()
{
    ConnectionNode * node = m_signalList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(connect && connect->isSignalSlotConnect())
        {
            connect->m_signal0->removeConnection(connect);
            connect->m_signal0 = nullptr;
            connect->m_slot = nullptr;
            delete connect;
        }
        node = m_signalList.getNext(node);
    }
    m_signalList.clear();
}

bool LVSlot::isConnectedBy(LVSignal *signal)
{
    ConnectionNode * node = m_signalList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(signal == connect->m_signal0 && this == connect->m_slot)
            return true;
        node = m_signalList.getNext(node);
    }
    return false;
}

void LVSlot::addConnection(LVConnection *connect)
{
    ConnectionNode * newNode = m_signalList.insertTail();
    newNode->data() = connect;
}

void LVSlot::removeConnection(LVConnection *connection)
{
    ConnectionNode * node = m_signalList.getHead();
    while (node)
    {
        LVConnection * connect = node->data();
        if(connect == connection)
        {
            m_signalList.remove(node);
            return;
        }
        node = m_signalList.getNext(node);
    }
}
