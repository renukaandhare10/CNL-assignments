// TCP Chat Client (Windows)
// Save as: client.cpp

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
    SOCKET sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sockfd == INVALID_SOCKET)
    {
        cout << "\nSocket creation failed.";
        WSACleanup();
        return 1;
    }

    // Step 3: Declare the server address.
    sockaddr_in serverAddr{};

    // Step 4: Configure the server IP address and port.
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Replace with the server's IP for another computer.
    serverAddr.sin_port = htons(PORT);

    // Step 5: Connect to the server.
    if (connect(sockfd, reinterpret_cast<sockaddr*>(&serverAddr),
                sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "\nConnection failed. Check that the server is running and the IP is correct.";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "\nConnected to the server!";

    // Step 6: Chat.
    char buffer[100];
    Chat c1;

    while (true)
    {
        cout << "\nClient: ";
        cin.getline(buffer, 100);

        c1.sendMessage(sockfd, buffer);

        if (strcmp(buffer, "bye") == 0)
        {
            cout << "\nClient ended the communication!";
            break;
        }

        c1.receiveMessage(sockfd, buffer);

        if (buffer[0] == '\0')
        {
            cout << "\nServer disconnected.";
            break;
        }

        cout << "\nServer: " << buffer;

        if (strcmp(buffer, "bye") == 0)
        {
            cout << "\nServer ended communication!";
            break;
        }
    }

    // Step 7: Close the socket and clean up Winsock.
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
