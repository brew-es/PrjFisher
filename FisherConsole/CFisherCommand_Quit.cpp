#include <iostream>
#include "CFisherCommand_Quit.h"

CFisherCommand_Quit::CFisherCommand_Quit() {}

CFisherCommand_Quit::~CFisherCommand_Quit() {}

bool CFisherCommand_Quit::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "quit") == 0;
}

void CFisherCommand_Quit::execute(const char* optString) { exit(0); }

void CFisherCommand_Quit::print() { std::cout << "quit [force, save <cache file>]" << std::endl; }
