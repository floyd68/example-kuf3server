#pragma once

#include "ifstream_file.h"

class load_json_files : protected ifstream_file
{
public:
	load_json_files(const wchar_t* directory_name);
	~load_json_files();
};

