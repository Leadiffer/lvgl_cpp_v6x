#ifndef I18N_H
#define I18N_H

/**
  * 多语言接口占位函数
  */

/**
 * @brief _
 * @param text 需要翻译的文本
 * @return
 */
const char* _(const char* text);

/**
 * @brief _
 * @param label 标签
 * @param text 需要翻译的文本
 * @return
 */
const char* _(const char* label,const char* text);

#endif // I18N_H
