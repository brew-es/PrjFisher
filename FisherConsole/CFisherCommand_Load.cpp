#include <iostream>
#include <windows.h>

#include "CFisherCommand_Load.h"

typedef void (*FisherModuleInit)();

static void run_module_init(HMODULE hDll) {
  FisherModuleInit fnModuleInit =
      (FisherModuleInit)GetProcAddress(hDll, "FisherModuleInit");
  if (fnModuleInit != NULL) {
    std::cout << "开始初始化..." << std::endl;
    fnModuleInit();
    std::cout << "完成！" << std::endl;
  } else {
    std::cout << "无需初始化。" << std::endl;
  }
}

CFisherCommand_Load::CFisherCommand_Load() {}

CFisherCommand_Load::~CFisherCommand_Load() {}

bool CFisherCommand_Load::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "load") == 0;
}

void CFisherCommand_Load::execute(const char* optString) {
  if (optString == NULL || strlen(optString) <= 0) {
    std::cout << "非法参数！" << std::endl;
    return;
  }

  std::cout << "将要加载动态库：" << optString << std::endl;

  HMODULE hDll = GetModuleHandle(optString);
  if (hDll != NULL) {
    std::cout << "重复加载动态库！（句柄：0x" << std::hex << hDll << "）"
              << std::endl;
    return;
  }

  hDll = LoadLibrary(optString);
  if (hDll != NULL) {
    std::cout << "加载成功。（句柄：0x" << std::hex << hDll << "）"
              << std::endl;
    run_module_init(hDll);
  } else {
    std::cout << "加载失败！（错误代码：0x" << std::hex << GetLastError()
              << "）" << std::endl;
  }
}

void CFisherCommand_Load::print() {
  std::cout << "load <DLL file path>" << std::endl;
}
