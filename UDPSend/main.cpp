
#include <stdio.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


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
	SOCKET sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sendSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		return -1;
	}

	// send
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9999);
	inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);

	char send[256] = "hello";
	sendto(sendSocket, send, strlen(send), 0, (sockaddr *)&address, sizeof(address));


	// close
	closesocket(sendSocket);
	WSACleanup();
}
