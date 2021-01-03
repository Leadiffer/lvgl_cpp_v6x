#include "LVButtonExt.h"

LVButtonExt::LVButtonExt(LVObject *par, const LVButtonExt *copy)
    :LVButton(par,copy)
    ,m_icon(true)
    ,m_text(true)
{
    //复制属性
    if(copy)
    {
        m_pattern = copy->m_pattern;
        if(copy->m_icon) setIcon(copy->m_icon->getSrc());
        if(copy->m_text) setText(copy->m_text->getText());
    }
    else
    {
        m_pattern = COL_TextIcon;
    }
}

LVButtonExt::LVButtonExt(const char *text, const void *icon , Pattern composing ,
                         LVObject *par, const LVButtonExt *copy)
    :LVButtonExt(par,copy)
{
    if(icon) setIcon(icon);
    if(text) setText(text);
    setPattern(composing);
}

LVImage *LVButtonExt::getIconWidget()
{
    return m_icon;
}

LVLabel *LVButtonExt::getTextWidget()
{
    return m_text;
}

const void *LVButtonExt::getIcon()
{
    return m_icon?m_icon->getSrc():nullptr;
}

void LVButtonExt::setIcon(const void *icon)
{
    if(!m_icon)
        m_icon.reset(new LVImage(this));
    m_icon->setSrc(icon);
    updatePattern();
}

char *LVButtonExt::getText()
{
    return m_text?m_text->getText():nullptr;
}

void LVButtonExt::setText(const char *text)
{
    if(!m_text)
    {
        m_text.reset(new LVLabel(this));
        m_text->setAlign(LVLabel::ALIGN_CENTER);
    }
    m_text->setText(text);
    updatePattern();
}

LVButtonExt::Pattern LVButtonExt::getPattern() const
{
    return m_pattern;
}

void LVButtonExt::setPattern(const Pattern &pattern)
{
    if(m_pattern != pattern)
    {
        m_pattern = pattern;
        updatePattern();
    }
}

void LVButtonExt::updatePattern()
{
    switch (m_pattern)
    {
    case IconOnly       :
        if(m_text) m_text->setHidden(true);
        setLayout(LVLayouts::LAYOUT_CENTER);
        break;
    case TextOnly       :
        if(m_icon) m_icon->setHidden(true);
        setLayout(LVLayouts::LAYOUT_CENTER);
        break;
    case COL_TextIcon  :
        if(m_icon) m_icon->setHidden(false);
        if(m_text) m_text->setHidden(false);
        if(m_icon) m_icon->moveForeground();
        setLayout(LVLayouts::LAYOUT_COL_M);
        break;
    case COL_IconText  :
        if(m_icon) m_icon->setHidden(false);
        if(m_text) m_text->setHidden(false);
        if(m_text) m_text->moveForeground();
        setLayout(LVLayouts::LAYOUT_COL_M);
        break;
    case ROW_IconText :
        if(m_icon) m_icon->setHidden(false);
        if(m_text) m_text->setHidden(false);
        if(m_text) m_text->moveForeground();
        setLayout(LVLayouts::LAYOUT_ROW_M);
        break;
    case ROW_TextIcon :
        if(m_icon) m_icon->setHidden(false);
        if(m_text) m_text->setHidden(false);
        if(m_icon) m_icon->moveForeground();
        setLayout(LVLayouts::LAYOUT_ROW_M);
        break;
    default:break;
    }
}
