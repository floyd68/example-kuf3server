#include "stdafx.h"
#include "User.h"
#include "GameLogic.h"
#include "PacketInfo.h"
#include "kuf3packet_header.h"
#include "stage_enemy_info.h"
#include "UserManager.h"
#include "resource_mgr.h" //test - DCAT
#include "game_room_mgr.h"

void User::handle_net_msg(const SMsgRecv& recv)
{
	SMsgSend sendMsg = recv.ConvertSendMsg();

	switch (static_cast<KUF3PACKET>(sendMsg.GetusID()))
	{
	case KUF3PACKET::C2S_LOGIN_AUTH_REQ:
		insert_user();
		break;
	case KUF3PACKET::C2S_READY_STAGE_REQ:
		send_stage_info();
		break;
	case KUF3PACKET::C2S_START_STAGE_REQ:
		break;
	case KUF3PACKET::C2S_DISCONNECT_REQ:
		quit(recv);
		break;
	default:
		m_pSessionMgr->BroadCast(this->shared_from_this(), sendMsg);
		break;
	}
}

void User::send(SMsgSend msg)
{
	m_pSessionMgr->send(this->shared_from_this(), msg);
}

void User::quit(const SMsgRecv& recv)
{
	int user_no;
	recv >> user_no;

	if (user_no != _unique_number)
		return;

	log_info("session : %d, unique_number : %d", this->shared_from_this(), _unique_number);
	static_cast<UserManager*>(m_pSessionMgr)->erase_user_map(_unique_number);
	_unique_number = -1;
	set_active(false);

	SMsgSend s(static_cast<unsigned short>(KUF3PACKET::S2C_DISCONNECT_RES));
	send(s);
}

void User::on_session_disconnected()
{
	if (_unique_number != -1)
	{
		// 강제종료? -_-
		static_cast<UserManager*>(m_pSessionMgr)->erase_user_map(_unique_number);
	}
	m_pSessionMgr->on_session_disconnected(this->shared_from_this());
}

bool User::insert_user()
{
	_unique_number = m_pSessionMgr->insert_user(this->shared_from_this());
	SMsgSend msg(static_cast<unsigned short>(KUF3PACKET::S2C_LOGIN_AUTH_RES));
	msg << _unique_number << D2D1::Point2F(static_cast<float>(WIN_SIZE_X >> 1), static_cast<float>(WIN_SIZE_Y >> 1)); 
	//todo 플레이어 시작위치는 일단 중앙에 줌. (추후 플레이어 시작위치 고민해볼 것)
	send(msg);
	return true;
}

bool User::send_stage_info()
{
	game_room_mgr::getSingleton()->creat_game_room(_unique_number);
	return true;
}
