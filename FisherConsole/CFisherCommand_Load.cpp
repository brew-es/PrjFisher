#include <iostream>
#include <windows.h>

#include "CFisherCommand_Load.h"

typedef void (*FisherModuleInit)();

static void run_module_init(HMODULE hDll) {
  FisherModuleInit fnModuleInit =
      (FisherModuleInit)GetProcAddress(hDll, "FisherModuleInit");
  if (fnModuleInit != NULL) {
    std::cout << "��ʼ��ʼ��..." << std::endl;
    fnModuleInit();
    std::cout << "��ɣ�" << std::endl;
  } else {
    std::cout << "�����ʼ����" << std::endl;
  }
}

CFisherCommand_Load::CFisherCommand_Load() {}

CFisherCommand_Load::~CFisherCommand_Load() {}

bool CFisherCommand_Load::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "load") == 0;
}

void CFisherCommand_Load::execute(const char* optString) {
  if (optString == NULL || strlen(optString) <= 0) {
    std::cout << "�Ƿ�������" << std::endl;
    return;
  }

  std::cout << "��Ҫ���ض�̬�⣺" << optString << std::endl;

  HMODULE hDll = GetModuleHandle(optString);
  if (hDll != NULL) {
    std::cout << "�ظ����ض�̬�⣡�������0x" << std::hex << hDll << "��"
              << std::endl;
    return;
  }

  hDll = LoadLibrary(optString);
  if (hDll != NULL) {
    std::cout << "���سɹ����������0x" << std::hex << hDll << "��"
              << std::endl;
    run_module_init(hDll);
  } else {
    std::cout << "����ʧ�ܣ���������룺0x" << std::hex << GetLastError()
              << "��" << std::endl;
  }
}

void CFisherCommand_Load::print() {
  std::cout << "load <DLL file path>" << std::endl;
}
