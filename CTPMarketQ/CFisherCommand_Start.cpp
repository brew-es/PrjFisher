#include "pch.h"
#include <iostream>

#include "CFisherCommand_Start.h"

#include "CMyCTPMarketQHandler.h"

CFisherCommand_Start::CFisherCommand_Start() {}

CFisherCommand_Start::~CFisherCommand_Start() {}

bool CFisherCommand_Start::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "start") == 0;
}

void CFisherCommand_Start::execute(const char* optString) {
  if (CMyCTPMarketQHandler::IsRunning()) {
    std::cout << "CTP��������Ѿ������С�" << std::endl;
    std::cout << "�����Ҫ�滻����ǰ�ã���ֹ֮ͣ�����ԣ�" << std::endl;
    return;
  }
  if (optString != nullptr) {
    std::cout << "���������������" << std::endl;
    const char* confile = optString;
    auto num = CMyCTPMarketQHandler::Start(confile);
    if (num == 0) {
      std::cout << "ʧ��!" << std::endl;
    } else {
      std::cout << "�ɹ�!" << std::endl;
    }
  } else {
    std::cout << "û��ָ�������ļ���" << std::endl;
  }
}

void CFisherCommand_Start::print() { std::cout << "start [conf file]" << std::endl; }
