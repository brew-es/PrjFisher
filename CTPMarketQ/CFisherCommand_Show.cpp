#include "pch.h"
#include <iostream>

#include "CFisherCommand_Show.h"

#include "CMyCTPMarketQHandler.h"

CFisherCommand_Show::CFisherCommand_Show(){}

CFisherCommand_Show::~CFisherCommand_Show(){}

bool CFisherCommand_Show::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "show") == 0;
}

void CFisherCommand_Show::execute(const char* optString) {
  if (optString == nullptr || strlen(optString) <= 0 ||
      strchr(optString, ' ') == nullptr) {
    std::cout << "²ÎÊý´íÎó£¡" << std::endl;
    return;
  }

  const char* instrumentID = optString;
  char* on_or_off = strchr((char*)optString, ' ') + 1;
  on_or_off[-1] = '\0';

  bool on = strcmp("on", on_or_off) == 0;
  CMyCTPMarketQHandler::Show(instrumentID, on);
}

void CFisherCommand_Show::print() {
  std::cout << "show <instrument id> <on|off>" << std::endl;
  std::cout << "show <*> <off>" << std::endl;
}
