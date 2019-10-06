#pragma once

void* ZMQ_NewContext();

void* ZMQ_InitPubSocket(void* context, uint16_t port);
int ZMQ_PubSocketSend(void* s, char* msg, size_t len);

void* ZMQ_InitSubSocket(void* context);
int ZMQ_SubSocketConn(void* s, uint16_t port);
int ZMQ_SubSocketFilter(void* s, const char* filter, size_t len, bool on);
int ZMQ_SubSocketRecv(void* s, char* msg, size_t len);
int ZMQ_SubSocketRecvAsync(void* s, char* msg, size_t len);

void ZMQ_CloseSocket(void* s);

void ZMQ_DestroyContext(void* context);
