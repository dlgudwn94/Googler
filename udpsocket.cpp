#include <winsock.h>
#include <stdlib.h>
#include <iostream>
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
	char buf[BUFFER_SIZE] = { '\0', };
	char fileSizeBuf[BUFFER_SIZE] = { '\0', };
	char ReadBuffer[BUFFER_SIZE] = { '\0', };
	char servIP[] = { "127.0.0.1" };

	int cliLen;
	int fileSize = 0;
	int fileNameLen = 0;
	int Readn = 0, Sendton = 0;
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

	if ((fp = _fsopen(fileName, "rb", _SH_DENYNO) == NULL)
	{
		printf("File Pointer Error\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);

	cout << "file size : " << fileSize << "bytes" << endl;

	sprintf_s(fileSizeBuf, MAX_LEN, "%d", fileSize);
	Sendton = sendto(sock, fileSizeBuf, strlen(fileSizeBuf), 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));

	if (Sendton != strlen(fileSizeBuf))
		printf("sendto() sent a different number of bytes than expected\n");

	fseek(fp, 0L, SEEK_SET);
	fileSize = 0;

	while (!feof(fp))
	{
		Readn = fread(buf, sizeof(char), MAX_LEN, fp);
		Sendton = sendto(sock, buf, Readn, 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));

		while (Sendton != Readn)\
		{
			cout << "sendto() sent a different number of bytes than expected" << endl;
			Sendton = sendto(sock, buf, Readn, 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));
		}
		fileSize += Sendton;

		cliLen = sizeof(echoServAddr);

		if ((recvMsgSize = recvfrom(sock, ReadBuffer, MAX_LEN, 0, (struct sockaddr *) & echoServAddr, &cliLen)) <= 0)
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