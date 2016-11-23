#pragma once

#include "json_loader.h"
#include "ifstream_file.h"

class load_json_files : protected ifstream_file, protected json_loader
{
public:
	load_json_files(const wchar_t* directory_name);
	~load_json_files();

	virtual bool load();
	bool create_component(const wchar_t* file_name);
};

