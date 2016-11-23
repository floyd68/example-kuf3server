#include "stdafx.h"
#include "game_logic_mgr.h"


void game_logic_mgr::Initialize()
{
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
		//CreateObjectMsg(enemy.strEnemyType, enemy.tPos);
	}
}