#include "pch.h"
#include <iostream>

#include "CFisherCommand_Stop.h"

CFisherCommand_Stop::CFisherCommand_Stop() {}

CFisherCommand_Stop::~CFisherCommand_Stop() {}

bool CFisherCommand_Stop::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "stop") == 0;
}

void CFisherCommand_Stop::execute(const char* optString) {
  std::cout << "断开三个期货公司的前置" << std::endl;
}

void CFisherCommand_Stop::print() { std::cout << "stop" << std::endl; }
