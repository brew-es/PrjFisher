#include "../ZeroMQ/include/zmq.h"

#include "ZMQHelper.h"

#pragma comment(lib, "../ZeroMQ/lib/libzmq-v142-mt-4_3_3.lib")

void* ZMQ_NewContext() {
	return zmq_ctx_new();
}

void* ZMQ_InitPubSocket(void* context, uint16_t port) {
	void* ret = nullptr;
	char addr_buf[128] = "";
	sprintf_s(addr_buf, 128, "tcp://*:%d", port);
	ret = zmq_socket(context, ZMQ_PUB);
	zmq_bind(ret, addr_buf);
	return ret;
}

int ZMQ_PubSocketSend(void* s, char* msg, size_t len) {
	int ret = 0;
	ret = zmq_send(s, msg, len, 0);
	return ret;
};

void* ZMQ_InitSubSocket(void* context) {
	void* ret = nullptr;
	ret = zmq_socket(context, ZMQ_SUB);
	zmq_setsockopt(ret, ZMQ_SUBSCRIBE, NULL, 0);
	return ret;
}

int ZMQ_SubSocketConn(void* s, uint16_t port) {
	int ret = 0;
	char addr_buf[128] = "";
	sprintf_s(addr_buf, 128, "tcp://127.0.0.1:%d", port);
	ret = zmq_connect(s, addr_buf);
	return ret;
}

int ZMQ_SubSocketFilter(void* s, const char* filter, size_t len, bool on) {
  int ret = 0;
  if (on) {
    ret = zmq_setsockopt(s, ZMQ_SUBSCRIBE, filter, len);
  } else {
    ret = zmq_setsockopt(s, ZMQ_UNSUBSCRIBE, filter, len);
  }
  return ret;
}

int ZMQ_SubSocketRecv(void* s, char* msg, size_t len) {
	int ret = 0;
	ret = zmq_recv(s, msg, len, 0);
	return ret;
};

void ZMQ_CloseSocket(void* s) {
	zmq_close(s);
}

void ZMQ_DestroyContext(void* context) {
	zmq_ctx_destroy(context);
}