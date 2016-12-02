#pragma once

#include "entity.h"

namespace EntityFactory
{
	// json ���Ͽ��� �о���� ������Ʈ�� ����
	struct component_info
	{
		std::string key; // ������Ʈ �ʿ��� Ű�� ���̴� string
		dynamic attribute; // �Ӽ�
	};

	EntityPtr CreateEntity(const std::string& strName);

	typedef std::map<std::string, std::vector<component_info>> ENTITY_MAP;
	extern ENTITY_MAP m_mapComponentStruct;
};