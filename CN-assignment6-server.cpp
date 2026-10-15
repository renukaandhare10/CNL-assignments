// UDP Uppercase-to-Lowercase Server (Windows)
// Save as: udp_server.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

using namespace std;

class Chat
{
public:
    void sendMessage(SOCKET sockfd, const char message[100],
                     const sockaddr_in& clientAddr, int len)
    {
        sendto(sockfd, message, static_cast<int>(strlen(message)), 0,
               reinterpret_cast<const sockaddr*>(&clientAddr), len);
    }

    void receiveMessage(SOCKET sockfd, char message[100],
                       sockaddr_in& clientAddr, int& len)
    {
        int n = recvfrom(sockfd, message, 99, 0,
                         reinterpret_cast<sockaddr*>(&clientAddr), &len);

        if (n > 0)
            message[n] = '\0';
        else
            message[0] = '\0';
    }
};

int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "\nWinsock initialization failed.";
        return 1;
    }

    SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sockfd == INVALID_SOCKET)
    {
        cout << "\nSocket creation failed.";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{}, clientAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(sockfd, reinterpret_cast<sockaddr*>(&serverAddr),
             sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "\nBind failed.";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "\nUDP server started...";
    cout << "\nWaiting for the client...";

    char buffer[100];
    int len = sizeof(clientAddr);
    Chat c1;

    while (true)
    {
        len = sizeof(clientAddr);
        c1.receiveMessage(sockfd, buffer, clientAddr, len);

        if (buffer[0] == '\0')
        {
            cout << "\nNo message received or client may have sent an empty message.";
            continue;
        }

        cout << "\nClient: " << buffer;

        if (strcmp(buffer, "bye") == 0)
        {
            cout << "\nClient ended communication!";
            break;
        }

        for (int i = 0; buffer[i] != '\0'; i++)
            buffer[i] = static_cast<char>(
                tolower(static_cast<unsigned char>(buffer[i]))
            );

        cout << "\nLowercase message: " << buffer;

        c1.sendMessage(sockfd, buffer, clientAddr, len);
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
