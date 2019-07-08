#pragma once

#include "CommonHead.h"

class IRegistAdapt
{
public:
	IRegistAdapt();
	virtual ~IRegistAdapt();

	/*
		窗口类注册函数
	*/
	bool Regist();

	/*
		卸载窗口类
	*/
	void UnRegist();

	void SetWndProc(WNDPROC	WndProc);
	void SetClassName(TString sClassName);
	void SetIns(HINSTANCE hIns);

private:
	/*
		默认窗口的样式
	*/
	virtual void _Init(WNDCLASSEX& wndClass, HINSTANCE hIns);

private:
	TString		_sClassName;
	HINSTANCE	_hIns;
	WNDPROC		_WndProc;
};

