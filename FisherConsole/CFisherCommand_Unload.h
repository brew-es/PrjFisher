#pragma once
#include "CFisherCommand.h"

class CFisherCommand_Unload : public CFisherCommand {
 public:
  CFisherCommand_Unload();
  virtual ~CFisherCommand_Unload();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
