#pragma once
#include "SingletonBase.h"
#include "game_room.h"

class game_room_mgr : public CSingletonBase<game_room_mgr>
{
public:
	game_room_mgr();
	~game_room_mgr();

	inline const size_t get_total_number() const { return vec_rooms.size(); }
	void creat_game_room(const int user_no);

	bool join(const int user_no, const int room_no); // ���� ����
	void out(const int user_no, const int room_no); // ������ �����ϰų� ���� �������� ȣ�� �ؾ� ��.

	void update(const unsigned long tick);

private:
	vector<game_room> vec_rooms;
	mutex mutex_vector;

};