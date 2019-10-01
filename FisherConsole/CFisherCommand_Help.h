#pragma once
#include "CFisherCommand.h"

class CFisherCommand_Help : public CFisherCommand {
 public:
  CFisherCommand_Help();
  virtual ~CFisherCommand_Help();

 private:
  // Í¨¹ý CFisherCommand ¼Ì³Ð
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
