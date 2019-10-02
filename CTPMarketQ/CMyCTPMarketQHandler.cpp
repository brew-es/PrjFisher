#include "pch.h"
#include <iostream>
#include <fstream>

#include "CMyCTPMarketQHandler.h"

#include <io.h>
#include <direct.h>

static bool MyCreateDirectory(std::string folder) {
  std::string sub;
  std::string folder_builder;

  std::replace(folder.begin(), folder.end(), '\\', '/');
  sub.reserve(folder.size());

  for (auto it = folder.begin(); it != folder.end(); ++it) {
    const char c = *it;
    sub.push_back(c);
    if (c == '/' || it == folder.end() - 1) {
      folder_builder.append(sub);
      if (0 != ::_access(folder_builder.c_str(), 0)) {
        if (0 != ::_mkdir(folder_builder.c_str())) {
          return false;
        }
      }
      sub.clear();
    }
  }
  return true;
}

enum {
  MD_RET_OK = -0,              // 代表成功
  MD_RET_CONNECT_FAILED = -1,  // 表示网络连接失败
  MD_RET_MAX_RESPONSE = -2,    // 表示未处理请求超过许可数
  MD_RET_MAX_REQUEST = -3,     // 表示每秒发送请求数超过许可数
};

static const char* errString(int err) {
  static char unknown[128] = "";

  switch (err) {
    case MD_RET_OK:
      return "成功";
    case MD_RET_CONNECT_FAILED:
      return "网络连接失败";
    case MD_RET_MAX_RESPONSE:
      return "未处理请求超过许可数";
    case MD_RET_MAX_REQUEST:
      return "每秒发送请求数超过许可数";
    default:
      sprintf_s(unknown, "未知错误(代码：%d)", err);
      return unknown;
  }
}

enum {
  MD_DISCONNECT_REASON_READ_FAILED = 0x1001,              // 网络读失败
  MD_DISCONNECT_REASON_WRITE_FAILED = 0x1002,             // 网络写失败
  MD_DISCONNECT_REASON_HEARTBEAT_READ_TIMEOUT = 0x2001,   // 接收心跳超时
  MD_DISCONNECT_REASON_HEARTBEAT_WRITE_TIMEOUT = 0x2002,  // 发送心跳失败
  MD_DISCONNECT_REASON_INVALID_PACKET = 0x2003,           // 收到错误报文
};

static const char* reasonString(int reason) {
  static char unknown[128] = "";

  switch (reason) {
    case MD_DISCONNECT_REASON_READ_FAILED:
      return "网络读失败";
    case MD_DISCONNECT_REASON_WRITE_FAILED:
      return "网络写失败";
    case MD_DISCONNECT_REASON_HEARTBEAT_READ_TIMEOUT:
      return "接收心跳超时";
    case MD_DISCONNECT_REASON_HEARTBEAT_WRITE_TIMEOUT:
      return "发送心跳失败";
    case MD_DISCONNECT_REASON_INVALID_PACKET:
      return "收到错误报文";
    default:
      sprintf_s(unknown, "未知原因(代码：0x%04x)", reason);
      return unknown;
  }
}

static CMyCTPMarketQHandler* CTPMarketQHandlerArray[MAX_COMPANIES_OF_FUTURES] = {
    nullptr};
static bool CTPMarketQRunning = false;

static std::vector<std::string> sqr_instrumentIDs, smd_instrumentIDs;

CMyCTPMarketQHandler::CMyCTPMarketQHandler(std::string company,
                                           std::string brokerID,
                                           std::string flowPath, bool usingUDP,
                                           bool isMulticast, std::string userID,
                                           std::string password,
                                           std::string front[MAX_FRONT_NUM])
    : _company(company),
      _brokerID(brokerID),
      _flowPath(flowPath),
      _usingUDP(usingUDP),
      _isMulticast(isMulticast),
      _userID(userID),
      _password(password),
      _requestID(0),
      _mdApi(nullptr) {
  MyCreateDirectory(_flowPath);

  _mdApi = CThostFtdcMdApi::CreateFtdcMdApi(_flowPath.c_str(), _usingUDP,
                                            _isMulticast);
  _mdApi->RegisterSpi(this);

  uint8_t registered_front_num = 0;
  for (size_t i = 0; i < MAX_FRONT_NUM; i++) {
    _front[i] = front[i];
    if (!_front[i].empty()) {
      std::string front_address(_usingUDP ? "udp://" : "tcp://");
      front_address += _front[i];
      _mdApi->RegisterFront((char*)front_address.c_str());
      registered_front_num++;
    }
  }
  _mdApi->Init();
};

