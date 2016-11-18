#pragma once

enum class PACKET_ID : unsigned short
{
	PACKET_IS_HOST,
	PACKET_IS_LOGIN_REQ,
	PACKET_NEW_PLAYER,
	PACKET_USER_INIT,
	PACKET_NEW_OBJ,
	PACKET_HOST_OBJ_INFO,
	PACKET_SEND_STAT_INFO,
	PACKET_SEND_POS_INFO,
	PACKET_MOVE,
	PACKET_ATT,
};

enum class ENTITY_TYPE
{
	TY_PLAYER,
	TY_OTHER_PLAYER,
	TY_BAT,
	TY_SKELETON,
	TY_ZOMBI,
	TY_GHOST,
	TY_MUSHROOM,
	TY_MAGE,
	TY_GOBLIN,
	TY_MINOTA,
	TY_DRAGON,
	TY_ATTACKBOX,
	TY_WARNINGBOX,
	TY_SPEEDUP,
	TY_HP,
	TY_ATT,
	TY_TRICELL,
	TY_FOURCELL,
	TY_RAPIER,
	TY_SHOTGUN,
	TY_RIFLE,
	TY_END
};
enum class OBJ_TYPE
{
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_PLAYERATTACKBOX,
	OBJ_ENEMYATTACKBOX,
	OBJ_WARNINGBOX,
	OBJ_ITEM,
	OBJ_CURSOR,
	OBJ_END
};
enum class ATTACK_TYPE
{
	ATT_ONECELL,
	ATT_TRIPLE,
	ATT_FOURWAY,
	ATT_RAPIER,
	ATT_SHOTGUN,
	ATT_RIFLE,
	ATT_FIRE,
	ATT_ONEWAY
};
struct PlayerData
{
	bool bAttUp;
	ATTACK_TYPE eAttType;
	float fCurHp;
	float fHp;
	float fAtt;
	float fAttUpTime;
	bool bTempInvincible;
	float fTempInvincibleTime;
	bool bIsInvincible;
	bool bSpeedUp;
	float fSpeed;
	float fSpeedUpTime;
};

struct ObjInfo
{
	ENTITY_TYPE eEntityName;
	float fX;
	float fY;
	OBJ_TYPE eObjType;
	boost::any ObjData;
};
