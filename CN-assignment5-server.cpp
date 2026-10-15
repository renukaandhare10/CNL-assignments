// TCP Chat Server (Windows)
// Save as: server.cpp

#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 8080

using namespace std;

class Chat
{
public:
    void sendMessage(SOCKET sockfd, const char message[100])
    {
        send(sockfd, message, static_cast<int>(strlen(message)), 0);
    }

    void receiveMessage(SOCKET sockfd, char message[100])
    {
        int n = recv(sockfd, message, 99, 0);

        if (n > 0)
        {
            message[n] = '\0';
        }
        else
        {
            message[0] = '\0';
        }
    }
};

int main()
{
    // Step 1: Initialize Winsock.
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cout << "\nWinsock initialization failed.";
        return 1;
    }

    // Step 2: Create a TCP socket.
    SOCKET sockfd, connfd;
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sockfd == INVALID_SOCKET)
    {
        cout << "\nSocket creation failed.";
        WSACleanup();
        return 1;
    }

    // Step 3: Declare server and client addresses.
    sockaddr_in serverAddr{}, clientAddr{};

    // Step 4: Configure the server IP address and port.
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Step 5: Bind the socket to the IP address and port.
    if (bind(sockfd, reinterpret_cast<sockaddr*>(&serverAddr),
             sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "\nBind failed.";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    // Step 6: Listen for client connections.
    if (listen(sockfd, 5) == SOCKET_ERROR)
    {
        cout << "\nListen failed.";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "\nServer started...";
    cout << "\nWaiting for the client...";

    // Step 7: Accept a client connection.
    int len = sizeof(clientAddr);
    connfd = accept(sockfd, reinterpret_cast<sockaddr*>(&clientAddr), &len);

    if (connfd == INVALID_SOCKET)
    {
        cout << "\nAccept failed.";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "\nClient connected!";

    // Step 8: Chat.
    char buffer[100];
    Chat c1;

    while (true)
    {
        c1.receiveMessage(connfd, buffer);

        if (buffer[0] == '\0')
        {
            cout << "\nClient disconnected.";
            break;
        }

        cout << "\nClient: " << buffer;

        if (strcmp("bye", buffer) == 0)
        {
            cout << "\nClient ended communication!";
            break;
        }

        cout << "\nServer: ";
        cin.getline(buffer, 100);
        c1.sendMessage(connfd, buffer);

        if (strcmp(buffer, "bye") == 0)
        {
            cout << "\nServer ended the communication!";
            break;
        }
    }

    // Step 9: Close sockets and clean up Winsock.
    closesocket(connfd);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
