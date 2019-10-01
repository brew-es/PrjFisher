#include <iostream>
#include "CFisherCommand_Version.h"

#define APP_VERSION_STRING "v1.0.0"

CFisherCommand_Version::CFisherCommand_Version() {}

CFisherCommand_Version::~CFisherCommand_Version() {}

bool CFisherCommand_Version::checkIfCmdString(const char* cmdString) {
  return strcmp(cmdString, "version") == 0;
}

void CFisherCommand_Version::execute(const char* optString) {
  std::cout << "Ó¦ÓÃ°æ±¾£º" << APP_VERSION_STRING << std::endl;
}

void CFisherCommand_Version::print() {
  std::cout << "version" << std::endl;
}
