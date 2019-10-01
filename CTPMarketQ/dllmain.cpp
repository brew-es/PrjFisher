// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include "CFisherCommand_Start.h"
#include "CFisherCommand_Stop.h"
#include "CFisherCommand_SMD.h"
#include "CFisherCommand_SQR.h"
#include "CFisherCommand_Show.h"
#include "CFisherCommand_List.h"

#include "CMyCTPMarketQHandler.h"

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
  CFisherCommand::Instance()->Append("start", new CFisherCommand_Start());
  CFisherCommand::Instance()->Append("stop", new CFisherCommand_Stop());
  CFisherCommand::Instance()->Append("smd", new CFisherCommand_SMD());
  CFisherCommand::Instance()->Append("sqr", new CFisherCommand_SQR());
  CFisherCommand::Instance()->Append("show", new CFisherCommand_Show());
  CFisherCommand::Instance()->Append("list", new CFisherCommand_List());
}

extern "C" void CTPMARKETQ_API FisherModuleDeinit() {
  CMyCTPMarketQHandler::Stop();

  CFisherCommand::Instance()->Remove("list");
  CFisherCommand::Instance()->Remove("show");
  CFisherCommand::Instance()->Remove("sqr");
  CFisherCommand::Instance()->Remove("smd");
  CFisherCommand::Instance()->Remove("stop");
  CFisherCommand::Instance()->Remove("start");
}