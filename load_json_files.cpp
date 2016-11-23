#include "stdafx.h"
#include "load_json_files.h"
#include <iostream>

load_json_files::load_json_files(const wchar_t* directory_name)
	: ifstream_file(directory_name)
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
}

load_json_files::~load_json_files()
{
}

bool load_json_files::create_component(const wchar_t* file_name)
{
	return true;
}
