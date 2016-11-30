#include "stdafx.h"
#include "game_room.h"
#include "entity_enum.h"
#include "resource_mgr.h"
#include "GameLogic.h"

game_room::game_room(const int user_no) : stage_no(0), wave_no(0)
{
	join(user_no);
}


game_room::~game_room()
{
}

bool game_room::init()
{
	send_stage_info();
	return false;
}

void game_room::send_stage_info()
{
	static std::map<std::string, ENTITY_TYPE> s_mapEntityTypeTable =
	{
		//{ "Player", ENTITY_TYPE::OBJ_PLAYER },
		//{ "OtherPlayer", OBJ_TYPE::OBJ_PLAYER },
		{ "Bat", ENTITY_TYPE::TY_BAT },
		{ "Skeleton", ENTITY_TYPE::TY_SKELETON },
		{ "Zombi", ENTITY_TYPE::TY_ZOMBI },
		{ "Ghost", ENTITY_TYPE::TY_GHOST },
		{ "Mushroom", ENTITY_TYPE::TY_MUSHROOM },
		{ "Mage", ENTITY_TYPE::TY_MAGE },
		{ "Goblin", ENTITY_TYPE::TY_GOBLIN },
		{ "Minota", ENTITY_TYPE::TY_MINOTA },
		{ "Dragon", ENTITY_TYPE::TY_DRAGON },
		{ "PlayerAttackBox", ENTITY_TYPE::TY_ATTACKBOX },
		//{ "PlayerEnemyBox", ENTITY_TYPE::tyen },
		{ "WarningBox", ENTITY_TYPE::TY_WARNINGBOX },
		{ "SpeedItem", ENTITY_TYPE::TY_SPEEDUP },
		{ "HpItem", ENTITY_TYPE::TY_HP },
		{ "AttItem", ENTITY_TYPE::TY_ATT },
		{ "TriCellItem", ENTITY_TYPE::TY_TRICELL },
		{ "FourCellItem", ENTITY_TYPE::TY_FOURCELL },
		{ "RapierItem", ENTITY_TYPE::TY_RAPIER },
		{ "ShotGunItem", ENTITY_TYPE::TY_SHOTGUN },
		{ "RifleItem", ENTITY_TYPE::TY_RIFLE },
		//{ "Cursor", ENTITY_TYPE::ty },
	};

	const auto& stage_info = resource_mgr::getSingleton()->get_stage_info();
	SMsgSend msg(static_cast<unsigned short>(KUF3PACKET::S2C_READY_STAGE_RES));

	int enemy_count = stage_info[stage_no][wave_no].size();
	msg << enemy_count;
	
	for (const auto& enemy : stage_info[stage_no][wave_no])
	{
		auto strName = enemy.strEnemyType;
		auto Point = enemy.tPos;

		auto entityTypeIter = s_mapEntityTypeTable.find(strName);
		 
		if (entityTypeIter != s_mapEntityTypeTable.end())
		{
			msg << strName << Point.x << Point.y; //test 일단 엔티티타입 스트링으로 보내봄.
		}
	}

	for (auto v : vec_user)
		GameLogic::getSingleton()->send(v, msg);
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
