#pragma once
#include "User.h"

class game_room
{
public:
	game_room(const int user_no);
	~game_room();
	
	bool init();
	bool join(const int user_no); // ���� ����
	void out(); // ������ �����ϰų� ���� �������� ȣ�� �ؾ� ��.
	void update(const unsigned long tick);

private:
	vector<int> _vec_user;
};

