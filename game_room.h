#pragma once
#include "User.h"

class game_room
{
public:
	game_room(const int user_no);
	~game_room();
	
	bool init();
	bool join(const int user_no); // ���� ����
	void out(const int user_no); // ������ �����ϰų� ���� �������� ȣ�� �ؾ� ��.
	void update(const unsigned long tick);

private:
	vector<int> vec_user;
};

