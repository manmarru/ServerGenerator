#pragma once
#include "Defines.h"
#include <process.h>
#include "MySystem.h"


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
    FD_ZERO(&m_Reads);

#pragma region �غ�
    if(WSAStartup(MAKEWORD(2, 2), &m_wsaData)  != 0)
    {
        cout << "WSASTARTUP ����!" << endl;
    }
    m_hServSock = socket(PF_INET, SOCK_STREAM, 0);
    if(m_hServSock == INVALID_SOCKET)
    {
        cout << "���� ���� ����!" << endl;
    }

    memset(&m_ServAddr, 0, sizeof(m_ServAddr));
    m_ServAddr.sin_family = AF_INET;
    m_ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_ServAddr.sin_port = htons(8000);
#pragma endregion

    if (bind(m_hServSock, (SOCKADDR*)&m_ServAddr, sizeof(m_ServAddr)) == SOCKET_ERROR)
    {
        cout << "���ε� ����!" << endl;
    }

    if (listen(m_hServSock, SOMAXCONN) == SOCKET_ERROR) // SOMAXCONN��ŭ ��� ���� (������ ��õ ����)
        cout << "���� ����!" << endl;
    cout << "�غ� ��" << endl;

    return RESULT_SUCCESS;
}

void CMySystem::Update()
{
    PACKAGE Recv;
    m_Temps = m_Reads;
    
    if (0 == m_CurrUser)
        return;
    
    if (select(0, &m_Temps, 0, 0, 0) == SOCKET_ERROR)
        cout << "select ����!\n";
    
    SOCKET Curr;
    for (int i = 0; i < m_Temps.fd_count; ++i)
    {
        Curr = m_Temps.fd_array[i];
        if (FD_ISSET(Curr, &m_Temps))
        {
            int len = recv(Curr, (char*)&Recv.Data, sizeof(Recv.Data), 0);
            if (len <= 0)
            {
                cout << "recv ���� �Ǵ� ���� ����!\n";
                closesocket(Curr);
                FD_CLR(Curr, &m_Reads);
                continue;
            }
            if (!strcmp(Recv.Data, "-1"))
            {
                cout << "���� ���� ���� �߻�\n";
                closesocket(Curr);
                FD_CLR(Curr, &m_Reads);
                --m_CurrUser;
                continue;
            }
            cout << Recv.Data << '\n';
            SendToAll((char*)Recv.Data, sizeof(Recv.Data));
        }
    }
}

void CMySystem::Release()
{
    WSACleanup();
    for (auto& sock : m_hClntSock)
    {
        if (sock != INVALID_SOCKET)
            closesocket(sock);
    }
    closesocket(m_hServSock);
    cout << "WSACleanup, ���� ����\n";
}

int CMySystem::Recv_N_Send()
{
    return 0;
}

void CMySystem::SendToAll(char* Send, int SendSize)
{
    for (int i = 0; i < m_CurrUser; ++i)
    {
        send(m_hClntSock[i], Send, sizeof(SendSize), 0);
    }
}

unsigned int APIENTRY CMySystem::ConnectUser()
{
    cout << "���� ���� �����..." << endl;
    //����
    m_szClntAddr[m_CurrUser] = sizeof(m_ClntAddr[m_CurrUser]);
    m_hClntSock[m_CurrUser] = accept(m_hServSock, (SOCKADDR*)&m_ClntAddr[m_CurrUser], &m_szClntAddr[m_CurrUser]);
    cout << "���� ��û�� �Ծ��!" << endl;
    if (m_hClntSock[m_CurrUser] == INVALID_SOCKET)
        cout << m_CurrUser << " ���� ���� ����" << endl;
    else
    {
        cout << "���ἳ��!" << endl;
        FD_SET(m_hClntSock[m_CurrUser], &m_Reads);
    }


    if (m_tInfo.UserNameInput)
    {
        USERNAME Temp;
        //���� �г��� �޾Ƽ� map�� ����
        if (recv(m_hClntSock[m_CurrUser], (char*)&Temp, sizeof(USERNAME), 0) <= 0)
            cout << "���� ����!" << endl;
        m_UserNames[m_CurrUser] = string(Temp.Name);
        cout << "���̵�: " << m_UserNames[m_CurrUser] << endl;
    }

    ++m_CurrUser;

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
