#include <iostream>
#include <winsock.h>
#include <stdlib.h>
#include <share.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")
#define BUFFER_SIZE (1024)

int main()
{
	int sock;
	int pNum=8888;
	FILE* fp;
	struct sockaddr_in sin;
	char fileName[BUFFER_SIZE] = { "test.txt" };
	char buf[BUFFER_SIZE] = { '\0' };
	char fileSizeBuf[BUFFER_SIZE] = { '\0' };
	char readBuffer[BUFFER_SIZE] = { '\0' };
	char servIP[] = { "127.0.0.1" };

	int cliLen;
	int fileSize = 0;
	int fileNameLen = 0;
	int readn = 0, sendton = 0;
	int recvMsgSize = 0;
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}
	
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		fprintf(stderr, "socket() failed");
		exit(1);
	}

	fileNameLen = strlen(fileName) + 1;

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(pNum);
	sin.sin_addr.s_addr = inet_addr(servIP);
	
	fp = _fsopen(fileName, "rb", _SH_DENYNO);
	
	if (fp == NULL)
	{
		cout << "File Pointer Error" << endl;
		exit(1);
	}
	
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	cout << "file size : " << fileSize << "bytes" << endl;

	sprintf_s(fileSizeBuf, BUFFER_SIZE, "%d", fileSize);
	sendton = sendto(sock, fileSizeBuf, strlen(fileSizeBuf), 0, (struct sockaddr *)&sin, sizeof(sin));

	if (sendton != strlen(fileSizeBuf))
		cout << "sendto() sent a different number of bytes than expected" << endl;

	fseek(fp, 0L, SEEK_SET);
	fileSize = 0;

	while (!feof(fp))
	{
		readn = fread(buf, sizeof(char), BUFFER_SIZE, fp);
		sendton = sendto(sock, buf, readn, 0, (struct sockaddr *)&sin, sizeof(sin));

		while (sendton != readn)
		{
			cout << "sendto() sent a different number of bytes than expected" << endl;
			sendton = sendto(sock, buf, readn, 0, (struct sockaddr *)&sin, sizeof(sin));
		}
		fileSize += sendton;

		cliLen = sizeof(sin);

		if ((recvMsgSize = recvfrom(sock, readBuffer, BUFFER_SIZE, 0, (struct sockaddr *) & sin, &cliLen)) <= 0)
		{
			cout << "Error" << endl;
			break;
		}
	}

	fclose(fp);
	closesocket(sock);
	WSACleanup();
	return 0;
}