#pragma once

class CFisherCommand_SMD : public CFisherCommand {
 public:
  CFisherCommand_SMD();
  virtual ~CFisherCommand_SMD();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
