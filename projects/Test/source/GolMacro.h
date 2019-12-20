
#ifndef __AUTO_LIB_H_
#define __AUTO_LIB_H_

#if defined (_WIN32)
#define PLAT win32
#else
#define PLAT x64
#endif

#if defined (_DEBUG)
#if defined (_MT)
#define CON Debug
#else
#define CON Debug_MDd
#endif
#else
#if defined (_MT)
#define CON Release
#else
#define CON Release_MT
#endif
#endif

#define DIH(P, C, L) lib\\ ## P ## \\ ## C ## \\ 
#define SWA(l) #l
#define SWAEX(l) SWA(l)
#define LIBDIR SWAEX(DIH(PLAT, CON, LNK))





#endif // __AUTO_LIB_H_
