#pragma once

#include "CommonHead.h"

class IRegistAdapt
{
public:
    IRegistAdapt();
    virtual ~IRegistAdapt();

    /*
        ������ע�ắ��
    */
    bool Regist();

    /*
        ж�ش�����
    */
    void UnRegist();

    void SetWndProc(WNDPROC    WndProc);
    void SetClassName(TString sClassName);
    void SetIns(HINSTANCE hIns);

private:
    /*
        Ĭ�ϴ��ڵ���ʽ
    */
    virtual void _Init(WNDCLASSEX& wndClass, HINSTANCE hIns);

private:
    TString        _sClassName;
    HINSTANCE    _hIns;
    WNDPROC        _WndProc;
};

