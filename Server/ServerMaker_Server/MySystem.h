#pragma once
#include "Defines.h"

enum RESULT { RESULT_FAILED, RESULT_SUCCESS, RESULT_END };

class CMySystem
{
private:
	CMySystem();
	~CMySystem();

public:
	RESULT Initialize(SERVERINFO _Info);
	void Update();
	void Release();

public:
	int Recv_N_Send();
	void SendToAll(char* Send, int SendSize);
public:
	unsigned int APIENTRY ConnectUser();
	void WaitForPlayer();

private:
	SOCKET m_hServSock;
	SOCKADDR_IN m_ServAddr;
	fd_set m_Reads;
	fd_set m_Temps;

private:
	vector<SOCKET> m_hClntSock;
	vector<SOCKADDR_IN> m_ClntAddr;
	vector<int> m_szClntAddr;
	vector<string> m_UserNames;

private:
	int m_CurrUser{ 0 };
	WSADATA m_wsaData;
	HANDLE m_hThread[2];
	char szPackage[1024];
	PACKAGE m_tReceive;

private:
	SERVERINFO m_tInfo;

public:
	static CMySystem* Create(SERVERINFO _Info);
	void Free();
};

