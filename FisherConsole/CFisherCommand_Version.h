#pragma once
#include "CFisherCommand.h"

class CFisherCommand_Version : public CFisherCommand {
 public:
  CFisherCommand_Version();
  virtual ~CFisherCommand_Version();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
