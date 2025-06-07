#include "CMySystem.h"

CMySystem::CMySystem()
{
}

CMySystem::~CMySystem()
{
}

void CMySystem::Initialize(SERVERINFO _Info)
{
}

void CMySystem::Update()
{
}

void CMySystem::Late_Update()
{
}

CMySystem* CMySystem::Create(SERVERINFO _Info)
{
    CMySystem* Instance = new CMySystem();
    Instance->Initialize(_Info);
    return nullptr;
}

void CMySystem::Free()
{
    delete this;
}
