#include "pch.h"
#include <iostream>

#include "CFisherCommand_List.h"

#include "CMyCTPMarketQHandler.h"

CFisherCommand_List::CFisherCommand_List() {}

CFisherCommand_List::~CFisherCommand_List() {}

bool CFisherCommand_List::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "list") == 0;
}

void CFisherCommand_List::execute(const char* optString) {
  const char* instrumentID = optString;
  CMyCTPMarketQHandler::List(instrumentID);
}

void CFisherCommand_List::print() {
  std::cout << "list <instrument id>" << std::endl;
  std::cout << "list <*>" << std::endl;
}
