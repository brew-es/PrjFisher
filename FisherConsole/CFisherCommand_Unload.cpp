#include <iostream>
#include <windows.h>

#include "CFisherCommand_Unload.h"

typedef void (*FisherModuleDeinit)();

static void run_module_deinit(HMODULE hDll) {
  FisherModuleDeinit fnModuleDeinit =
      (FisherModuleDeinit)GetProcAddress(hDll, "FisherModuleDeinit");
  if (fnModuleDeinit != NULL) {
    std::cout << "��ʼ����ʼ��..." << std::endl;
    fnModuleDeinit();
    std::cout << "��ɣ�" << std::endl;
  } else {
    std::cout << "���跴��ʼ����" << std::endl;
  }
}

CFisherCommand_Unload::CFisherCommand_Unload() {}

CFisherCommand_Unload::~CFisherCommand_Unload() {}

bool CFisherCommand_Unload::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "unload") == 0;
}

void CFisherCommand_Unload::execute(const char* optString) {
  if (optString == NULL || strlen(optString) <= 0) {
    std::cout << "�Ƿ�������" << std::endl;
    return;
  }

  std::cout << "��Ҫж�ض�̬�⣺" << optString << std::endl;

  HMODULE hDll = GetModuleHandle(optString);
  if (hDll == NULL) {
    std::cout << "δ���ظö�̬�⣡��������룺0x" << std::hex << GetLastError()
              << "��" << std::endl;
    return;
  }

  run_module_deinit(hDll);

  if (FreeLibrary(hDll)) {
    std::cout << "ж�سɹ����������0x" << std::hex << hDll << "��"
              << std::endl;
  } else {
    std::cout << "ж��ʧ�ܣ���������룺0x" << std::hex << GetLastError()
              << "��" << std::endl;
  }
}

void CFisherCommand_Unload::print() {
  std::cout << "unload <DLL file name>" << std::endl;
}
