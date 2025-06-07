#pragma once
#include "Defines.h"

class CMySystem
{
private:
	CMySystem();
	~CMySystem();

public:
	void Initialize(SERVERINFO _Info);
	void Update();
	void Late_Update();

public:
	static CMySystem* Create(SERVERINFO _Info);
	void Free();
};

