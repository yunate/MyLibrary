1、将下面的文件复制到工作目录下
setup\Microsoft.DTfW.DHL.manifest
setup\dbghelp.dll
release\vld.lib
release\vld_x86.dll

2、在main文件中添加：
// 内存泄露检测器
#ifndef NDEBUG
#pragma comment(lib, "..//vld//release//vld.lib")
#include "..//vld//head//vld.h"
#endif