#include <iostream>

#include "CFisherCommand.h"

#include "CFisherCommand_Help.h"
#include "CFisherCommand_Version.h"
#include "CFisherCommand_Load.h"
#include "CFisherCommand_Unload.h"
#include "CFisherCommand_Quit.h"

class CFisherCommand_Dummy : public CFisherCommand {
 public:
  CFisherCommand_Dummy() {}
  virtual ~CFisherCommand_Dummy() {}

 private:
  // Í¨¹ý CFisherCommand ¼Ì³Ð
  virtual bool checkIfCmdString(const char* cmdString) override {
    return false;
  }
  virtual void execute(const char* optString) override {}
  virtual void print() override {}
};


CFisherCommand* CFisherCommand::_instancePtr = nullptr;

CFisherCommand::CFisherCommand() : _nextCmdPtr(nullptr), _prevCmdPtr(nullptr){}

CFisherCommand::~CFisherCommand() {
  if (_nextCmdPtr != nullptr) {
    _nextCmdPtr->Release();
    _nextCmdPtr = nullptr;
  }
}

CFisherCommand* CFisherCommand::Instance() {
  if (_instancePtr == nullptr) {
    _instancePtr = new CFisherCommand_Dummy();

    std::cout << std::endl << "[" << std::endl;
    _instancePtr->Append("help", new CFisherCommand_Help());
    _instancePtr->Append("version", new CFisherCommand_Version());
    _instancePtr->Append("load", new CFisherCommand_Load());
    _instancePtr->Append("unload", new CFisherCommand_Unload());
    _instancePtr->Append("quit", new CFisherCommand_Quit());
    std::cout << "]" << std::endl;
  }
  return _instancePtr;
}

void CFisherCommand::Release() { delete this; }

void CFisherCommand::Execute(const char* cmdString, const char* optString) {
  if (this->checkIfCmdString(cmdString)) {
    this->execute(optString);
  } else if (_nextCmdPtr != nullptr) {
    _nextCmdPtr->Execute(cmdString, optString);
  } else {
    std::cout << "ÎÞÐ§ÃüÁî£¨" << cmdString << " " << optString << "£©"
              << std::endl;
  }
}

void CFisherCommand::Append(const char* cmdString, CFisherCommand* cmdPtr) {
  if (this->checkIfCmdString(cmdString)) {
    std::cout << "ÖØ¸´×¢²áÃüÁî£¨" << cmdString << "£©" << std::endl;
    cmdPtr->Release();
  } else if (_nextCmdPtr != nullptr) {
    _nextCmdPtr->Append(cmdString, cmdPtr);
  } else {
    cmdPtr->_prevCmdPtr = this;
    _nextCmdPtr = cmdPtr;
    std::cout << "³É¹¦×¢²áÃüÁî£¨" << cmdString << "£©" << std::endl;
  }
}

void CFisherCommand::Remove(const char* cmdString) {
  if (this->checkIfCmdString(cmdString)) {
    _prevCmdPtr->_nextCmdPtr = _nextCmdPtr;
    _nextCmdPtr = _prevCmdPtr = nullptr;
    std::cout << "³É¹¦·´×¢²áÃüÁî£¨" << cmdString << "£©" << std::endl;
    this->Release();
  } else if (_nextCmdPtr != nullptr) {
    _nextCmdPtr->Remove(cmdString);
  } else {
    std::cout << "Î´×¢²áÃüÁî£¨" << cmdString << "£©" << std::endl;
  }
}
