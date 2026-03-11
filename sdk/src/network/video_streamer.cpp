#include <iostream>
#include <winsock2.h>

#define CHUNK_SIZE 1400 // Stay under MTU to avoid fragmentation

void StreamVideoPacket(const uint8_t* frameData, size_t frameSize, SOCKET sock, sockaddr_in& target) {
    size_t sent = 0;
    while (sent < frameSize) {
        size_t toSend = std::min((size_t)CHUNK_SIZE, frameSize - sent);
        sendto(sock, (const char*)(frameData + sent), toSend, 0, (struct sockaddr*)&target, sizeof(target));
        sent += toSend;
    }
}
