#include "i18n.h"

const char* _(const char* text)
{
    return text;
}

const char* _(const char* label,const char* text)
{
    (void)label;
    return text;
}
