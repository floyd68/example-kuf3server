#include "stdafx.h"
#include "ai_component.h"
#include "KUF3Math.h"

BEGIN_DO_ATTR(ai_component)
END_DO_ATTR

ai_component::ai_component(EntityPtr ptr, const dynamic & file_name) : CComponentBase(ptr)
{
	auto meta_table = kaguya::UserdataMetatable<ai_component>();
	auto ai_meta_table = meta_table.setConstructors<ai_component(EntityPtr, const dynamic &)>();

	// �Լ� ���ε�
	ai_meta_table = ai_meta_table.addFunction("update_random_pos", &ai_component::update_random_pos);

	// ���
	state["ai"].setClass(ai_meta_table);

	state["ai_class"] = this;

	std::string strFileName = "lua/";
	strFileName += boost::any_cast<std::string>(file_name.at("Script"));
	state.dofile(strFileName);
}

ai_component::~ai_component()
{
}

bool ai_component::ready(float elapsed_time)
{
	if (is_ready) return true;

	float alpha = m_pEntity->GetAttr<float>("Alpha");

	alpha = alpha + elapsed_time * 0.3f;

	if (alpha > 1.f)
	{
		update_random_pos();
		m_pEntity->SetAttr("IsInvincible", false);
		alpha = 1.f;
		is_ready = true;
	}

	m_pEntity->SetAttr("Alpha", alpha);

	return false;
}

void ai_component::update_random_pos()
{
	auto point = RandomPoint();
	// m_pEntity->Do("move_unit", point); // ���� �ȸ���
}

// ���� ��� ���� �ȸ��� -_-
// ���� ������ ���� output ���� ���� �ű� ���̺귯���� �־���߰��� ������ �� ��
// ���� �׽�Ʈ ���غ�. ���常��. ����� �κ��� ����.