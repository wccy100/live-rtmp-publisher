#ifndef _PACKET_QUEUE_H_
#define _PACKET_QUEUE_H_

#include <cstring>
#include <mutex>
#include <condition_variable>
#include <librtmp/rtmp.h>
#include "RTMPPackager.h"

struct PacketNode {
    RTMPPacket packet;
    char *buf;
};

// single consumer !!!

class PacketQueue {
public:
    PacketQueue(int capacity = 100, int size = 32768);

    ~PacketQueue();

    void push(RTMPPackager& packager);

    void push(const RTMPPacket& packet);

    void pop();

    RTMPPacket& front();
private:
    PacketNode *mDataBuf;
    std::mutex mMutex;
    std::condition_variable mFull;
    std::condition_variable mEmpty;
    int mHead;
    int mTail;
    int mCapacity;
};

#endif