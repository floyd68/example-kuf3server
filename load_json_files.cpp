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

using namespace EntityFactory;
bool load_json_files::create_component(const wchar_t* file_name)
{
	string name("Data\\" + _system::W2M(file_name) + ".json");
	rapidjson::Document document = json_loader::file_load(name.c_str());
	if (document.HasParseError())
		return false;

	vector<ComsIDAndInitVal> vecComsStruct;

	auto iter = document.MemberBegin();
	auto enditer = document.MemberEnd();

	auto strEntityName = iter->value.GetString();
	++iter;

	for (; iter != enditer; ++iter)
	{
		ComsIDAndInitVal comStruct;
		comStruct.strComID = iter->name.GetString();

		const auto& memberValue = iter->value;
		auto memberEndIter = memberValue.MemberEnd();
		for (auto memberIter = memberValue.MemberBegin(); memberIter != memberEndIter; ++memberIter)
		{
			boost::any anyValue;
			const auto& initValue = memberIter->value;

			auto strMemberValueName = memberIter->name.GetString();

			if (strMemberValueName == "Shape")
			{
				const static map<string, RENDER_VALUE> s_mapRenderValueTable =
				{
					{ "E_CIRCLE", RENDER_VALUE::E_CIRCLE },
					{ "E_CIRCLE_N", RENDER_VALUE::E_CIRCLE_N },
					{ "E_RECT", RENDER_VALUE::E_RECT },
					{ "E_RECT_N", RENDER_VALUE::E_RECT_N },
				};

				auto renderValueIter = s_mapRenderValueTable.find(initValue.GetString());

				if (renderValueIter != s_mapRenderValueTable.end())
					anyValue = renderValueIter->second;
			}
			else if (strMemberValueName == "ColObjType")
			{
				const static map<string, OBJ_TYPE> s_mapEntityColObjTypeTable =
				{
					{ "ENTITY_PLAYER", OBJ_TYPE::OBJ_PLAYER },
					{ "ENTITY_ENEMY", OBJ_TYPE::OBJ_ENEMY },
					{ "ENTITY_PLAYERATTACKBOX", OBJ_TYPE::OBJ_PLAYERATTACKBOX },
					{ "ENTITY_ENEMYATTACKBOX", OBJ_TYPE::OBJ_ENEMYATTACKBOX },
					{ "ENTITY_WARNINGBOX", OBJ_TYPE::OBJ_WARNINGBOX },
					{ "ENTITY_ITEM", OBJ_TYPE::OBJ_ITEM },
				};

				auto entityColObjTypeIter = s_mapEntityColObjTypeTable.find(initValue.GetString());

				if (entityColObjTypeIter != s_mapEntityColObjTypeTable.end())
					anyValue = entityColObjTypeIter->second;
			}
			else if (initValue.IsInt())
				anyValue = initValue.GetInt();
			else if (initValue.IsDouble())
				anyValue = static_cast<float>(initValue.GetDouble());
			else if (initValue.IsString())
				anyValue = static_cast<string>(initValue.GetString());
			else if (initValue.IsBool())
				anyValue = initValue.GetBool();

			comStruct.InitVal.emplace(dynamic::value_type(memberIter->name.GetString(), anyValue));
		}
		vecComsStruct.push_back(comStruct);
	}
	m_mapComponentStruct.emplace(ENTITY_MAP::value_type(strEntityName, vecComsStruct));

	return true;
}
