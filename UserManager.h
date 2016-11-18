#pragma once

#include "PacketInfo.h"
#include "User.h"

class UserManager :public SessionManager<User>
{
public:
	UserManager(asio::io_service& service, int nInitial, bool bGrow)
		:SessionManager<User>(service, nInitial, bGrow){}
	
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
	//virtual void AddStatObjInfo(UserPtr pSession, const SMsgRecv& msg) override
	//{
	//	unsigned EntityID;
	//	msg >> EntityID;
	//	PlayerData stPlayerData = boost::any_cast<PlayerData>(m_vecObjList[EntityID].ObjData);
	//	msg >> stPlayerData.bAttUp >> stPlayerData.eAttType >> stPlayerData.fCurHp >> stPlayerData.fHp >> stPlayerData.fAtt >> stPlayerData.fAttUpTime >> stPlayerData.bTempInvincible >> stPlayerData.fTempInvincibleTime >> stPlayerData.bIsInvincible;
	//	m_vecObjList[EntityID].ObjData = stPlayerData;
	//}
	virtual void SendIsHost(UserPtr pSession)override
	{
		SMsgSend msg(static_cast<unsigned short>(PACKET_ID::PACKET_IS_HOST));
		if (m_liUserList.empty())
		{
			pSession->SetHost(true);
			msg << true;
		}
		else
			msg << false;
		pSession->start_send(msg);
	}
private:
	std::list<UserPtr> m_liUserList;
};

