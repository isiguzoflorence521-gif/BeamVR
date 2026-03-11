#include <iostream>
#include <string>
#include <cstring>

#if defined(_WIN32)
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

namespace BeamVR {
    class UDPSender {
        int sock;
        struct sockaddr_in server_addr;

    public:
        bool Init(const char* ip, int port) {
#if defined(_WIN32)
            WSADATA wsa;
            WSAStartup(MAKEWORD(2,2), &wsa);
#endif
            sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (sock < 0) return false;

            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(port);
            inet_pton(AF_INET, ip, &server_addr.sin_addr);
            
            return true;
        }

        void Send(const uint8_t* data, int sz) {
            sendto(sock, (const char*)data, sz, 0, 
                   (struct sockaddr*)&server_addr, sizeof(server_addr));
        }

        ~UDPSender() {
#if defined(_WIN32)
            closesocket(sock);
            WSACleanup();
#else
            close(sock);
#endif
        }
    };
}
