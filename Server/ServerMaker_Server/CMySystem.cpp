#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "Defines.h"
#include <process.h>
#include "CMySystem.h"


CMySystem::CMySystem()
{
}

CMySystem::~CMySystem()
{
}

RESULT CMySystem::Initialize(SERVERINFO _Info)
{
    m_tInfo = _Info;


    m_szClntAddr.resize(m_tInfo.AccessLimit);
    m_ClntAddr.resize(m_tInfo.AccessLimit);
    m_hClntSock.resize(m_tInfo.AccessLimit);
    m_UserNames.resize(m_tInfo.AccessLimit);

#pragma region �غ�
    WSAStartup(MAKEWORD(2, 2), &m_wsaData);
    m_hServSock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&m_ServAddr, 0, sizeof(m_ServAddr));
    m_ServAddr.sin_family = AF_INET;
    m_ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_ServAddr.sin_port = htons(8000);
#pragma endregion
    bind(m_hServSock, (SOCKADDR*)&m_ServAddr, sizeof(m_ServAddr));
    cout << "�غ� ��" << endl;

    return RESULT_SUCCESS;
}

void CMySystem::Update()
{
}

void CMySystem::Late_Update()
{
}

void CMySystem::Release()
{
    WSACleanup();
    cout << "WSACleanup\n";
}

int CMySystem::Recv_N_Send()
{
    return 0;
}

unsigned int APIENTRY CMySystem::ConnectUser()
{
    listen(m_hServSock, SOMAXCONN); // SOMAXCONN��ŭ ��� ���� (������ ��õ ����)
    //����
    m_szClntAddr[m_CurrUser] = sizeof(m_ClntAddr[m_CurrUser]);
    m_hClntSock[m_CurrUser] = accept(m_hServSock, (SOCKADDR*)&m_ClntAddr[m_CurrUser], &m_szClntAddr[m_CurrUser]);
    if (m_hClntSock[m_CurrUser] == INVALID_SOCKET)
        cout << m_CurrUser << " ���� ���� ����" << endl;
    else
        cout << "���ἳ��!" << endl;

    ++m_CurrUser;

    if (m_tInfo.UserNameInput)
    {
        USERNAME Temp;
        //���� �г��� �޾Ƽ� map�� ����
        if (recv(m_hClntSock[m_CurrUser], (char*)&Temp, sizeof(USERNAME), 0) < 0)
            cout << "���� ����!" << endl;
        m_UserNames[m_CurrUser] = string(Temp.Name);
		cout << "���̵�: " << m_UserNames[m_CurrUser];
    }

    return 0;
}

void CMySystem::WaitForPlayer()
{
    while (m_CurrUser <= m_tInfo.AccessLimit)
    {
        ConnectUser();
    }
}

CMySystem* CMySystem::Create(SERVERINFO _Info)
{
    CMySystem* Instance = new CMySystem();
    if (Instance->Initialize(_Info) == RESULT_FAILED)
        return nullptr;
    return Instance;
}

void CMySystem::Free()
{
    Release();
    delete this;
}
