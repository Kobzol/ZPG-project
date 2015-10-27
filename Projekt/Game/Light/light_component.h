#pragma once

#include <string>

#include "light.h"
#include "../Component/icomponent.h"
#include "../Object/game_object.h"
#include "../../Content/program_manager.h"

class LightComponent : public IComponent
{
public:
	LightComponent(Light* light, std::string name);

	void update() override;
	void dispose() override;

private:
	Light* light;
	std::string name;
};