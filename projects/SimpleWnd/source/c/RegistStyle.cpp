#include "RegistStyle.h"

SimpleRegistStyle::SimpleRegistStyle()
	: IRegistAdapt()
{
}

SimpleRegistStyle::~SimpleRegistStyle()
{
}

void SimpleRegistStyle::_Init(WNDCLASSEX & wndClass, HINSTANCE hIns)
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