CMyCTPMarketQHandler::~CMyCTPMarketQHandler() {
  if (_mdApi != nullptr) {
    CThostFtdcUserLogoutField userLogoutField;
    memset(&userLogoutField, 0x00, sizeof(CThostFtdcUserLogoutField));

    strcpy_s(userLogoutField.BrokerID, _brokerID.c_str());
    strcpy_s(userLogoutField.UserID, _userID.c_str());

    int ret = _mdApi->ReqUserLogout(&userLogoutField, ++_requestID);
    _mdApi->Release();
  }
}

CMyCTPMarketQHandler* CMyCTPMarketQHandler::Handler(uint8_t handlerIndex) {
  CMyCTPMarketQHandler* ret = nullptr;
  if (handlerIndex < MAX_COMPANIES_OF_FUTURES) {
    ret = CTPMarketQHandlerArray[handlerIndex];
  }
  return ret;
}

uint8_t CMyCTPMarketQHandler::Start(const char* confile) {
  uint8_t ret = 0;

  std::ifstream ifs(confile);
  if (ifs.is_open()) {
    std::string errs;

    Json::Value root;
    Json::CharReaderBuilder crbuider;

    Json::parseFromStream(crbuider, ifs, &root, &errs);

    // std::cout << root << std::endl;

    Json::Value conf = root["conf"];
    for (int i = 0; i < std::min<int>(conf.size(), MAX_COMPANIES_OF_FUTURES);
         i++) {
      std::string company = conf[i]["company"].asString();
      std::string brokerID = conf[i]["brokerID"].asString();
      std::string flowPath = conf[i]["flowPath"].asString();

      bool usingUDP = conf[i]["usingUDP"].asBool();
      bool isMulticast = conf[i]["isMulticast"].asBool();

      std::string userID = conf[i]["userID"].asString();
      std::string password = conf[i]["password"].asString();

      std::string address[MAX_FRONT_NUM];

      Json::Value front = conf[i]["front"];
      for (int j = 0; j < std::min<int>(front.size(), MAX_FRONT_NUM); j++) {
        address[j] = front[j].asString();
      }

      try {
        CTPMarketQHandlerArray[i] =
            new CMyCTPMarketQHandler(company, brokerID, flowPath, usingUDP,
                                     isMulticast, userID, password, address);
        std::cout << "（" << i << "，" << company << "）成功。" << std::endl;
      } catch (std::exception& e) {
        std::cout << "（" << i << "，" << company << "）失败：" << e.what()
                  << std::endl;
      }

      ret++;
    }

    CTPMarketQRunning = ret > 0;
  }

  return ret;
}

bool CMyCTPMarketQHandler::IsRunning() { return CTPMarketQRunning; }

void CMyCTPMarketQHandler::Stop() {
  for (size_t i = 0; i < MAX_COMPANIES_OF_FUTURES; i++) {
    if (CTPMarketQHandlerArray[i] != nullptr) {
      delete CTPMarketQHandlerArray[i];
      CTPMarketQHandlerArray[i] = nullptr;
    }
  }
  CTPMarketQRunning = false;
}

