#include "pch.h"
#include <iostream>

#include "CFisherCommand_SQR.h"

CFisherCommand_SQR::CFisherCommand_SQR() {}

CFisherCommand_SQR::~CFisherCommand_SQR() {}

bool CFisherCommand_SQR::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "sqr") == 0;
}

void CFisherCommand_SQR::execute(const char* optString) {}

void CFisherCommand_SQR::print() {
  std::cout << "sqr <instrument id> <on|off>" << std::endl;
  std::cout << "sqr <*> <off>" << std::endl;
}
