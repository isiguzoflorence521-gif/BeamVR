#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5005
#define MAX_PACKET_SIZE 65507 

namespace BeamVR {
    class WindowsReceiver {
        SOCKET sock;
        struct sockaddr_in recv_addr;

    public:
        bool Initialize() {
            WSADATA wsa;
            if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;

            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (sock == INVALID_SOCKET) return false;

            recv_addr.sin_family = AF_INET;
            recv_addr.sin_port = htons(PORT);
            recv_addr.sin_addr.s_addr = INADDR_ANY;

            if (bind(sock, (struct sockaddr*)&recv_addr, sizeof(recv_addr)) == SOCKET_ERROR) {
                return false;
            }

            std::cout << "[BeamVR] Windows Receiver listening on port " << PORT << "..." << std::endl;
            return true;
        }

        void Listen() {
            std::vector<uint8_t> buffer(MAX_PACKET_SIZE);
            struct sockaddr_in sender_addr;
            int sender_len = sizeof(sender_addr);

            while (true) {
                int bytes_received = recvfrom(sock, (char*)buffer.data(), MAX_PACKET_SIZE, 0, 
                                              (struct sockaddr*)&sender_addr, &sender_len);
                
                if (bytes_received > 0) {
                    // Logic: Send buffer to H.264 Decoder (FFmpeg) or Graphics API
                    std::cout << "[BeamVR] Received frame chunk: " << bytes_received << " bytes" << std::endl;
                }
            }
        }

        ~WindowsReceiver() {
            closesocket(sock);
            WSACleanup();
        }
    };
}

int main() {
    BeamVR::WindowsReceiver receiver;
    if (receiver.Initialize()) {
        receiver.Listen();
    }
    return 0;
}
