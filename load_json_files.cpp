#include "stdafx.h"
#include "load_json_files.h"
#include "str_util.h"
#include <iostream>

load_json_files::load_json_files(const wchar_t* directory_name)
	: ifstream_file(directory_name)
{
}

load_json_files::~load_json_files()
{
}

bool load_json_files::load()
{
	vec_files json_files;
	read_all(json_files);

	for (auto v : json_files)
	{
		for (auto k : v.second)
		{
			log_info("load file : %s", k);
			if (create_component(k.c_str()) == false)
			{
				log_error("failed to create componet file. name : %s", k);
			}
		}
	}

	return true;
}

bool load_json_files::create_component(const wchar_t* file_name)
{
	string name("Data\\" + _system::W2M(file_name) + ".json");
	rapidjson::Document document = json_loader::file_load(name.c_str());
	if (document.HasParseError())
		return false;

	return true;
}
