#pragma once

class CFisherCommand_Stop : public CFisherCommand {
 public:
  CFisherCommand_Stop();
  virtual ~CFisherCommand_Stop();

 private:
  // ͨ�� CFisherCommand �̳�
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
