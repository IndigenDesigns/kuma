#ifndef __AutoHelper_H__
#define __AutoHelper_H__

#include "kmapi.h"
#include "TestLoop.h"
#include "../../third_party/libkev/src/util/DestroyDetector.h"

#include <map>

using namespace kuma;

class ProtoDemuxer : public TestObject, public kev::DestroyDetector
{
public:
    ProtoDemuxer(TestLoop* loop, long conn_id);
    ~ProtoDemuxer();

    KMError attachFd(SOCKET_FD fd, uint32_t ssl_flags);
    int close();
    
    void onSend(KMError err);
    void onReceive(KMError err);
    void onClose(KMError err);
    
    void onHttpData(KMBuffer &buf);
    void onHttpEvent(HttpEvent ev);
    
private:
    void cleanup();
    bool checkHttp2();
    void demuxHttp(const KMBuffer *init_buf);
    
private:
    TestLoop*       loop_;
    long            conn_id_;
    
    TcpSocket       tcp_;
    HttpParser      http_parser_;
};

#endif
