#pragma once
#include "SingletonBase.h"
#include "UserManager.h"
#include "stage_enemy_info.h"
#include "load_json_files.h"

//#include "component_base.h"

class game_logic_mgr : public CSingletonBase<game_logic_mgr>
{
public:
	game_logic_mgr(): m_iStageLv(0), m_iWave(0), load_file(L"Data"){}

public:
	void Initialize();

	//EntityPtr CreateObject(const std::string& strName, D2D1_POINT_2F Point = { 0.f, 0.f });
	//void CreateObjectMsg(const std::string& strName, D2D1_POINT_2F Point = { 0.f, 0.f });

	const ENEMY_WAVE_INFO& get_stage_info();

private:
	void CreateEnemy();

	unsigned m_iStageLv;
	unsigned m_iWave;

	stage_enemy_info	stage_info;
	load_json_files		load_file;
};

