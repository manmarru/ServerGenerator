#pragma once
#include <vector>
#include <iostream>

struct PACKAGE
{
	char szID;
	int iType;
	char Data[1024];
};

struct SERVERINFO
{
	bool UsingHeader;
	int AccessLimit;
	bool AlertConnect;
	bool AlertReceive;
	bool AlertSend;
};