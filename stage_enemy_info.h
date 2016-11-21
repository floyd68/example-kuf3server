#pragma once

#include "json_loader.h"
#include "data_structure.h"


class stage_enemy_info : protected json_loader
{
public:
	stage_enemy_info();
	virtual ~stage_enemy_info();

	virtual bool load();
	const ENEMY_WAVE_INFO& get_data() { return m_vecEnemyWaveInfo; }

private:
	void load_stage(const rapidjson::Value& v);
	void load_enemy(const rapidjson::Value& v, __out EnemyCreateInfo& enemy) const;

	ENEMY_WAVE_INFO m_vecEnemyWaveInfo;
};

