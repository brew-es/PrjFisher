#pragma once

#ifdef _DEBUG
#define MAX_COMPANIES_OF_FUTURES 4 // 最后一个配置是7*24的行情测试服务器
#else
#define MAX_COMPANIES_OF_FUTURES 3
#endif  // _DEBUG

#define MAX_FRONT_NUM	8

class CMyCTPMarketQHandler : public CThostFtdcMdSpi {
 public:
  CMyCTPMarketQHandler(std::string company, std::string brokerID,
                       std::string flowPath, bool usingUDP, bool isMulticast,
                       std::string userID, std::string password,
                       std::string front[MAX_FRONT_NUM]);
  virtual ~CMyCTPMarketQHandler();

 public:
  static CMyCTPMarketQHandler *Handler(uint8_t handlerIndex);

  static uint8_t Start(const char *confile);
  static bool IsRunning();
  static void Stop();
  static bool SQR(const char *instrumentID, bool on);
  static bool SMD(const char *instrumentID, bool on);
  static void List(const char *instrumentID);

 public:
  bool sqr(const char *instrumentID, bool on);
  bool smd(const char *instrumentID, bool on);

 private:
  virtual void OnFrontConnected();
  virtual void OnFrontDisconnected(int nReason);

  virtual void OnHeartBeatWarning(int nTimeLapse);

  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                              CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                              bool bIsLast);
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                               CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                               bool bIsLast);

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                          bool bIsLast);

  virtual void OnRspSubMarketData(
      CThostFtdcSpecificInstrumentField *pSpecificInstrument,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUnSubMarketData(
      CThostFtdcSpecificInstrumentField *pSpecificInstrument,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRspSubForQuoteRsp(
      CThostFtdcSpecificInstrumentField *pSpecificInstrument,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
  virtual void OnRspUnSubForQuoteRsp(
      CThostFtdcSpecificInstrumentField *pSpecificInstrument,
      CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

  virtual void OnRtnDepthMarketData(
      CThostFtdcDepthMarketDataField *pDepthMarketData);
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

 private:
  std::string _company;
  std::string _brokerID;
  std::string _flowPath;
  bool _usingUDP;
  bool _isMulticast;
  std::string _front[MAX_FRONT_NUM];

  std::string _userID;
  std::string _password;

  int _requestID;
  CThostFtdcMdApi *_mdApi;
};
