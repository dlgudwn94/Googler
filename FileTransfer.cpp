#include "FileTransfer.h"

FileTransfer::FileTransfer(char *fileName, char *servIP)
{
	
	memset(buf, '\0', sizeof(buf));
	memset(fileSizeBuf, '\0', sizeof(fileSizeBuf));
	memset(readBuffer, '\0', sizeof(readBuffer));

	this->fileName = fileName;
	this->servIP = servIP;
	
	cout << "file name: "<<fileName << endl;
	cout << "servIP: " << servIP << endl;

	this->fileSize = 0;
	this->fileNameLen = 0;
	this->readn = 0;
	this->sendton = 0;
	this->recvMsgSize = 0;
	this->fileNameLen = strlen(this->fileName) + 1;
	this->echoServPort = atoi("8888");
}

FileTransfer::~FileTransfer()
{
	cout << "Transfer terminate! (File Size = " << fileSize << ")" << endl;
	fclose(fp);
	WSACleanup();
	exit(0);
}

int FileTransfer::setFileName(char *fileName)
{
	this->fileName = fileName;

	return 0;
}

int  FileTransfer::setServIP(char *servIP)
{
	this->servIP = servIP;

	return 0;
}

void FileTransfer::IsStartup()
{
	if (WSAStartup(MAKEWORD(2, 0), &wasData) != 0)
	{
		fprintf(stderr, "WSAStartup() failed");
		fclose(fp);
		WSACleanup();
		exit(1);
	}
}

void FileTransfer::IsSocket()
{
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		cout << "socket() failed" << endl;
		fclose(fp);
		WSACleanup();
		exit(1);
	}
}

void FileTransfer::ClientStart()
{
	cout << "UDP Client Start!" << endl;
	cout << "file name : " << fileName << endl;

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	this->fp = _fsopen(fileName, "rb", _SH_DENYNO);

	if (fp == NULL)
	{
		cout << "File pointer error" << endl;
		WSACleanup();
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	this->fileSize = ftell(fp);
	
	cout << "File size : " << fileSize << "bytes"<< endl;
	sprintf_s(fileSizeBuf, BUFF_SIZE, "%d", fileSize);

	sendton = sendto(sock, fileSizeBuf, strlen(fileSizeBuf), 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr));

	if (sendton != strlen(fileSizeBuf))
		cout << "sendto() sent a different number of bytes than expected1" << endl;
}

void FileTransfer::StartTransfer()
{
	fseek(fp, 0L, SEEK_SET);
	cout << "Start file transfer!" << endl;
	fileSize = 0;

	while (!feof(fp))
	{
		readn = fread(buf, sizeof(char), BUFF_SIZE, fp);
		sendton = sendto(sock, buf, readn, 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr));

		while (sendton != readn)
		{
			cout << "sendto() sent a different number of bytes than expected2" << endl;
			sendton = sendto(sock, buf, readn, 0, (struct sockaddr*)&echoServAddr, sizeof(echoServAddr));
		}
		
		fileSize += sendton;

		cliLen = sizeof(echoServAddr);

		if (recvMsgSize = recvfrom(sock, readBuffer, BUFF_SIZE, 0, (struct sockaddr*)&echoServAddr,&cliLen)<=0)
		{
			cout << "Error" << endl;
			break;
		}
	}
}
