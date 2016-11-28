#include "stdafx.h"
#include "resource_mgr.h"


void resource_mgr::Initialize()
{
	load_file.load();
	stage_info.load();
}

const ENEMY_WAVE_INFO& resource_mgr::get_stage_info()
{
	return stage_info.get_data();
}