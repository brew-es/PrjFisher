#pragma once


#ifdef _DEBUG
#define MAX_COMPANIES_OF_FUTURES 4 // 最后一个配置是7*24的行情测试服务器
#else
#define MAX_COMPANIES_OF_FUTURES 3
#endif  // _DEBUG

#define MAX_FRONT_NUM	8

enum {
  MSG_TYPE_MARKET = 0x2004,
  MSG_TYPE_QUOTE = 0x2005,
};