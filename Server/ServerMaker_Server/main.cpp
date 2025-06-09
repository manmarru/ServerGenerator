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
		cout << "���μ��� ���� ���� �̻���!" << endl;
		system("pause");
		return 0;
	}

	int Temp = argc;
	SERVERINFO Info;
	// ���� �ٲܰŸ� �����ؾߵ�!!
	// ���ʷ����� �ʿ����� �ٲ� �� �����ؾߵ�!!
	Info.AccessLimit = stoi((string)argv[2]); // �ִ����Ӱ����ο�
	Info.UsingHeader = string(argv[4]) == "true"; // �����뿩��
	Info.AlertConnect = string(argv[6]) == "true"; // ����/���� �˸�
	Info.AlertReceive = string(argv[8]) == "true"; // ���ž˸�
	Info.AlertSend = string(argv[10]) == "true"; // �۽ž˸�
	Info.UserNameInput = string(argv[12]) == "true"; // �������̵� �Է¹���

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

