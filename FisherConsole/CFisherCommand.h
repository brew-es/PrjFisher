#pragma once

#include "CFisherConsole.h"


class FISHER_API CFisherCommand {
 public:
  CFisherCommand();
  virtual ~CFisherCommand();

  friend class CFisherCommand_Help;

 public:
  static CFisherCommand* Instance();

 public:
  virtual void Release();
  void Execute(const char* cmdString, const char* optString);
  void Append(const char* cmdString, CFisherCommand* cmdPtr);
  void Remove(const char* cmdString);

 private:
  virtual bool checkIfCmdString(const char* cmdString) = 0;
  virtual void execute(const char* optString) = 0;
  virtual void print() = 0;

 protected:
  CFisherCommand* _nextCmdPtr;

 private:
  CFisherCommand* _prevCmdPtr;

 private:
  static CFisherCommand* _instancePtr;
};
