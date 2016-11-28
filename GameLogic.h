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
#include "resource_mgr.h"

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
	GameLogic() {}

	NetworkService service;
	UserManager* UserMgr;

public:
	// by floyd
	// 초기화, 실제 동작 부분, 마무리 부분은 확실히 분리해 놓을것
	// Init 함수에서 초기화만이 아닌 실제 동작 부분과 마무리 까지 하리라고 함수명만 보고 도대체 누가 생각할 수 있겠음????

	void Init()
	{
		// by floyd
		// GameLogic이라는 클래스에서 resource_mgr를 생성하고 소멸시킨다는 얘기는
		// gmae_logic_mgr은 GameLogic이 관리한다는 얘기고 그건 곧 resource_mgr은 GameLogic에 속한 클래스라는 얘기임
		// 어떤 클래스 B가 어떤 클래스 A에 속한다는 건 B에 대한 접근은 오로지 A를 통해서만 해야 한다는 얘기
		// 현재 클래스 구조는 아주 아주 잘못 되었기 때문에 둘 중 하나의 방식으로 바꾸어야 함
		// 1. gmae_logic_mgr을 싱글톤이 아닌 GameLogic의 멤버 변수로 바꾸고 GameLogic외부에서 접근할 일이 있으면 GameLogic을 통해서 해야함
		// 1-1. GameLogic에서 get_resource_mgr() 같은 함수는 절대 절대 만들지 말아야 함. 이 함수를 만들어야 할 정도로 외부에서 접근이 많다면 2번 방법을 고려해야함
		// 2. resource_mgr을 외부에서 접근할 일이 많다면 GameLogic내에서 생성하는게 아니라 Main쪽에서 생성해야함. 

		//resource_mgr::getSingleton()->Initialize(); //스테이지 관련 정보 로드 DCAT
	}
	void Run()
	{
		//연결관련 부분은 따로 빼면 좋겠음..DCAT

		std::stringstream ss;
		ss << std::this_thread::get_id();

		fprintf(stdout, "Main Thread %s\n", ss.str().c_str());

		UserMgr = new UserManager(service.get_io_service(), 100, true);

		auto tcp_acceptor = service.new_acceptor<User>(9999, UserMgr);

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
		delete UserMgr;
	}
	void Destroy()
	{
		resource_mgr::getSingleton()->releaseSingleton();

		//stage_enemy_info::getSingleton()->releaseSingleton();
	}

};