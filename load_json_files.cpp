#include "load_json_files.h"
#include <iostream>

load_json_files::load_json_files(const wchar_t* directory_name)
	: ifstream_file(directory_name)
{
	/* test
	vec_files vec;
	read_all(vec);

	for (auto v : vec)
	{
		wcout << L"file name : " << v.first << endl;
		for (auto k : v.second)
		{
			wcout << k << endl;
		}
	}

	vec ��� ������ ��ƼƼ �ҷ����ָ��..........
	*/
}


load_json_files::~load_json_files()
{
}
