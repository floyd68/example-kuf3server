#pragma once

#include "entity.h"
#include "kaguya\kaguya.hpp" // lua

class ai_component : public CComponentBase
{
public:
	ai_component(EntityPtr ptr, const dynamic& file_name);
	~ai_component();

	DEFINE_DO_ATTR(ai_component)

private:
	GET_ATTR
	SET_ATTR
	DO_ACTION

	virtual COMPONENT_ID GetComponentID() const { return COMPONENT_ID::COM_AI; }
	virtual void update(float fElapsedTime)
	{
		state["update"](fElapsedTime);
	}

	// lua
	bool ready(float elapsed_time);
	void update_random_pos();

private:
	bool is_ready;
	kaguya::State state;
};

