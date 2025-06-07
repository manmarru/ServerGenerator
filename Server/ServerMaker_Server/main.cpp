#include <Windows.h>
#include "Defines.h"
#include <string>
#include "CMySystem.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 10)
	{
		cout << "프로세스 인자 갯수 이상함!" << endl;
		system("pause");
		return 0;
	}

	int Temp = argc;
	SERVERINFO Info;
	Info.UsingHeader = string(argv[2]) == "true"; // 헤더사용여부
	Info.AccessLimit = stoi((string)argv[4]); // 최대접속가능인원
	Info.AlertConnect = string(argv[6]) == "true"; // 접속/해제 알림
	Info.AlertReceive = string(argv[8]) == "true"; // 수신알림
	Info.AlertSend = string(argv[10]) == "true"; // 송신알림

	for (int i = 1; i < Temp; i += 2)
	{
		cout << argv[i] << ": " << argv[i + 1] << endl;
	}

	CMySystem* pMySystem = CMySystem::Create(Info);

	vector<PACKAGE> tReceive;
	vector<HANDLE> hThread;
	vector<SOCKET> hClntSock;
	vector<SOCKADDR_IN> clntAddr;

	WSADATA wadData;
	SOCKET hServSock;
	SOCKADDR_IN servAddr;

	vector<int> szClntAddr;
	char szPackage[1024];



	system("pause");
	pMySystem->Free();

	return 0;
}