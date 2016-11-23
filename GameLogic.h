#pragma once
#include "NetworkService.h"
#include "PacketInfo.h"
#include "SMsg.h"
#include "SingletonBase.h"
#include "UserManager.h"
#include <conio.h>
//#include <map>  //필요없는 헤어 DCAT

#include "json_loader.h"
//#include "stage_enemy_info.h"
#include "game_logic_mgr.h"

class Obj : public NetStreamable
{
public:
	bool WriteTo(SMsgSend& msg) const override
	{
		return true;
	};
	bool ReadFrom(const SMsgRecv& msg) override
	{
		return true;
	};
};

class GameLogic : public CSingletonBase<GameLogic>
{
public:
	GameLogic(){}

public:
	void Init()
	{
		game_logic_mgr::getSingleton()->Initialize(); //스테이지 관련 정보 로드 DCAT

		//연결관련 부분은 따로 빼면 좋겠음..DCAT
		NetworkService service;

		std::stringstream ss;
		ss << std::this_thread::get_id();

		fprintf(stdout, "Main Thread %s\n", ss.str().c_str());

		UserManager UserMgr(service.get_io_service(), 100, true);

		auto tcp_acceptor = service.new_acceptor<User>(9999, &UserMgr);

		// test -.-;; zz
		//stage_enemy_info::getSingleton()->load();

		service.Run(8);
		while (true)
		{
			if (_getch() == '[')
			{
				service.Stop();
				break;
			}
		}

		service.Join();
		game_logic_mgr::getSingleton()->releaseSingleton();

		//stage_enemy_info::getSingleton()->releaseSingleton();

	}
};