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
//todo ���� ���� �ı��Ǵ� �κ��� ����.
//���� �ı��Ǹ� ���� �����Ǵ� �� �ѹ��� ��� ���� ������ ����غ��� ��.
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

	// �� �κ� ����ó���� �̷��� �ص� ���������� �𸣰���.
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