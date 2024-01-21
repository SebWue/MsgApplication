
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <Windows.h>
#include "server.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;
WSADATA wsaData;


int server::startup()
{
    int iResult;

    //-------------------------------------------------
    // Selecting the WSA Version and fill out wsaData |
    //-------------------------------------------------
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }
    else {
        cout << "Winsock dll found!" << endl;
        cout << "The Status: " << wsaData.szSystemStatus << endl;
    }

    //----------------------
    // Setting up a Socket |
    //----------------------
    SOCKET serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        printf("socket() is OK! \n");
    }

    //-----------------------------------------
    // Setting all the Ports and IP addresses |
    //-----------------------------------------
    int port = 12341;
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("168.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);

    //------------------------------------------------
    // Binding the Socket to the Port and IP address |
    //------------------------------------------------
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        printf("bind() is OK!\n");
    }


    closesocket(serverSocket);

    WSACleanup();
}

