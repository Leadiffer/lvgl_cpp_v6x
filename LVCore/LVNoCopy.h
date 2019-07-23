#ifndef LVNOCOPY_H
#define LVNOCOPY_H

class LVNoCopy
{
public:
    LVNoCopy() = default;    //使用合成的默认构造函数
    LVNoCopy(const LVNoCopy&) = delete;  //阻止拷贝
    LVNoCopy & operator = (const LVNoCopy&) = delete; //阻止赋值
    ~LVNoCopy() = default; //使用合成的析构函数
};

#endif // LVNOCOPY_H
