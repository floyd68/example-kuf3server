#include "stdafx.h"
#include "load_json_files.h"
#include "str_util.h"
//#include <iostream> //필요없는 헤더DCAT
#include "entity_factory.h"

using namespace rapidjson;

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
		for (auto file_name : v.second)
		{
			log_info("load file : %s", file_name.c_str()); 
			if (load_component_info(file_name.c_str()) == false)
			{
				log_error("failed to create componet file. name : %s", file_name);
			}
		}
	}
	return true;
}

using namespace EntityFactory;
bool load_json_files::load_component_info(const wchar_t* file_name)
{
	string name("Data\\" + _system::W2M(file_name) + ".json");
	rapidjson::Document document = json_loader::file_load(name.c_str());
	if (document.HasParseError())
		return false;

	vector<component_info> vecComsStruct;

	auto iter_category = document.MemberBegin();
	auto category_end = document.MemberEnd();

	auto eneity_object_type = iter_category->value.GetString();
	++iter_category;

	for (; iter_category != category_end; ++iter_category)
	{
		component_info st_component;
		st_component.key = iter_category->name.GetString();

		const auto& component = iter_category->value;
		auto component_end = component.MemberEnd();
		for (auto iter_component = component.MemberBegin(); iter_component != component_end; ++iter_component)
		{
			boost::any anyValue;
			const auto& attribute = iter_component->value;
			
			if (st_component.key == "ColObjType")
			{
				static std::map<std::string, OBJ_TYPE> table =
				{
					{ "ENTITY_PLAYER", OBJ_TYPE::OBJ_PLAYER },
					{ "ENTITY_ENEMY", OBJ_TYPE::OBJ_ENEMY },
				};

				auto iter = table.find(attribute.GetString());
				if (iter != table.end())
					anyValue = iter->second;
			}
			else if (attribute.IsInt())
				anyValue = attribute.GetInt();

			else if (attribute.IsDouble())
				anyValue = static_cast<float>(attribute.GetDouble());

			else if (attribute.IsString())
				anyValue = static_cast<string>(attribute.GetString());

			else if (attribute.IsBool())
				anyValue = attribute.GetBool();
			else
			{
				log_error("undefind type. key : %s, value : %s", st_component.key, attribute.GetString());
				continue;
			}

			st_component.attribute.emplace(dynamic::value_type(st_component.key, anyValue));
		}
		vecComsStruct.push_back(st_component);
	}
	m_mapComponentStruct.emplace(ENTITY_MAP::value_type(eneity_object_type, vecComsStruct));

	return true;
}
