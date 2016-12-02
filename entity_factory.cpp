#include "stdafx.h"
#include "entity_factory.h"
#include "obj_mgr.h"

#include "ai_component.h"

//#include "PositionComponent.h"
//#include "RenderComponent.h"
//#include "ColliderComponent.h"
//#include "AttackComponent.h"
//#include "InputComponent.h"
//#include "CreateComponent.h"
//#include "WarningBoxComponent.h"
//#include "GuageComponent.h"
//#include "ItemComponent.h"
//#include "StatPlayerComponent.h"
//#include "StatEnemyComponent.h"
//#include "AttackBoxComponent.h"
//#include "AIComponent.h"
//#include "CursorComponent.h"

EntityFactory::ENTITY_MAP EntityFactory::m_mapComponentStruct = {};
//-----------------------------------------------------------------------------------------------------------
typedef CompPtr(*CompCreatorfunc)(EntityPtr, const dynamic&);

#define COMP( _name_ ) [](EntityPtr pEntity, const dynamic& params) -> CompPtr { return CompPtr(new _name_(pEntity, params)); }

static std::map <std::string, CompCreatorfunc> s_mapCompCreator =
{
	{ "COM_AI", COMP(ai_component) },
};
//-----------------------------------------------------------------------------------------------------------
static std::map<std::string, OBJ_TYPE> s_mapEntityObjTypeTable =
{
	{ "Bat", OBJ_TYPE::OBJ_ENEMY },
};
//-----------------------------------------------------------------------------------------------------------
static std::map<std::string, dynamic> s_EntityStrAttrTable =
{
	{ "Player",{ { "Speed", 200.f },{ "Hp", 100.f },{ "CurHp", 100.f },{ "Att", 10.f } } },
	{ "OtherPlayer",{ { "Speed", 200.f },{ "Hp", 100.f },{ "CurHp", 100.f },{ "Att", 10.f } } },
	{ "Bat",{ { "Speed", 60.f },{ "Hp", 20.f },{ "CurHp", 20.f },{ "Att", 10.f } } },
	{ "Skeleton",{ { "Speed", 60.f },{ "Hp", 30.f },{ "CurHp", 30.f },{ "Att", 10.f } } },
	{ "Zombi",{ { "Speed", 60.f },{ "Hp", 30.f },{ "CurHp", 30.f },{ "Att", 10.f } } },
	{ "Ghost",{ { "Speed", 100.f },{ "Hp", 20.f },{ "CurHp", 20.f },{ "Att", 20.f } } },
	{ "Mushroom",{ { "Speed", 0.f },{ "Hp", 40.f },{ "CurHp", 40.f },{ "Att", 20.f } } },
	{ "Mage",{ { "Speed", 20.f },{ "Hp", 50.f },{ "CurHp", 50.f },{ "Att", 10.f } } },
	{ "Goblin",{ { "Speed", 80.f },{ "Hp", 30.f },{ "CurHp", 30.f },{ "Att", 10.f } } },
	{ "Minota",{ { "Speed", 50.f },{ "Hp", 100.f },{ "CurHp", 100.f },{ "Att", 30.f } } },
	{ "Dragon",{ { "Speed", 50.f },{ "Hp", 100.f },{ "CurHp", 100.f },{ "Att", 40.f } } },
	{ "PlayerAttackBox",{ { "Alpha", 0.5f },{ "Color", D2D1::ColorF::Blue } } },
	{ "EnemyAttackBox",{ { "Alpha", 0.5f } } },
	{ "WarningBox",{} },
	{ "SpeedItem",{ { "Item", ITEM_ID::ITEM_SPEEDUP } } },
	{ "HpItem",{ { "Item", ITEM_ID::ITEM_HP } } },
	{ "AttItem",{ { "Item", ITEM_ID::ITEM_ATT } } },
	{ "TriCellItem",{ { "Item", ITEM_ID::ITEM_TRICELL } } },
	{ "FourCellItem",{ { "Item", ITEM_ID::ITEM_FOURCELL } } },
	{ "RapierItem",{ { "Item", ITEM_ID::ITEM_RAPIER } } },
	{ "ShotGunItem",{ { "Item", ITEM_ID::ITEM_SHOTGUN } } },
	{ "RifleItem",{ { "Item", ITEM_ID::ITEM_RIFLE } } },
	{ "Cursor",{} },
};
//-----------------------------------------------------------------------------------------------------------
EntityPtr EntityFactory::CreateEntity(const std::string& strName)
{
	EntityPtr pEntity = std::make_shared<CEntity>();

	size_t uObjSize = CObjectMgr::getSingleton()->GetvecObjSize() + CObjectMgr::getSingleton()->GetvecAddObjSize();

	pEntity->SetEntityID(uObjSize);

	auto iter = m_mapComponentStruct.find(strName);
	if (iter == m_mapComponentStruct.end())
		return nullptr;

	auto entityObjTypeIter = s_mapEntityObjTypeTable.find(strName);

	if (entityObjTypeIter != s_mapEntityObjTypeTable.end())
		pEntity->SetObjType(entityObjTypeIter->second);

	auto strAttrIter = s_EntityStrAttrTable.find(strName);
	if (strAttrIter == s_EntityStrAttrTable.end())
		return nullptr;

	for (auto strAttr : strAttrIter->second)
	{
		pEntity->SetAttr(strAttr.first, strAttr.second);
	}

	return pEntity;
}