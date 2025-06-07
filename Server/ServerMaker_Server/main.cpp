#include <Windows.h>
#include "Defines.h"
#include <string>
#include "CMySystem.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 10)
	{
		cout << "���μ��� ���� ���� �̻���!" << endl;
		system("pause");
		return 0;
	}

	int Temp = argc;
	SERVERINFO Info;
	Info.UsingHeader = string(argv[2]) == "true"; // �����뿩��
	Info.AccessLimit = stoi((string)argv[4]); // �ִ����Ӱ����ο�
	Info.AlertConnect = string(argv[6]) == "true"; // ����/���� �˸�
	Info.AlertReceive = string(argv[8]) == "true"; // ���ž˸�
	Info.AlertSend = string(argv[10]) == "true"; // �۽ž˸�

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