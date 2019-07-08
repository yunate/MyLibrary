#pragma once

#include <tchar.h>
#include <windows.h>

class App
{
public:
	~App();

private:
	App();
	App(const App&);

public:
	// 注册所有的窗口类
	void RegistAllWnd();

	// 卸载所有的窗口类
	void UnRegistAllWnd();

public:
	inline HINSTANCE GetIns() { return _hIns; }
	inline void SetIns(HINSTANCE hIns) { _hIns = hIns; };

private:
	HINSTANCE _hIns;

private:
	static App& GetSignalIns()
	{
		static App s_Ins;
		return s_Ins;
	}

	friend App& GetAppIns();
};

inline App& GetAppIns() 
{
	return App::GetSignalIns();
}

