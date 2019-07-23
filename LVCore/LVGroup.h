/**
 * @file lv_group.h
 *
 */

#ifndef LVGROUP_H
#define LVGROUP_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_core/lv_group.h>
#include "LVObject.h"
#include "LVCallBack.h"
#include "../LVMisc/LVMemory.h"

/*********************
 *      DEFINES
 *********************/
/*Predefined keys to control the focused object via lv_group_send(group, c)*/
/*For compatibility in signal function define the keys regardless to `LV_USE_GROUP`*/

enum class LVKey : lv_key_t
{
    UP        = LV_KEY_UP        , /*0x11*/
    DOWN      = LV_KEY_DOWN      , /*0x12*/
    RIGHT     = LV_KEY_RIGHT     , /*0x13*/
    LEFT      = LV_KEY_LEFT      , /*0x14*/
    ESC       = LV_KEY_ESC       , /*0x1B*/
    DEL       = LV_KEY_DEL       , /*0x7F*/
    BACKSPACE = LV_KEY_BACKSPACE , /*0x08*/
    ENTER     = LV_KEY_ENTER     , /*0x0A, '\n'*/
    NEXT      = LV_KEY_NEXT      , /*0x09, '\t'*/
    PREV      = LV_KEY_PREV      , /*0x0B, '*/
    HOME      = LV_KEY_HOME      , /*0x02, STX*/
    END       = LV_KEY_END       , /*0x03, ETX*/
};

#if LV_USE_GROUP != 0
/**********************
 *      TYPEDEFS
 **********************/
class LVGroup;

using LVGroupStyleModifCallBack = LVCallBack<void(LVGroup *, LVStyle *),void>;
using LVGroupFocusCallBack = LVCallBack<void(LVGroup *),void>;

using LVGroupUserData = lv_group_user_data_t;

/**
 * Groups can be used to logically hold objects so that they can be individually focused.
 * They are NOT for laying out objects on a screen (try `lv_cont` for that).
 */
class LVGroup : public lv_group_t
{
    LV_MEMORY

    enum RefocusPolicy : lv_group_refocus_policy_t
    {
        NEXT = LV_GROUP_REFOCUS_POLICY_NEXT,
        PREV = LV_GROUP_REFOCUS_POLICY_PREV
    };

public:
    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Init. the group module
     * @remarks Internal function, do not call directly.
     */
    static void init(void)
    {
        return lv_group_init();
    }

    /**
     * Create a new object group
     * @return pointer to the new object group
     */
    LVGroup()
    {
        LVMemory::placementAlloc(this);
        lv_group_create();
        LVMemory::resetPlacementAlloc();
    }

    /**
     * Delete a group object
     * @param group pointer to a group
     */
    ~LVGroup()
    {
        lv_group_del(this);
    }


    /**
     * Add an object to a group
     * @param group pointer to a group
     * @param obj pointer to an object to add
     */
    void addObject(LVObject * obj)
    {
        lv_group_add_obj(this,obj);
    }

    /**
     * Remove an object from its group
     * @param obj pointer to an object to remove
     */
    static void removeObject(LVObject * obj)
    {
        lv_group_remove_obj(obj);
    }

    /**
     * Remove all objects from a group
     * @param group pointer to a group
     */
    void removeAllObjects()
    {
        lv_group_remove_all_objs(this);
    }

    /**
     * Focus on an object (defocus the current)
     * @param obj pointer to an object to focus on
     */
    static void focusObject(LVObject * obj)
    {
        lv_group_focus_obj(obj);
    }

    /**
     * Focus the next object in a group (defocus the current)
     * @param group pointer to a group
     */
    void focusNext()
    {
        lv_group_focus_next(this);
    }

    /**
     * Focus the previous object in a group (defocus the current)
     * @param group pointer to a group
     */
    void focusPrev()
    {
        lv_group_focus_prev(this);
    }

    /**
     * Do not let to change the focus from the current object
     * @param group pointer to a group
     * @param en true: freeze, false: release freezing (normal mode)
     */
    void focusFreeze(bool en)
    {
        lv_group_focus_freeze(this,en);
    }

    /**
     * Send a control character to the focuses object of a group
     * @param group pointer to a group
     * @param c a character (use LV_KEY_.. to navigate)
     * @return result of focused object in group.
     */
    lv_res_t sendData(uint32_t c)
    {
        return lv_group_send_data(this,c);
    }

    /**
     * Set a function for a group which will modify the object's style if it is in focus
     * @param group pointer to a group
     * @param style_mod_cb the style modifier function pointer
     */
    void setStyleModifCallBack(const LVGroupStyleModifCallBack& style_mod_cb)
    {
        m_styleModCb = style_mod_cb;
        lv_group_set_style_mod_cb(this,(lv_group_style_mod_cb_t)lvGroupStyleModifCallBackAgent);
    }

    /**
     * Set a function for a group which will modify the object's style if it is in focus in edit mode
     * @param group pointer to a group
     * @param style_mod_edit_cb the style modifier function pointer
     */
    void setStyleModifEditCallBack(const LVGroupStyleModifCallBack& style_mod_edit_cb)
    {
        m_styleModEditCb = style_mod_edit_cb;
        lv_group_set_style_mod_edit_cb(this,(lv_group_style_mod_cb_t)lvGroupStyleModifEditCallBackAgent);
    }

