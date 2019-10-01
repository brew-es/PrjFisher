// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"

// 当使用预编译的头时，需要使用此源文件，编译才能成功。

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/FisherConsole.lib")
#else
#pragma comment(lib, "../x64/Release/FisherConsole.lib")
#endif  // _DEBUG
