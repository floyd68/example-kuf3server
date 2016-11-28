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

	resource_mgr::getSingleton()->Initialize(); //스테이지 관련 정보 로드 DCAT
	
	GameLogic::getSingleton()->Init();
	// by floyd
	// GameLogic 매니저의 초기화, 실제 동작, 마무리 구분
	GameLogic::getSingleton()->Run();
	GameLogic::getSingleton()->Destroy();
	
	resource_mgr::getSingleton()->releaseSingleton();

	svr_logger::destroy();
	return 0;
}

