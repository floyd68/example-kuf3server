#pragma once
#include "SingletonBase.h"
#include "UserManager.h"
#include "stage_enemy_info.h"
#include "load_json_files.h"

//#include "component_base.h"

class resource_mgr : public CSingletonBase<resource_mgr>
{
public:
	resource_mgr(): load_file(L"Data"){}

public:
	void Initialize();

	const ENEMY_WAVE_INFO& get_stage_info();

private:
	stage_enemy_info	stage_info;
	load_json_files		load_file;
};

