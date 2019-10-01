#pragma once
#include "CFisherCommand.h"

class CFisherCommand_Quit : public CFisherCommand {
 public:
  CFisherCommand_Quit();
  virtual ~CFisherCommand_Quit();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
