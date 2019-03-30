#include <iostream>
#include <ws2tcpip.h>
#include <process.h>
#include <atomic>
#include "header.h"
#include "packet.h"
#include "print.h"
#pragma comment(lib, "ws2_32.lib")
#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)

std::atomic<bool> wait(false);
unsigned int WINAPI input(void *arg) {
	char option;
	while (true) {
		option = getc(stdin);
		switch (option)
		{
		case 'q':
			wait = true;
			return 0;
			break;
		}
	}
	return 0;
}
unsigned int WINAPI sniff(void *param ){
	SOCKET s = (SOCKET)param;
	char *Buffer = new char[65536];
	int pkSize;
	Packets list = Packets();
	printf("패킷 캡쳐중...\n");
	memset(Buffer, 0, 65536);
	Print::printMain();
	
	Print *print = new Print(fopen("log.txt", "w"));
	while (!wait.load())
	{
		pkSize = recvfrom(s, Buffer, 65536, 0, 0, 0);
		if (pkSize > 0)
		{
			Packet *packet = new Packet(Buffer, print, pkSize);
			list.add(packet);
			//packet.getPayload();
			//printf("%s\n", packet.getPayload());
			//system("pause");
			//memset(Buffer, 0, 65536);
		}
		else
			return 1;
	}
	print->close();
	delete print;
	delete[] Buffer;
	return 0;
}
int main() {
	WSADATA wsock;
	SOCKET s;
	struct in_addr addr;
	SOCKADDR_IN dest;
	char host[100], source_ip[20];
	char *Buffer = new char[65536];
	hostent *server;
	int optval, pkSize, i, in;
	char option;
	HANDLE hSockThread = NULL;
	DWORD dwSockThreadID = NULL;

	HANDLE hKeyThread = NULL;
	DWORD dwKeyThreadID = NULL;
	//winsock 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsock) != 0)
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(EXIT_FAILURE);
	}
	//raw sock 생성
	if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_IP)) == SOCKET_ERROR)
	{
		printf("Creation of raw socket failed.");
		return 0;
	}
	//localhost 정보를 가져옴
	if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
	{
		printf("Error : %d", WSAGetLastError());
		return 1;
	}
	printf("호스트 이름: %s", host);
	if ((server = gethostbyname(host)) == 0)
	{
		printf("Unable to resolve.");
		return 0;
	}
	for (int i = 0; server->h_addr_list[i] != 0; ++i)
	{
		memcpy(&addr, server->h_addr_list[i], sizeof(struct in_addr));
		printf("\n인터페이스 번호 : %d 주소 : %s\n", i, inet_ntoa(addr));
	}
	printf("사용할 인터페이스 번호를 입력해주세요 : ");
	scanf("%d", &in);

	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr, server->h_addr_list[in], sizeof(dest.sin_addr.s_addr));
	dest.sin_family = AF_INET;
	dest.sin_port = 0; //your destination port

	if (bind(s, (SOCKADDR*)&dest, sizeof(dest)) == SOCKET_ERROR)
		printf(" bind 실패 ");

	printf("\nBinding successful\n");
	i = 1;
	if (WSAIoctl(s, SIO_RCVALL, &i, sizeof(i), 0, 0, (LPDWORD)&in, 0, 0) == SOCKET_ERROR) {
		printf("WSAIoctl() failed.\n");
		perror("Error:");
		return 1;
	}
	hSockThread = (HANDLE)_beginthreadex(NULL, 0, sniff, (void*)s, 0, (unsigned*)&dwSockThreadID);
	hKeyThread = (HANDLE)_beginthreadex(NULL, 0, input, NULL, 0, (unsigned*)&dwKeyThreadID);

	WaitForSingleObject(hSockThread, INFINITE);

	closesocket(s);
	WSACleanup();
	
	return 0;
}