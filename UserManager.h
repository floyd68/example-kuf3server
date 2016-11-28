#pragma once

#include "kuf3packet_header.h"
#include "User.h"

class UserManager : public SessionManager<User>
{
public:
	UserManager(asio::io_service& service, int nInitial, bool bGrow)
		: SessionManager<User>(service, nInitial, bGrow){}
	
public:
	virtual void AddUserList(UserPtr pSession) override
	{
		m_liUserList.push_back(pSession);
	}

	virtual void BroadCast(UserPtr pSession, SMsgSend& msg) override
	{
		for (auto& Session : m_liUserList)
		{
			if (pSession == Session)
				continue;
			Session->start_send(msg);
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

	int get_user_ptr(int user_no) { return 0; } // todo : 작업해야함.
private:
	std::list<UserPtr> m_liUserList;
	// map<int, UserPtr> map_User;
};

