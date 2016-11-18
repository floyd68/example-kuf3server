// RXTServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

