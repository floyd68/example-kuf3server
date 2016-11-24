#pragma once

class data_mgr
{
public:
	data_mgr();
	~data_mgr();

	void init();
	bool load();

	vector<string> vec_entity;
};

