#pragma once
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