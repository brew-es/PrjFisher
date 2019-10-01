#include "pch.h"
#include <iostream>

#include "CFisherCommand_SMD.h"

CFisherCommand_SMD::CFisherCommand_SMD() {}

CFisherCommand_SMD::~CFisherCommand_SMD() {}

bool CFisherCommand_SMD::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "smd") == 0;
}

void CFisherCommand_SMD::execute(const char* optString) {}

void CFisherCommand_SMD::print() {
  std::cout << "smd <instrument id> <on|off>" << std::endl;
  std::cout << "smd <*> <off>" << std::endl;
}
