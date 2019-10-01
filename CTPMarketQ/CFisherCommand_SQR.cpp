#include "pch.h"
#include <iostream>

#include "CFisherCommand_SQR.h"

#include "CMyCTPMarketQHandler.h"

CFisherCommand_SQR::CFisherCommand_SQR() {}

CFisherCommand_SQR::~CFisherCommand_SQR() {}

bool CFisherCommand_SQR::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "sqr") == 0;
}

void CFisherCommand_SQR::execute(const char* optString) {
  if (optString == nullptr || strlen(optString) <= 0 ||
      strchr(optString, ' ') == nullptr) {
    std::cout << "²ÎÊý´íÎó£¡" << std::endl;
    return;
  }

  const char* instrumentID = optString;
  char* on_or_off = strchr((char*)optString, ' ') + 1;
  on_or_off[-1] = '\0';

  bool on = strcmp("on", on_or_off) == 0;
  CMyCTPMarketQHandler::SQR(instrumentID, on);
}

void CFisherCommand_SQR::print() {
  std::cout << "sqr <instrument id> <on|off>" << std::endl;
  std::cout << "sqr <*> <off>" << std::endl;
}
