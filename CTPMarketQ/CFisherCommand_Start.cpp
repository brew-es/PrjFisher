#include "pch.h"
#include <iostream>

#include "CFisherCommand_Start.h"

CFisherCommand_Start::CFisherCommand_Start() {}

CFisherCommand_Start::~CFisherCommand_Start() {}

bool CFisherCommand_Start::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "start") == 0;
}

void CFisherCommand_Start::execute(const char* optString) {
  std::cout << "尝试连接三个期货公司的前置" << std::endl;
}

void CFisherCommand_Start::print() { std::cout << "start [conf file]" << std::endl; }
