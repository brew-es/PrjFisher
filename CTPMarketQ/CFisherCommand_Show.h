#pragma once

class CFisherCommand_Show : public CFisherCommand {
 public:
  CFisherCommand_Show();
  virtual ~CFisherCommand_Show();

 private:
  // Í¨¹ý CFisherCommand ¼Ì³Ð
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
