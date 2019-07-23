/**
 * @file lv_ll.c
 * Handle linked lists. The nodes are dynamically allocated by the 'lv_mem' module.
 */

#ifndef LVLINKLIST_H
#define LVLINKLIST_H


/*********************
 *      INCLUDES
 *********************/
#include <lv_misc/lv_ll.h>
#include "LVMemory.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

template<class T>
class LVLinkList;

/*Dummy type to make handling easier*/
/**
 * @brief 链表节点的元数据
 * 记录双向链表节点的前后关系
 *
 * NOTE:一定要放在派生类继承数据结构后,
 * 例如:
 * class LVTask : public lv_task_t , public LVLLNodeMeta , public LVTaskEnhance
 * class LVObject : public lv_obj_t , public LVLLNodeMeta
 */
struct LVLLNodeMeta
{
    lv_ll_node_t * _Prev; //!< 前一个节点指针
    lv_ll_node_t * _Next; //!< 后一个节点指针
};

/**
 * @brief 链表的节点类型
 * 无法实例化,只能由链表获取,或者强制类型转换得到
 * 无法析构掉,只能由链表删除清理
 * T 类型会被4字节对齐
 */
template<class T = lv_ll_node_t>
class LVLLNode
{
    LV_MEMORY
private:
    LVLLNode() {}
public:

    ~LVLLNode() {}

    T m_nodeData; //!< 节点数据
    LVLLNodeMeta m_nodeMeta; //!< 节点元信息

//    T& operator->(){ return m_nodeData; }
//    const T& operator->() const { return m_nodeData; }

    //TODO:这里的操作需要区分类类型 基本类型 指针类型
    operator T(){ return m_nodeData; }

    /**
     * @brief 节点数据
     * @return
     */
    T & data() { return m_nodeData; }
    const T & data() const { return m_nodeData; }

    //设置节点数据
    void setData(const T& t){ m_nodeData = t; }

    /**
     * @brief 从链表中移除这个节点,并删除这个节点数据,归还内存
     * @param lv_ll_p
     */
    void deleteFromLVLL(const LVLinkList<T> * lv_ll_p);

    /**
     * @brief 从链表中移除这个节点,数据依旧占用存在
     * @param lv_ll_p
     */
    void removeFromLVLL(const LVLinkList<T> * lv_ll_p);

    /**
     * @brief 获取这个节点的前一个节点
     * @return
     */
    LVLLNode<T> * getPrevNode(){ return (LVLLNode<T>*)m_nodeMeta._Prev; }

    /**
     * @brief 获取这个节点的后一个节点
     * @return
     */
    LVLLNode<T> * getNextNode(){ return (LVLLNode<T>*)m_nodeMeta._Next; }

} __attribute__((aligned(4))); //4字节对其


/*Description of a linked list*/


/**
 * @brief 链表类型
 *
 * 链表中每个节点的实际大小计算如下:
 *  每个节点的的实际内存分配情况
 * { [ LVMemoryHeader(4) ] [ T(*4) ] [ LVLLNodeMeta(4+4)] }
 *
 * nodeSize = sizeof()
 *
 */
template<class T = lv_ll_node_t>
class LVLinkList : public lv_ll_t
{
    LV_MEMORY

protected:
   LVLinkList(){}

public:

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Initialize linked list
     * @param ll_dsc pointer to ll_dsc variable
     * @param node_size the size of 1 node in bytes
     */
    LVLinkList(uint32_t node_size = sizeof(T))
    {
        //NOTE: node_size会根据4字节对齐而调整
       lv_ll_init(this , node_size);
    }

    LVLinkList * fromLVll(lv_ll_t * ll)
    {
        return (LVLinkList<T> *)ll;
    }

    /**
     * Add a new head to a linked list
     * @param ll_p pointer to linked list
     * @return pointer to the new head
     */
    LVLLNode<T> * insertHead()
    {
        return (LVLLNode<T>*)lv_ll_ins_head(this);
    }

    /**
     * Insert a new node in front of the n_act node
     * @param ll_p pointer to linked list
     * @param n_act pointer a node
     * @return pointer to the new head
     */
    LVLLNode<T> * insertPrev(T * n_act)
    {
        return (LVLLNode<T>*)lv_ll_ins_prev(this,n_act);
    }

    LVLLNode<T> * insertPrev(LVLLNode<T> * n_act)
    {
        return (LVLLNode<T>*)lv_ll_ins_prev(this,n_act);
    }

