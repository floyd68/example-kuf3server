// RXTServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameLogic.h"


int main()
{
	srand((unsigned)time(NULL));

	GameLogic::getSingleton()->Init();
	GameLogic::getSingleton()->releaseSingleton();
	
    return 0;
}

