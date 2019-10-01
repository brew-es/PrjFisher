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
    std::cout << "CTP行情服务已经在运行。" << std::endl;
    std::cout << "如果需要替换行情前置，请停止之后再试！" << std::endl;
    return;
  }
  if (optString != nullptr) {
    std::cout << "尝试启动行情服务" << std::endl;
    const char* confile = optString;
    auto num = CMyCTPMarketQHandler::Start(confile);
    if (num == 0) {
      std::cout << "失败!" << std::endl;
    } else {
      std::cout << "成功!" << std::endl;
    }
  } else {
    std::cout << "没有指定配置文件！" << std::endl;
  }
}

void CFisherCommand_Start::print() { std::cout << "start [conf file]" << std::endl; }
