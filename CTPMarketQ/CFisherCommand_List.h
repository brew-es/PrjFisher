#pragma once

class CFisherCommand_List : public CFisherCommand {
 public:
  CFisherCommand_List();
  virtual ~CFisherCommand_List();

 private:
  // Í¨¹ý CFisherCommand ¼Ì³Ð
  virtual bool checkIfCmdString(const char* cmdString) override;
  virtual void execute(const char* optString) override;
  virtual void print() override;
};
