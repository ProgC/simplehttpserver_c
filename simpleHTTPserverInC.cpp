// Run this server and type 'localhost:15890' in the webbrowser then you will see 'Hello World'

#include "stdafx.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

WSADATA wsaData;

//#define DEFAULT_PORT "8080"
#define DEFAULT_PORT "15890"

int _tmain(int argc, _TCHAR* argv[])
{

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) return 1;

	struct addrinfo *result = nullptr, hints;
		
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;		
	hints.ai_flags = AI_PASSIVE;
	
	getaddrinfo(nullptr, DEFAULT_PORT, &hints, &result);
	SOCKET listenSocket = INVALID_SOCKET;

	listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	bind(listenSocket, result->ai_addr, (int)result->ai_addrlen);
		
	SOCKET clientSocket;
	while (1)
	{
		if (listen(listenSocket, 10) < 0)
		{
			return 1;
		}
		
		clientSocket = accept(listenSocket, nullptr, nullptr);

		if (clientSocket > 0)
		{
			printf("client is connected\n");
		}
				
		send(clientSocket, "HTTP/1.1 200 OK\n", 16,0);
		send(clientSocket, "Content-length: 46\n", 19, 0);
		send(clientSocket, "Content-Type: text/html\n\n", 25, 0);
		send(clientSocket, "<html><body><H1>Hello world</H1></body></html>", 46, 0);

		closesocket(clientSocket);
	}

	closesocket(listenSocket);
	return 0;
}

