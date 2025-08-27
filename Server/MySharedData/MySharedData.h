#pragma once
#include <string>

using namespace std;

struct USERNAME
{
	char Name[128];
};

struct PACKETHEADER
{
	unsigned int size;
};

struct PACKAGE
{
	int ID;
	char Data[1024];
};

struct NAME_PACKAGE
{
	char UserName[128];
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