bool CMyCTPMarketQHandler::SQR(const char* instrumentID, bool on) {
  if (on && (instrumentID == nullptr || strlen(instrumentID) <= 0 ||
             instrumentID[0] == '*')) {
    std::cout << "参数错误！" << std::endl;
    return false;
  }

  if (instrumentID == nullptr || strlen(instrumentID) <= 0 ||
      instrumentID[0] == '*') {
    for (size_t i = 0; i < MAX_COMPANIES_OF_FUTURES; i++) {
      if (CTPMarketQHandlerArray[i] != nullptr) {
        for (size_t j = 0; j < smd_instrumentIDs.size(); j++) {
          CTPMarketQHandlerArray[i]->sqr(smd_instrumentIDs[j].c_str(), false);
        }
      }
    }
    sqr_instrumentIDs.clear();
    std::cout << "已全部取消询价。" << std::endl;
    return true;
  }

  auto found_instrumentID = std::find_if(
      sqr_instrumentIDs.begin(), sqr_instrumentIDs.end(),
      [instrumentID](std::string v) { return v.compare(instrumentID) == 0; });
  if (on) {
    if (found_instrumentID != sqr_instrumentIDs.end()) {
      std::cout << "重复订阅（" << instrumentID << "）" << std::endl;
      return true;
    }
    sqr_instrumentIDs.emplace_back(instrumentID);
  } else {
    if (found_instrumentID == sqr_instrumentIDs.end()) {
      std::cout << "没有订阅（" << instrumentID << "）" << std::endl;
      return true;
    }
    sqr_instrumentIDs.erase(found_instrumentID);
  }

  for (size_t i = 0; i < MAX_COMPANIES_OF_FUTURES; i++) {
    if (CTPMarketQHandlerArray[i] != nullptr) {
      CTPMarketQHandlerArray[i]->sqr(instrumentID, on);
    }
  }

  std::cout << (on ? "订阅询价完成。" : "取消询价完成。") << std::endl;
  return true;
}

bool CMyCTPMarketQHandler::SMD(const char* instrumentID, bool on) {
  if (on && (instrumentID == nullptr || strlen(instrumentID) <= 0 ||
             instrumentID[0] == '*')) {
    std::cout << "参数错误！" << std::endl;
    return false;
  }

  if (instrumentID == nullptr || strlen(instrumentID) <= 0 ||
      instrumentID[0] == '*') {
    for (size_t i = 0; i < MAX_COMPANIES_OF_FUTURES; i++) {
      if (CTPMarketQHandlerArray[i] != nullptr) {
        for (size_t j = 0; j < smd_instrumentIDs.size(); j++) {
          CTPMarketQHandlerArray[i]->smd(smd_instrumentIDs[j].c_str(), false);
        }
      }
    }
    smd_instrumentIDs.clear();
    std::cout << "已全部取消行情。" << std::endl;
    return true;
  }

  auto found_instrumentID = std::find_if(
      smd_instrumentIDs.begin(), smd_instrumentIDs.end(),
      [instrumentID](std::string v) { return v.compare(instrumentID) == 0; });
  if (on) {
    if (found_instrumentID != smd_instrumentIDs.end()) {
      std::cout << "重复订阅（" << instrumentID << "）" << std::endl;
      return true;
    }
    smd_instrumentIDs.emplace_back(instrumentID);
  } else {
    if (found_instrumentID == smd_instrumentIDs.end()) {
      std::cout << "没有订阅（" << instrumentID << "）" << std::endl;
      return true;
    }
    smd_instrumentIDs.erase(found_instrumentID);
  }

  for (size_t i = 0; i < MAX_COMPANIES_OF_FUTURES; i++) {
    if (CTPMarketQHandlerArray[i] != nullptr) {
      CTPMarketQHandlerArray[i]->smd(instrumentID, on);
    }
  }

  std::cout << (on ? "订阅行情完成。" : "取消行情完成。") << std::endl;
  return true;
}

void CMyCTPMarketQHandler::List(const char* instrumentID) {
  if (instrumentID == nullptr || strlen(instrumentID) <= 0 ||
      instrumentID[0] == '*') {
    std::cout << "已订阅行情" << std::endl;
    for (size_t i = 0; i < smd_instrumentIDs.size(); i++) {
      std::cout << smd_instrumentIDs[i] << std::endl;
    }
    std::cout << "已订阅询价" << std::endl;
    for (size_t i = 0; i < sqr_instrumentIDs.size(); i++) {
      std::cout << sqr_instrumentIDs[i] << std::endl;
    }
    return;
  }

  std::cout << "合约（" << instrumentID << "）：";
  auto found_smd_instrumentID = std::find_if(
      smd_instrumentIDs.begin(), smd_instrumentIDs.end(),
      [instrumentID](std::string v) { return v.compare(instrumentID) == 0; });
  if (found_smd_instrumentID != smd_instrumentIDs.end()) {
    std::cout << "行情 ";
  }

  auto found_sqr_instrumentID = std::find_if(
      sqr_instrumentIDs.begin(), sqr_instrumentIDs.end(),
      [instrumentID](std::string v) { return v.compare(instrumentID) == 0; });
  if (found_sqr_instrumentID != sqr_instrumentIDs.end()) {
    std::cout << "询价";
  }
  std::cout << std::endl;
}

