#include "stdafx.h"
#include "User.h"
#include "GameLogic.h"
#include "PacketInfo.h"

void User::handle_net_msg(const SMsgRecv& msg)
{
	SMsgSend sendMsg = msg.ConvertSendMsg();

	switch (static_cast<PACKET_ID>(sendMsg.GetusID()))
	{
	case PACKET_ID::PACKET_IS_LOGIN_REQ:
		AddUser();
		break;
	case PACKET_ID::PACKET_NEW_OBJ:
	{
		ENTITY_TYPE eType;
		float fX;
		float fY;

		msg >> eType >> fX >> fY;

		ObjInfo tObjInfo = { eType, fX, fY };

		GameLogic::getSingleton()->AddObjInfo(tObjInfo);
		m_pSessionMgr->BroadCast(this->shared_from_this(), sendMsg);
		this->shared_from_this()->start_send(sendMsg);
		break;
	}
	case PACKET_ID::PACKET_SEND_POS_INFO:
		AddPlayerPosObjInfo(msg);
		break;
	case PACKET_ID::PACKET_SEND_STAT_INFO:
		AddPlayerStatObjInfo(msg);
		break;
	default:
		m_pSessionMgr->BroadCast(this->shared_from_this(), sendMsg);
		break;
	}
}

void User::SendObjList()
{
	size_t nSize = GameLogic::getSingleton()->GetObjListSize() - 1;
	unsigned ID = static_cast<unsigned>(nSize);

	const std::vector<ObjInfo>& vecObjList = GameLogic::getSingleton()->GetvecObjList();

	for (size_t i = 0; i < nSize; ++i)
	{
		SMsgSend msg(static_cast<unsigned short>(PACKET_ID::PACKET_USER_INIT));
		msg << ID;
		msg << vecObjList[i].eEntityName;
		msg << vecObjList[i].fX;
		msg << vecObjList[i].fY;
		this->shared_from_this()->start_send(msg);
	}
	SMsgSend msg(static_cast<unsigned short>(PACKET_ID::PACKET_USER_INIT));
	msg << ID;
	msg << ENTITY_TYPE::TY_PLAYER;
	msg << vecObjList[nSize].fX;
	msg << vecObjList[nSize].fY;
	this->shared_from_this()->start_send(msg);
}

void User::AddUser()
{
	PlayerData stPlayerData;
	ObjInfo eObjInfo = { ENTITY_TYPE::TY_OTHER_PLAYER, 400.f, 400.f, OBJ_TYPE::OBJ_PLAYER, stPlayerData };
	SMsgSend Sendmsg(static_cast<unsigned short>(PACKET_ID::PACKET_NEW_PLAYER));
	Sendmsg << eObjInfo.eEntityName << eObjInfo.fX << eObjInfo.fY;
	m_pSessionMgr->BroadCast(this->shared_from_this(), Sendmsg);
	m_pSessionMgr->SendIsHost(this->shared_from_this());
	GameLogic::getSingleton()->AddObjInfo(eObjInfo);
	SendObjList();
	m_pSessionMgr->AddUserList(this->shared_from_this());
}
void  User::AddPlayerStatObjInfo(const SMsgRecv& msg)
{
	unsigned EntityID;
	msg >> EntityID;
	const std::vector<ObjInfo>& vecObjList = GameLogic::getSingleton()->GetvecObjList();
	PlayerData stPlayerData = boost::any_cast<PlayerData>(vecObjList[EntityID].ObjData);
	msg >> stPlayerData.bAttUp >> stPlayerData.eAttType >> stPlayerData.fCurHp >> stPlayerData.fHp >> stPlayerData.fAtt >> stPlayerData.fAttUpTime >> stPlayerData.bTempInvincible >> stPlayerData.fTempInvincibleTime >> stPlayerData.bIsInvincible;
	GameLogic::getSingleton()->SetObjInt(EntityID, stPlayerData);
}

void  User::AddPlayerPosObjInfo(const SMsgRecv& msg)
{
	unsigned EntityID;
	msg >> EntityID;
	const std::vector<ObjInfo>& vecObjList = GameLogic::getSingleton()->GetvecObjList();
	PlayerData stPlayerData = boost::any_cast<PlayerData>(vecObjList[EntityID].ObjData);
	msg >> stPlayerData.bSpeedUp >> stPlayerData.fSpeed >> stPlayerData.fSpeedUpTime;
	GameLogic::getSingleton()->SetObjInt(EntityID, stPlayerData);
}