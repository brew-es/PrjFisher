#pragma once


#ifdef _DEBUG
#define MAX_COMPANIES_OF_FUTURES 4 // ���һ��������7*24��������Է�����
#else
#define MAX_COMPANIES_OF_FUTURES 3
#endif  // _DEBUG

#define MAX_FRONT_NUM	8

enum {
  MSG_TYPE_MARKET = 0x2004,
  MSG_TYPE_QUOTE = 0x2005,
};