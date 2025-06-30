//
// Created by rodri on 28/06/2025.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include "ports.h"

#pragma comment(lib, "Ws2_32.lib")

// Thread function for handling individual clients
DWORD WINAPI handle_client(LPVOID client_socket) {
    SOCKET sock = *(SOCKET *)client_socket;
    char buffer[1024];
    int bytes_received;

    printf("[+] New client connected. Socket: %d\n", (int)sock);

    while ((bytes_received = recv(sock, buffer, sizeof(buffer) -1,0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("[CLIENT %d] %s\n",(int)sock, buffer);

        const char *response = "Message received successfully!\n";
        send(sock, response, strlen(response), 0);
    }

    printf("[-] Client disconnected. Socket: %d\n", (int)sock);
    closesocket(sock);
    free(client_socket);
    return 0;
}

//main server function
void open_door() {
    WSADATA wsa;
    SOCKET server_socket, *new_sock;
    struct sockaddr_in server_address; //address server (bind)
    struct sockaddr_in client_address; //address client (accept)
    int client_len;
    int port;

    printf("Enter port to listen on: ");
    scanf("%d", &port);

    printf("[*] Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("[-] Winsock initialization failed. Code: %d\n", WSAGetLastError());
        return;
    }
    printf("[+] Winsock initialized successfully.\n");

    //create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("[-] Socket creation failed. Code: %d\n", WSAGetLastError());
        WSACleanup();
        return;
    }
    printf("[+] Socket created successfully.\n");

    //configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    //bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("[-] Bind failed. Code: %d\n", WSAGetLastError());
        closesocket(server_socket);
        WSACleanup();
        return;
    }
    printf("[+] Bind successfully. Listening on port %d\n", port);

    //start listening
    listen(server_socket, 5);
    printf("[*] Waiting for incoming connections...\n");

    client_len = sizeof(client_address);
    while ((new_sock = malloc(sizeof(SOCKET))) &&
        (*new_sock = accept(server_socket, (struct sockaddr *)&client_address, &client_len)) != INVALID_SOCKET) {
    printf("[+] Connection accepted from %s:%d\n",
        inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

        //create a new thread for each client
        CreateThread(NULL, 0, handle_client, (void *)new_sock, 0, NULL);
    }

    if (*new_sock == INVALID_SOCKET) {
        printf("[-] Accept failed. Code: %d\n", WSAGetLastError());
    }

    closesocket(server_socket);
    WSACleanup();

}

void close_door() {
    printf("[*] close_door() not implemented yet.\n");
}