bool CMyCTPMarketQHandler::sqr(const char* instrumentID, bool on) {
  char* instrumentIDs[] = {(char*)instrumentID};
  if (on) {
    _mdApi->SubscribeForQuoteRsp(instrumentIDs, 1);
  } else {
    _mdApi->UnSubscribeForQuoteRsp(instrumentIDs, 1);
  }
  return true;
}

bool CMyCTPMarketQHandler::smd(const char* instrumentID, bool on) {
  char* instrumentIDs[] = {(char*)instrumentID};
  if (on) {
    _mdApi->SubscribeMarketData(instrumentIDs, 1);
  } else {
    _mdApi->UnSubscribeMarketData(instrumentIDs, 1);
  }
  return true;
}

void CMyCTPMarketQHandler::OnFrontConnected() {
  std::cout << std::endl << "（" << _company << "）前置已连接。" << std::endl;

  CThostFtdcReqUserLoginField userLoginField;
  memset(&userLoginField, 0x00, sizeof(CThostFtdcReqUserLoginField));

  strcpy_s(userLoginField.BrokerID, _brokerID.c_str());
  strcpy_s(userLoginField.UserID, _userID.c_str());
  strcpy_s(userLoginField.Password, _password.c_str());
  strcpy_s(userLoginField.UserProductInfo, "CTPMarketQ");

  int ret = _mdApi->ReqUserLogin(&userLoginField, _requestID++);
  std::cout << "（" << _company << "）尝试登入：" << errString(ret)
            << std::endl;
}

void CMyCTPMarketQHandler::OnFrontDisconnected(int nReason) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "前置已断开。（原因：" << reasonString(nReason) << "）"
            << std::endl;
}

void CMyCTPMarketQHandler::OnHeartBeatWarning(int nTimeLapse) {
  std::cout << "（" << _company << "）"
            << "距上一次心跳时间：" << nTimeLapse << "秒。" << std::endl;
}

void CMyCTPMarketQHandler::OnRspUserLogin(
    CThostFtdcRspUserLoginField* pRspUserLogin,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "登入响应：" << pRspInfo->ErrorMsg << "（RequstID："
            << nRequestID << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRspUserLogout(
    CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo,
    int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "登出响应：" << pRspInfo->ErrorMsg << "（RequstID："
            << nRequestID << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRspError(CThostFtdcRspInfoField* pRspInfo,
                                      int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "错误响应：" << pRspInfo->ErrorMsg << "（RequstID："
            << nRequestID << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRspSubMarketData(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "订阅（" << pSpecificInstrument->InstrumentID << "）行情："
            << pRspInfo->ErrorMsg << "（RequstID：" << nRequestID
            << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRspUnSubMarketData(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "取消（" << pSpecificInstrument->InstrumentID << "）行情："
            << pRspInfo->ErrorMsg << "（RequstID：" << nRequestID
            << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRspSubForQuoteRsp(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "订阅（" << pSpecificInstrument->InstrumentID << "）询价："
            << pRspInfo->ErrorMsg << "（RequstID：" << nRequestID
            << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRspUnSubForQuoteRsp(
    CThostFtdcSpecificInstrumentField* pSpecificInstrument,
    CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
  std::cout << std::endl
            << "（" << _company << "）"
            << "取消（" << pSpecificInstrument->InstrumentID << "）询价："
            << pRspInfo->ErrorMsg << "（RequstID：" << nRequestID
            << (bIsLast ? "，最后一次）" : "）") << std::endl;
}

void CMyCTPMarketQHandler::OnRtnDepthMarketData(
    CThostFtdcDepthMarketDataField* pDepthMarketData) {
  std::cout << std::endl
            << "MarketData：" << pDepthMarketData->InstrumentID << std::endl;
};

void CMyCTPMarketQHandler::OnRtnForQuoteRsp(
    CThostFtdcForQuoteRspField* pForQuoteRsp) {
  std::cout << std::endl
            << "Quote：" << pForQuoteRsp->InstrumentID << std::endl;
}
