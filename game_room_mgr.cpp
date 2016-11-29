#include "stdafx.h"
#include "game_room_mgr.h"
#include "svr_logger.h"


game_room_mgr::game_room_mgr()
{
}


game_room_mgr::~game_room_mgr()
{
}

void game_room_mgr::creat_game_room(const int user_no)
{
	game_room room(user_no);
	room.init();

	vec_rooms.push_back(room);
}

bool game_room_mgr::join(const int user_no, const int room_no)
{
//todo 현재 방이 파괴되는 부분이 없음.
//방이 파괴되면 새로 생성되는 방 넘버를 어떻게 넣을 것인지 고민해봐야 함.
	lock_guard<mutex> lock(mutex_vector);
	if (vec_rooms.empty())	return false; 
	try
	{
		vec_rooms.at(room_no).join(user_no);
	}
	catch (const out_of_range& e)
	{
		log_error("room is not exist");
		return false;
	}

	// 이 부분 예외처리를 이렇게 해도 괜찮은건지 모르겠음.
	return true;
}

void game_room_mgr::out(const int user_no, const int room_no)
{
	lock_guard<mutex> lock(mutex_vector);
	if (vec_rooms.empty())	return;
	try
	{
		vec_rooms.at(room_no).out(user_no);
	}
	catch (const out_of_range& e)
	{
		log_error("room is not exist");
		return;
	}
}

void game_room_mgr::update(const unsigned long tick)
{
}