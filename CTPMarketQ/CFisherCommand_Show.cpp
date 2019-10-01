#include "pch.h"
#include <iostream>

#include "CFisherCommand_Show.h"

CFisherCommand_Show::CFisherCommand_Show(){}

CFisherCommand_Show::~CFisherCommand_Show(){}

bool CFisherCommand_Show::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "show") == 0;
}

void CFisherCommand_Show::execute(const char* optString) {
  std::cout << "展示合约的分时图" << std::endl;
}

void CFisherCommand_Show::print() {
  std::cout << "show <instrument id> [1|2|3 <num>] <on|off>" << std::endl;
  std::cout << "show <*> <off>" << std::endl;
}
