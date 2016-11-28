#include "stdafx.h"
#include "User.h"
#include "GameLogic.h"
#include "PacketInfo.h"
#include "kuf3packet_header.h"
#include "stage_enemy_info.h"

#include "resource_mgr.h" //test - DCAT

#define SEND(x) m_pSessionMgr->send(this->shared_from_this(), x);

void User::handle_net_msg(const SMsgRecv& msg)
{
	SMsgSend sendMsg = msg.ConvertSendMsg();

	switch (static_cast<KUF3PACKET>(sendMsg.GetusID()))
	{
	case KUF3PACKET::C2S_LOGIN_AUTH_REQ:
		add_user();
		break;
	case KUF3PACKET::C2S_READY_STAGE_REQ:
		send_stage_info();
		break;
	case KUF3PACKET::C2S_START_STAGE_REQ:
		break;
	default:
		m_pSessionMgr->BroadCast(this->shared_from_this(), sendMsg);
		break;
	}
}

bool User::add_user()
{
	m_pSessionMgr->AddUserList(this->shared_from_this());
	SMsgSend msg(static_cast<unsigned short>(KUF3PACKET::S2C_LOGIN_AUTH_RES));
	SEND(msg);
	return true;
}

bool User::send_stage_info()
{
	SMsgSend msg(static_cast<unsigned short>(KUF3PACKET::S2C_READY_STAGE_RES));

	//const auto& abc = xxx.get_date();

	//msg << resource_mgr::getSingleton()->get_stage_info();




	SEND(msg);
	return true;
}
