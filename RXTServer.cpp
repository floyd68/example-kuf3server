// RXTServer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameLogic.h"


int main()
{
	srand((unsigned)time(NULL));

	std::wcout.imbue(std::locale("kor"));
	std::wcin.imbue(std::locale("kor"));

	svr_logger::create(L"log", L"log");

	log_info("test %d �ѱ�!", 1);

	GameLogic::getSingleton()->Init();
	GameLogic::getSingleton()->releaseSingleton();
	
	svr_logger::destroy();
	return 0;
}
