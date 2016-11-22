// RXTServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "GameLogic.h"


#include "load_json_files.h"

int main()
{
	srand((unsigned)time(NULL));

	std::wcout.imbue(std::locale("kor"));
	std::wcin.imbue(std::locale("kor"));

	svr_logger::create(L"log", L"log");

	log_info("test %d 한글!", 1);

	/*
	load_json_files iff(L"svr_entity");

	stage_enemy_info test;
	test.load();
	*/
	GameLogic::getSingleton()->Init();
	GameLogic::getSingleton()->releaseSingleton();
	
	svr_logger::destroy();
	return 0;
}

