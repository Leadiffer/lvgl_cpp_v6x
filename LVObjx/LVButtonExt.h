#ifndef LVBUTTONEXT_H
#define LVBUTTONEXT_H

#include <LVCore/LVPointer.h>
#include <LVObjx/LVButton.h>
#include <LVObjx/LVLabel.h>
#include <LVObjx/LVImage.h>

/**
 * @brief The LVButtonExt class 增强版按钮控件
 * 可以直接设置图像和按钮文字,省去额外生成图像和标签控件的必要
 */
class LVButtonExt
        : public LVButton
{
    LV_MEMORY

public:

    /**
     * @brief 排版类型
     */
    enum Pattern
    {
        IconOnly,       //!< 只显示图标
        TextOnly,       //!< 只显示文字
        TextUnderIcon,  //!< 文字在图标下方
        IconText,       //!< 文字在图标右侧
        TextIcon        //!< 图标在文字右侧
    };

protected:

    Pattern m_pattern; //!< 排版类型
    LVPointer<LVImage> m_icon; //!< 图像控件
    LVPointer<LVLabel> m_text; //!< 文字控件

public:

    LVButtonExt(LVObject * par = nullptr, const LVButtonExt * copy = nullptr);

    LVButtonExt(const char * text, const void * icon = nullptr, Pattern composing = TextUnderIcon,
                LVObject * par = nullptr, const LVButtonExt *copy = nullptr);

    /**
     * @brief get Icon Widget
     * @return
     */
    LVImage * getIconWidget();

    /**
     * @brief get Text Widget
     * @return
     */
    LVLabel * getTextWidget();

    /**
     * @brief get Icon Src
     * @return
     */
    const void* getIcon();

    /**
     * @brief set Icon
     * @param icon
     */
    void setIcon(const void* icon);

    /**
     * @brief get text
     * @return
     */
    char* getText();

    /**
     * @brief set Text
     * @param text
     */
    void setText(const char* text);

    /**
     * @brief 获取排版类型
     * @return
     */
    Pattern getPattern() const;

    /**
     * @brief 设置排版类型
     * @param composing
     */
    void setPattern(const Pattern &pattern);

    /**
     * @brief 更新图像和文本的排版布局
     */
    void updatePattern();
};

#endif // LVBUTTONEXT_H
