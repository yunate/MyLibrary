#pragma once
#include "IRegistAdapt.h"

class SimpleRegistStyle :
    public IRegistAdapt
{
public:
    SimpleRegistStyle();
    virtual ~SimpleRegistStyle();

private:
    // ���еĴ�����ʽ�����ֻ��Ϊ��˵�����⣬ʵ���Ϻ�WndRegister�е�һ��-.-
    virtual void _Init(WNDCLASSEX& wndClass, HINSTANCE hIns);
};

