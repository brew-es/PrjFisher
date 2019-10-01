#include "pch.h"
#include <iostream>

#include "CFisherCommand_SMD.h"

#include "CMyCTPMarketQHandler.h"

CFisherCommand_SMD::CFisherCommand_SMD() {}

CFisherCommand_SMD::~CFisherCommand_SMD() {}

bool CFisherCommand_SMD::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "smd") == 0;
}

void CFisherCommand_SMD::execute(const char* optString) {
  if (optString == nullptr || strlen(optString) <= 0 ||
      strchr(optString, ' ') == nullptr) {
    std::cout << "²ÎÊý´íÎó£¡" << std::endl;
    return;
  }

  const char* instrumentID = optString;
  char* on_or_off = strchr((char*)optString, ' ') + 1;
  on_or_off[-1] = '\0';

  bool on = strcmp("on", on_or_off) == 0;
  CMyCTPMarketQHandler::SMD(instrumentID, on);
}

void CFisherCommand_SMD::print() {
  std::cout << "smd <instrument id> <on|off>" << std::endl;
  std::cout << "smd <*> <off>" << std::endl;
}
