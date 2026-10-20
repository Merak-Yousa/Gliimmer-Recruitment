#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

DWORD WINAPI thread_func(LPVOID lpThreadParameter) {
    SOCKET client_socket = *(SOCKET*)lpThreadParameter;
    free(lpThreadParameter);

    while (1) {

        char buffer[1024] = { 0 };
        int ret = recv(client_socket, buffer, 1024, 0);
        if (ret <= 0) break;

        printf("%s\n", buffer);

        send(client_socket, buffer, (int)strlen(buffer), 0);
        
    }
    return 0;
}

int main() {

    //Windows上使用网络功能,开始网络权限
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建socket套接字
    SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == listen_socket) {
        printf("create listen socket failed ! errcode: %d\n",WSAGetLastError());
        return -1;
    }

    //给socket绑定端口号
    struct sockaddr_in local = { 0 };
    local.sin_family = AF_INET;
    local.sin_port = htons(8080); 
    local.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (-1 == bind(listen_socket, (struct sockaddr*)&local, sizeof(local))) {
        printf("bind socket failed ! errcode: %d\n", WSAGetLastError());
        return -1;
    }

    //给socket开启监听属性
    if (-1 == listen(listen_socket, 10)) {
        printf("start listen failed ! errcode: %d\n", WSAGetLastError());
        return -1;
    }

    //等待客户端连接
    while (1)
    {
        SOCKET client_socket = accept(listen_socket, NULL, NULL);
        if (INVALID_SOCKET == client_socket)
            continue;

        SOCKET* sockfd = (SOCKET*)malloc(sizeof(SOCKET));
        *sockfd = client_socket;

        //进入线程
        CreateThread(NULL, 0, thread_func, sockfd, 0, NULL);
        //开始通讯
    }
    return 0;
}