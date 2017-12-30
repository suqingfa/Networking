#include <stdio.h>
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
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
	{
		printf("socket error !");
		return -1;
	}

	// bind
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(server, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
		return -1;
	}

	// listen
	if (listen(server, 8) == SOCKET_ERROR)
	{
		printf("listen error !");
		return -1;
	}

	// accept
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	SOCKET client = accept(server, (sockaddr *)&remoteAddr, &nAddrlen);
	if (client == INVALID_SOCKET)
	{
		printf("accept error !");
		return -1;
	}

	// send receive
	char buffer[256];
	int ret = recv(client, buffer, sizeof(buffer), 0);
	if (ret > 0)
	{
		buffer[ret] = 0;
		printf("%s \n", buffer);
	}

	closesocket(client);

	closesocket(server);
	WSACleanup();
}
