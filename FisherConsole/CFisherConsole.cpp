// CFisherConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "CFisherCommand.h"

extern void SetConsoleCtrlHandler();

int main() {

  atexit([]() {
    std::cout << "Fisher控制台已结束。" << std::endl;
    std::cout << "]" << std::endl;
  });

  std::cout << "开始运行Fisher控制台" << std::endl;
  SetConsoleCtrlHandler();

  CFisherCommand::Instance();
  std::cout << std::endl;

  while (true) {
    char cmdLine[512] = "";

    std::cout << ":";
    std::fgets(cmdLine, 512, stdin);
    std::fflush(stdin);

    char* newLineChar = strrchr(cmdLine, '\n');
    if (newLineChar != nullptr) {
      *newLineChar = '\0';
    }

    const char* cmdString = cmdLine;
    char* optString = strchr(cmdLine, ' ');
    if (optString != nullptr) {
      *optString = '\0';
      optString++;
    } else {
      optString = (char*)"";
    }

    std::cout << std::endl << "[" << std::endl;
    CFisherCommand::Instance()->Execute(cmdLine, optString);
    std::cout << "]" << std::endl;
    std::cout << std::endl;
  };
}
