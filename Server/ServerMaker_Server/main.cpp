#include "Defines.h"
#include "MySystem.h"
#include <process.h>

CMySystem* pMySystem;

unsigned int __stdcall WaitForPlayer(void* pArg)
{
	while (1)
	{
		pMySystem->ConnectUser();
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 13)
	{
		cout << "프로세스 인자 갯수 이상함!" << endl;
		system("pause");
		return 0;
	}

	int Temp = argc;
	SERVERINFO Info;
	// 순서 바꿀거면 조심해야됨!!
	// 제너레이터 쪽에서도 바꿀 때 조심해야됨!!
	Info.AccessLimit = stoi((string)argv[2]); // 최대접속가능인원
	Info.UsingHeader = string(argv[4]) == "true"; // 헤더사용여부
	Info.AlertConnect = string(argv[6]) == "true"; // 접속/해제 알림
	Info.AlertReceive = string(argv[8]) == "true"; // 수신알림
	Info.AlertSend = string(argv[10]) == "true"; // 송신알림
	Info.UserNameInput = string(argv[12]) == "true"; // 유저아이디 입력받음

	for (int i = 1; i < Temp; i += 2)
	{
		cout << argv[i] << ": " << argv[i + 1] << endl;
	}

	pMySystem = CMySystem::Create(Info);
	
	pMySystem->ConnectUser();

	unsigned int ThreadID;
	
	HANDLE ConnectThread;
	ConnectThread = (HANDLE)_beginthreadex(nullptr, 0, WaitForPlayer, nullptr, 0, &ThreadID);
	while (1)
	{
		pMySystem->Update();
	}

	pMySystem->Free();
	
	system("pause");

	return 0;
}

