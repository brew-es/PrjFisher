#include <iostream>
#include <windows.h>

static BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
  switch (fdwCtrlType) {
      // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
      std::cout << "Ctrl-C event" << std::endl;
      Beep(750, 300);
      return TRUE;

      // CTRL-CLOSE: confirm that the user wants to exit.
    case CTRL_CLOSE_EVENT:
      Beep(600, 200);
      std::cout << "Ctrl-Close event" << std::endl;
      return TRUE;

      // Pass other signals to the next handler.
    case CTRL_BREAK_EVENT:
      Beep(900, 200);
      std::cout << "Ctrl-Break event" << std::endl;
      return FALSE;

    case CTRL_LOGOFF_EVENT:
      Beep(1000, 200);
      std::cout << "Ctrl-Logoff event" << std::endl;
      return FALSE;

    case CTRL_SHUTDOWN_EVENT:
      Beep(750, 500);
      std::cout << "Ctrl-Shutdown event" << std::endl;
      return FALSE;

    default:
      return FALSE;
  }
}

void SetConsoleCtrlHandler() {
  // SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_PROCESSED_INPUT);
  std::cout << "设置控制台响应接口："
            << (SetConsoleCtrlHandler(CtrlHandler, TRUE) ? "成功" : "失败")
            << std::endl;
}
