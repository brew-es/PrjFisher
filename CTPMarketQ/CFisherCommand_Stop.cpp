#include "pch.h"
#include <iostream>

#include "CFisherCommand_Stop.h"

#include "CMyCTPMarketQHandler.h"

CFisherCommand_Stop::CFisherCommand_Stop() {}

CFisherCommand_Stop::~CFisherCommand_Stop() {}

bool CFisherCommand_Stop::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "stop") == 0;
}

void CFisherCommand_Stop::execute(const char* optString) {
  std::cout << "尝试停止行情服务" << std::endl;
  CMyCTPMarketQHandler::Stop();
  std::cout << "完成。" << std::endl;
}

void CFisherCommand_Stop::print() { std::cout << "stop" << std::endl; }