    /**
     * Add a new tail to a linked list
     * @param ll_p pointer to linked list
     * @return pointer to the new tail
     */
    LVLLNode<T> * insertTail()
    {
        return (LVLLNode<T>*)lv_ll_ins_tail(this);
    }

    /**
     * Remove the node 'node_p' from 'll_p' linked list.
     * It does not free the the memory of node.
     * @param ll_p pointer to the linked list of 'node_p'
     * @param node_p pointer to node in 'll_p' linked list
     */
    void remove(T * node_p)
    {
        lv_ll_rem(this, node_p);
    }

    void remove(LVLLNode<T> * node_p)
    {
        lv_ll_rem(this, node_p);
    }

    /**
     * Remove and free all elements from a linked list. The list remain valid but become empty.
     * @param ll_p pointer to linked list
     */
    void clear()
    {
        lv_ll_clear(this);
    }

    /**
     * Move a node to a new linked list
     * @param ll_ori_p pointer to the original (old) linked list
     * @param ll_new_p pointer to the new linked list
     * @param node pointer to a node
     * @param head true: be the head in the new list
     *             false be the head in the new list
     */
    void changeList(LVLinkList<T> * ll_new_p, T * node, bool head)
    {
        lv_ll_chg_list(this,ll_new_p, node, head);
    }

    void changeList(LVLinkList<T> * ll_new_p, LVLLNode<T> * node, bool head)
    {
        lv_ll_chg_list(this,ll_new_p, node, head);
    }

    /**
     * Return with head node of the linked list
     * @param ll_p pointer to linked list
     * @return pointer to the head of 'll_p'
     */
    LVLLNode<T> * getHead() const
    {
        return (LVLLNode<T>*)lv_ll_get_head(this);
    }

    /**
     * Return with tail node of the linked list
     * @param ll_p pointer to linked list
     * @return pointer to the head of 'll_p'
     */
    LVLLNode<T> * getTail() const
    {
        return (LVLLNode<T>*)lv_ll_get_tail(this);
    }

    /**
     * Return with the pointer of the next node after 'n_act'
     * @param ll_p pointer to linked list
     * @param n_act pointer a node
     * @return pointer to the next node
     */
    LVLLNode<T> * getNext(const T * n_act) const
    {
        return (LVLLNode<T>*)lv_ll_get_next(this,n_act);
    }

    LVLLNode<T> * getNext(const LVLLNode<T> * n_act) const
    {
        return (LVLLNode<T>*)lv_ll_get_next(this,n_act);
    }

    /**
     * Return with the pointer of the previous node after 'n_act'
     * @param ll_p pointer to linked list
     * @param n_act pointer a node
     * @return pointer to the previous node
     */
    LVLLNode<T> * getPrev(const T * n_act) const
    {
        return (LVLLNode<T>*)lv_ll_get_prev(this,n_act);
    }

    LVLLNode<T> * getPrev(const LVLLNode<T> * n_act) const
    {
        return (LVLLNode<T>*)lv_ll_get_prev(this,n_act);
    }

    /**
     * Return the length of the linked list.
     * @param ll_p pointer to linked list
     * @return length of the linked list
     */
    uint32_t getLength() const
    {
        return lv_ll_get_len(this);
    }

    /**
     * Move a node before an other node in the same linked list
     * @param ll_p pointer to a linked list
     * @param n_act pointer to node to move
     * @param n_after pointer to a node which should be after `n_act`
     */
    void moveBefore(T * n_act, T * n_after)
    {
        lv_ll_move_before(this, n_act, n_after);
    }

    void moveBefore(LVLLNode<T> * n_act, LVLLNode<T> * n_after)
    {
        lv_ll_move_before(this, n_act, n_after);
    }

    /**
     * Check if a linked list is empty
     * @param ll_p pointer to a linked list
     * @return true: the linked list is empty; false: not empty
     */
    bool isEmpty() const
    {
        return lv_ll_is_empty(this);
    }

    /*******************
     *     ENHANCE
     *******************/

    //TODO:模仿QList的接口
    //TODO: 实现迭代器


};



template<class T>
void LVLLNode<T>::deleteFromLVLL(const LVLinkList<T> *lv_ll_p){ lv_ll_p->remove(this); delete this; }

template<class T>
void LVLLNode<T>::removeFromLVLL(const LVLinkList<T> *lv_ll_p){ lv_ll_p->remove(this); }


/**********************
 *      MACROS
 **********************/



#endif


