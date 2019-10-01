#include <iostream>
#include <windows.h>

#include "CFisherCommand_Unload.h"

typedef void (*FisherModuleDeinit)();

static void run_module_deinit(HMODULE hDll) {
  FisherModuleDeinit fnModuleDeinit =
      (FisherModuleDeinit)GetProcAddress(hDll, "FisherModuleDeinit");
  if (fnModuleDeinit != NULL) {
    std::cout << "开始反初始化..." << std::endl;
    fnModuleDeinit();
    std::cout << "完成！" << std::endl;
  } else {
    std::cout << "无需反初始化。" << std::endl;
  }
}

CFisherCommand_Unload::CFisherCommand_Unload() {}

CFisherCommand_Unload::~CFisherCommand_Unload() {}

bool CFisherCommand_Unload::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "unload") == 0;
}

void CFisherCommand_Unload::execute(const char* optString) {
  if (optString == NULL || strlen(optString) <= 0) {
    std::cout << "非法参数！" << std::endl;
    return;
  }

  std::cout << "将要卸载动态库：" << optString << std::endl;

  HMODULE hDll = GetModuleHandle(optString);
  if (hDll == NULL) {
    std::cout << "未加载该动态库！（错误代码：0x" << std::hex << GetLastError()
              << "）" << std::endl;
    return;
  }

  run_module_deinit(hDll);

  if (FreeLibrary(hDll)) {
    std::cout << "卸载成功。（句柄：0x" << std::hex << hDll << "）"
              << std::endl;
  } else {
    std::cout << "卸载失败！（错误代码：0x" << std::hex << GetLastError()
              << "）" << std::endl;
  }
}

void CFisherCommand_Unload::print() {
  std::cout << "unload <DLL file name>" << std::endl;
}
