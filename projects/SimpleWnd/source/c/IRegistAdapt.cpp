#include "IRegistAdapt.h"

IRegistAdapt::IRegistAdapt()
	: _sClassName(_T("")), _hIns(0), _WndProc(0)
{
}

IRegistAdapt::~IRegistAdapt()
{
}

bool IRegistAdapt::Regist()
{
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hInstance = _hIns;
	wndClass.lpszClassName = _sClassName.c_str();
	wndClass.lpfnWndProc = _WndProc;
	_Init(wndClass, _hIns);
	return RegisterClassEx(&wndClass) == 0 ? false : true;
}

void IRegistAdapt::UnRegist()
{
	UnregisterClass(_sClassName.c_str(), _hIns);
}

void IRegistAdapt::SetWndProc(WNDPROC WndProc)
{
	_WndProc = WndProc;
}

void IRegistAdapt::SetClassName(TString sClassName)
{
	_sClassName = sClassName;
}

void IRegistAdapt::SetIns(HINSTANCE hIns)
{
	_hIns = hIns;
}

void IRegistAdapt::_Init(WNDCLASSEX & wndClass, HINSTANCE hIns)
{
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hIcon = 0;
	wndClass.lpszMenuName = 0;
	wndClass.hIcon = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = ::LoadCursor(hIns, IDC_ARROW);
}
