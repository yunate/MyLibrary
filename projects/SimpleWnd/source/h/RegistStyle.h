#pragma once
#include "IRegistAdapt.h"

class SimpleRegistStyle :
	public IRegistAdapt
{
public:
	SimpleRegistStyle();
	virtual ~SimpleRegistStyle();

private:
	// 特有的窗口样式，这儿只是为了说明问题，实际上和WndRegister中的一样-.-
	virtual void _Init(WNDCLASSEX& wndClass, HINSTANCE hIns);
};

