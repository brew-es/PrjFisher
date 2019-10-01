#pragma once

class CFisherCommand_SQR : public CFisherCommand {
 public:
  CFisherCommand_SQR();
  virtual ~CFisherCommand_SQR();

 private:
  // Í¨¹ý CFisherCommand ¼Ì³Ð
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
