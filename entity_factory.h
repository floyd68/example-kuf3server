#pragma once

#include "entity.h"

namespace EntityFactory
{
	// json 파일에서 읽어오는 컴포넌트의 정보
	struct component_info
	{
		std::string key; // 컴포넌트 맵에서 키로 쓰이는 string
		dynamic attribute; // 속성
	};

	EntityPtr CreateEntity(const std::string& strName);

	typedef std::map<std::string, std::vector<component_info>> ENTITY_MAP;
	extern ENTITY_MAP m_mapComponentStruct;
};