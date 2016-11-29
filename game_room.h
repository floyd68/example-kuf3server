#pragma once
#include "User.h"

class game_room
{
public:
	game_room(const int user_no);
	~game_room();
	
	bool init();
	bool join(const int user_no); // 유저 참여
	void out(const int user_no); // 유저가 종료하거나 접속 끊겼을때 호출 해야 함.
	void update(const unsigned long tick);

private:
	vector<int> vec_user;
};

