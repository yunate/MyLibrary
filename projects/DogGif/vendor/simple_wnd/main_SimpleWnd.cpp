
#include <tchar.h>
#include <windows.h>

#include "App.h"
#include "SimpleWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       nCmdShow)
{
	App* pApp = &GetAppIns();
	pApp->SetIns(hInstance);
	pApp->RegistAllWnd();

	// Ö÷Âß¼­
	{
		SimpleWnd simpleWnd;
		simpleWnd.DoModel();
	}

	pApp->UnRegistAllWnd();
	return 0;
}