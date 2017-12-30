
#include <stdio.h>
#include <winsock2.h>
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
	SOCKET receiveSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (receiveSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		return -1;
	}

	// bind
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(9999);
	address.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(receiveSocket, (sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
	{
		printf("bind error !");
		return -1;
	}

	// receive
	char buffer[256] = { 0 };
	sockaddr_in remoteAddr;
	int nAddrLen = sizeof(remoteAddr);
	int ret = recvfrom(receiveSocket, buffer, sizeof(buffer) - 1, 0, (sockaddr *)&remoteAddr, &nAddrLen);
	if (ret > 0)
	{
		printf("receive length: %d \n", ret);
		buffer[ret] = 0;
		printf("%s", buffer);
	}

	// close
	closesocket(receiveSocket);
	WSACleanup();
}
