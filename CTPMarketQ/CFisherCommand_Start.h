#pragma once

class CFisherCommand_Start : public CFisherCommand {
 public:
  CFisherCommand_Start();
  virtual ~CFisherCommand_Start();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
