#include <stdio.h> 
#include <winsock.h>
#include <stdlib.h>
#pragma comment(lib, "ws2_32.lib")
#define BUFFER_SIZE (256)

int main() {
	int sock;
	int pNum = 8888;
	char buf[BUFFER_SIZE] = { "hello world" };
	struct sockaddr_in sin;
	WSADATA wsaData;
	char servIP[] = { "127.0.0.1" };

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}
	
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "socket() failed");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(pNum);
	sin.sin_addr.s_addr = inet_addr(servIP);

	if (sendto(sock, buf, strlen(buf) + 1, 0, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
		exit(1);
	}

	closesocket(sock);
	WSACleanup();  /* Cleanup Winsock */
	
	return 0;
}