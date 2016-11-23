#pragma once
#include "SingletonBase.h"
#include "UserManager.h"
#include "stage_enemy_info.h"

class game_logic_mgr : public CSingletonBase<game_logic_mgr>
{
public:
	game_logic_mgr(): m_iStageLv(0), m_iWave(0) {}

public:
	void Initialize();
	void CreateEnemy();

	const ENEMY_WAVE_INFO& get_stage_info();

private:
	unsigned m_iStageLv;
	unsigned m_iWave;

	stage_enemy_info stage_info;

};

