#pragma once

#include "SingletonBase.h"
#include "component_base.h"

class CEntity;

class CObjectMgr : public CSingletonBase <CObjectMgr>
{
public:
	CObjectMgr() {}

public:
	void Update(float fElapsedTime);
	void Render();

public:
	bool Do(const std::string& strAction, const boost::any& param = 0);
	template <typename T> void for_each_entities(const T& pred)
	{
		for (auto entity : m_vecObject)
			pred(entity);
	}
	template <typename T> void for_each_Addentities(const T& pred)
	{
		for (auto entity : m_vecAddObject)
			pred(entity);
	}
	template <typename T> EntityPtr find_for(T pred)
	{
		for (auto entity : m_vecObject)
		{
			if (pred(entity))
				return entity;
		}
		return nullptr;
	}
	EntityPtr GetLastEntity(int Index)
	{
		if (m_vecAddObject.empty())
			return m_vecObject[Index];
	}
	size_t GetvecObjSize() { return m_vecObject.size(); }
	size_t GetvecAddObjSize() { return m_vecAddObject.size(); }
public:
	void AddObject(EntityPtr pEntity)
	{
		m_vecAddObject.push_back(pEntity);
	}
	// std::vector<CEntity*> GetVecObj(){ return m_vecObject; }
	// vector�� by reference�� �ƴ� by value�� �ѱ�� ���� �־��� �����ս��� ������.
	// ���������� ������ Manager ���� ��ü�� �״�� �ܺη� �Ѱ��ִ� ���� ����� ���ؾ���.
	// ��� ���� for_each_entities, find_for ���� �Լ��� ����ϰų� ����� �Լ��� ����� ����Ͽ��� ��.

private:
	std::vector< EntityPtr > m_vecObject;
	std::vector< EntityPtr > m_vecAddObject;
};