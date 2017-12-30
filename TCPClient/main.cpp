#include <stdio.h>
#include <WS2tcpip.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	// init
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("WSAStartup error !");
		return -1;
	}

	// socket
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == INVALID_SOCKET)
	{
		printf("socket error !");
		return -1;
	}

	// connect
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(8888);
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);
	if (connect(client, (sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
	{
		printf("connect error !");
		return -1;
	}

	// send receive
	char sendBuffer[256] = "hello";
	send(client, sendBuffer, strlen(sendBuffer), 0);


	closesocket(client);
	WSACleanup();
}
