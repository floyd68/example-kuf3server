#include "stdafx.h"
#include "game_logic_mgr.h"


void game_logic_mgr::Initialize()
{
	load_file.load();
	stage_info.load();
}

const ENEMY_WAVE_INFO& game_logic_mgr::get_stage_info()
{
	return stage_info.get_data();
}

void game_logic_mgr::CreateEnemy()
{
	for (auto enemy : get_stage_info()[m_iStageLv][m_iWave])
	{
		//CreateObject(enemy.strEnemyType, enemy.tPos);
	}
}