#pragma once
#include "CFisherCommand.h"

class CFisherCommand_Load : public CFisherCommand {
 public:
  CFisherCommand_Load();
  virtual ~CFisherCommand_Load();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
