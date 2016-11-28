#include "stdafx.h"
#include "json_loader.h"
#include "stage_enemy_info.h"
#include "KUF3Math.h"
#include "resource_mgr.h"

stage_enemy_info::stage_enemy_info()
{
}


stage_enemy_info::~stage_enemy_info()
{
}

bool stage_enemy_info::load()
{
	rapidjson::Document document = json_loader::file_load("Data/StageEnemyInfo.json");

	if (document.HasParseError())
		return false;

	auto iter = document.FindMember("Enemies");
	auto size = iter->value.Size();
	for (auto i = 0; i < size; ++i)
	{
		const auto& v = iter->value[i];
		if (v.IsObject() == false)
			continue;

		load_stage(v);
	}

	log_info("m_vecEnemyWaveInfo count : %d", m_vecEnemyWaveInfo.size());
	return true;
}

void stage_enemy_info::load_stage(const rapidjson::Value& v)
{
	auto all_stage_iter = v.MemberBegin();
	auto all_stage_end = v.MemberEnd();

	++all_stage_iter;

	vec_waves vec_wave;
	while (all_stage_iter != all_stage_end)
	{
		auto wave_iter = all_stage_iter->value.Begin();
		auto wave_end = all_stage_iter->value.End();

		vec_enemys vec_enemy;
		while (wave_iter != wave_end)
		{
			EnemyCreateInfo enemy;
			load_enemy(*wave_iter, __out enemy);
			vec_enemy.push_back(forward<EnemyCreateInfo>(enemy));
			++wave_iter;
		}
		vec_wave.push_back(forward<vec_enemys>(vec_enemy));
		
		++all_stage_iter;
	}
	m_vecEnemyWaveInfo.push_back(forward<vec_waves>(vec_wave));
}

void stage_enemy_info::load_enemy(const rapidjson::Value& v, __out EnemyCreateInfo& enemy) const
{
	auto enemy_iter = v.MemberBegin();
	auto enemy_end = v.MemberEnd();

	while (enemy_iter != enemy_end)
	{
		string name = enemy_iter->name.GetString();
		const auto& value = enemy_iter->value;

		if ("Type" == name)				enemy.strEnemyType = value.GetString();
		else if ("PosX" == name)		enemy.tPos.x = value.GetDouble();
		else if ("PosY" == name)		enemy.tPos.y = value.GetDouble();
		else if ("PosRandom" == name)	enemy.tPos = RandomPoint();

		++enemy_iter;
	}
}