    /**
     * Set a function for a group which will be called when a new object is focused
     * @param group pointer to a group
     * @param focus_cb the call back function or NULL if unused
     */
    void setFocusCallBack(const LVGroupFocusCallBack& focus_cb)
    {
        m_focusCb = focus_cb;
        lv_group_set_focus_cb(this,(lv_group_focus_cb_t)lvGroupFocusCallBackAgent);
    }

    /**
     * Set whether the next or previous item in a group is focused if the currently focussed obj is
     * deleted.
     * @param group pointer to a group
     * @param new refocus policy enum
     */
    void setRefocusPolicy(RefocusPolicy policy)
    {
        lv_group_set_refocus_policy(this,policy);
    }

    /**
     * Manually set the current mode (edit or navigate).
     * @param group pointer to group
     * @param edit: true: edit mode; false: navigate mode
     */
    void setEditing(bool edit)
    {
        lv_group_set_editing(this,edit);
    }

    /**
     * Set the `click_focus` attribute. If enabled then the object will be focused then it is clicked.
     * @param group pointer to group
     * @param en: true: enable `click_focus`
     */
    void setClickFocus(bool en)
    {
        lv_group_set_click_focus(this,en);
    }

    /**
     * Set whether focus next/prev will allow wrapping from first->last or last->first object.
     * @param group pointer to group
     * @param en: true: wrapping enabled; false: wrapping disabled
     */
    void setWrap(bool en)
    {
        lv_group_set_wrap(this,en);
    }

    /**
     * Modify a style with the set 'style_mod' function. The input style remains unchanged.
     * @param group pointer to group
     * @param style pointer to a style to modify
     * @return a copy of the input style but modified with the 'style_mod' function
     */
    LVStyle * modifStyle(const LVStyle * style)
    {
        return (LVStyle *)lv_group_mod_style(this,style);
    }

    /**
     * Get the focused object or NULL if there isn't one
     * @param group pointer to a group
     * @return pointer to the focused object
     */
    LVObject * getFocused()
    {
        return (LVObject *)lv_group_get_focused(this);
    }

    #if LV_USE_USER_DATA
    /**
     * Get a pointer to the group's user data
     * @param group pointer to an group
     * @return pointer to the user data
     */
    LVGroupUserData * getUserData()
    {
        return lv_group_get_user_data(this);
    }

    #endif

    /**
     * Get a the style modifier function of a group
     * @param group pointer to a group
     * @return pointer to the style modifier function
     */
    LVGroupStyleModifCallBack getStyleModfiCallBack()
    {
        return m_styleModCb;
    }

    /**
     * Get a the style modifier function of a group in edit mode
     * @param group pointer to a group
     * @return pointer to the style modifier function
     */
    const LVGroupStyleModifCallBack & getStyleModifEditCallBack() const
    {
        return m_styleModEditCb;
    }

    /**
     * Get the focus callback function of a group
     * @param group pointer to a group
     * @return the call back function or NULL if not set
     */
    const LVGroupFocusCallBack & getFocusCallBack() const
    {
        return m_focusCb;
    }

    /**
     * Get the current mode (edit or navigate).
     * @param group pointer to group
     * @return true: edit mode; false: navigate mode
     */
    bool getEditing()
    {
        return lv_group_get_editing(this);
    }

    /**
     * Get the `click_focus` attribute.
     * @param group pointer to group
     * @return true: `click_focus` is enabled; false: disabled
     */
    bool getClickFocus()
    {
        return lv_group_get_click_focus(this);
    }

    /**
     * Get whether focus next/prev will allow wrapping from first->last or last->first object.
     * @param group pointer to group
     * @param en: true: wrapping enabled; false: wrapping disabled
     */
    bool getWrap()
    {
        return lv_group_get_wrap(this);
    }

    /**
     * Notify the group that current theme changed and style modification callbacks need to be
     * refreshed.
     * @param group pointer to group. If NULL then all groups are notified.
     */
    void reportStyleModifed()
    {
        return lv_group_report_style_mod(this);
    }

    /*******************
     *     ENHANCE
     *******************/

    LVGroupStyleModifCallBack m_styleModCb;      /**< A function to modifies the style of the focused object*/
    LVGroupStyleModifCallBack m_styleModEditCb; /**< A function which modifies the style of the edited object*/
    LVGroupFocusCallBack m_focusCb;              /**< A function to call when a new object is focused (optional)*/

    static void lvGroupStyleModifCallBackAgent(lv_group_t * group, lv_style_t * style)
    {
        LVGroup * lvGroup = (LVGroup*)group;
        if(lvGroup && lvGroup->m_styleModCb)
            lvGroup->m_styleModCb((LVGroup*)group,(LVStyle*)style);
    }

    static void lvGroupStyleModifEditCallBackAgent(lv_group_t * group, lv_style_t * style)
    {
        LVGroup * lvGroup = (LVGroup*)group;
        if(lvGroup && lvGroup->m_styleModEditCb)
            lvGroup->m_styleModEditCb((LVGroup*)group,(LVStyle*)style);
    }

    static void lvGroupFocusCallBackAgent(lv_group_t * group)
    {
        LVGroup * lvGroup = (LVGroup*)group;
        if(lvGroup && lvGroup->m_focusCb)
            lvGroup->m_focusCb(lvGroup);
    }
};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_GROUP != 0*/

#endif /*LV_GROUP_H*/
