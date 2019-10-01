#include <iostream>

#include "CFisherCommand_Help.h"

CFisherCommand_Help::CFisherCommand_Help() {}

CFisherCommand_Help::~CFisherCommand_Help() {}

bool CFisherCommand_Help::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "help") == 0;
}

void CFisherCommand_Help::execute(const char* optString) {
  const char* cmdString = optString;
  if (cmdString == nullptr || strlen(cmdString) <= 0 ||
      this->checkIfCmdString(cmdString)) {
    this->print();
  } else {
    CFisherCommand* cmdPtr = _nextCmdPtr;
    while (cmdPtr != nullptr) {
      if (cmdPtr->checkIfCmdString(cmdString)) {
        cmdPtr->print();
        break;
      }
      cmdPtr = cmdPtr->_nextCmdPtr;
    }
    if (cmdPtr == nullptr) {
      std::cout << "ÎÞÐ§ÃüÁî£¨" << cmdString << "£©" << std::endl;
    }
  }
}

void CFisherCommand_Help::print() {
  std::cout << "help <command string>" << std::endl;
}
