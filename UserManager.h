#pragma once

#include "kuf3packet_header.h"
#include "User.h"

class UserManager;
typedef std::shared_ptr<UserManager> UserMgrPtr;
class UserManager : public SessionManager<User>
{
public:
	UserManager(asio::io_service& service, int nInitial, bool bGrow)
		: _generator(0), SessionManager<User>(service, nInitial, bGrow){}
	
public:
	virtual int insert_user(UserPtr ptr) override
	{
		int unique_number = generate_unique_number();
		_map_User.insert({ unique_number, ptr }); // 일단은 ID 없으니까 ㅡ.ㅡ... 유저 구분하기 위해 아무 숫자나 준다
		return unique_number;
	}
	void erase_user_map(int unique_number)
	{
		_map_User.erase(unique_number);
	}

	bool send(int user_no, SMsgSend msg)
	{
		const auto it = _map_User.find(user_no);
		if (it == _map_User.end())
			return false;

		it->second->start_send(msg);
	}


	// -------------------------------------------------------------------------

	virtual void BroadCast(UserPtr pSession, SMsgSend& msg) override
	{
		for (auto& Session : _map_User)
		{
			if (pSession == Session.second)
				continue;
			Session.second->start_send(msg);
		}
	}
	virtual void SendIsHost(UserPtr pSession)override
	{
		//SMsgSend msg(static_cast<unsigned short>(PACKET_ID::PACKET_IS_HOST));
		//if (m_liUserList.empty())
		//{
		//	pSession->SetHost(true);
		//	msg << true;
		//}
		//else
		//	msg << false;
		//pSession->start_send(msg);  //빌드를 위해 잠시 막아둠 DCAT
	}

	virtual void send(UserPtr pSession, SMsgSend& msg) override
	{
		pSession->start_send(msg);
	}

private:
	int generate_unique_number()
	{
		_mutex.lock();
		++_generator;
		_mutex.unlock();
		return _generator;
	}
	
	mutex _mutex;
	int _generator;
	map<int, UserPtr> _map_User;
};

