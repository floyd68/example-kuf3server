#include "stdafx.h"
#include "game_room.h"


game_room::game_room(int user_no)
{
}


game_room::~game_room()
{
}

bool game_room::init()
{
	return false;
}

bool game_room::join(const int user_no)
{
	vec_user.push_back(user_no);
	return true;
}

void game_room::out(const int user_no)
{
	auto it = find(vec_user.begin(), vec_user.end(), user_no);
	if (vec_user.end() == it)
		return;

	vec_user.erase(it);
}

void game_room::update(const unsigned long tick)
{
}
