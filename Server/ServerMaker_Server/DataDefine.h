#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

struct USERNAME
{
	char Name[256];
};

struct PACKAGE
{
	int ID;
	int Type;
	char Data[1024];
};

struct SERVERINFO
{
	bool UsingHeader;
	int AccessLimit;
	bool AlertConnect;
	bool AlertReceive;
	bool AlertSend;
	bool UserNameInput;
};