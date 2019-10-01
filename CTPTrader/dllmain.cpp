// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#define CTPMARKETQ_API __declspec(dllexport)
extern "C" void CTPMARKETQ_API FisherModuleInit() {
  //CFisherCommand::Instance()->Append("win", new CFisherCommand_Start());
  //CFisherCommand::Instance()->Append("stop", new CFisherCommand_Stop());
  //CFisherCommand::Instance()->Append("smd", new CFisherCommand_SMD());
  //CFisherCommand::Instance()->Append("sqr", new CFisherCommand_SQR());
}
