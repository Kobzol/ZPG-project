#pragma once

#include "game.h"
#include "timer.h"
#include "Component/icomponent.h"
#include "../Audio/audio_manager.h"

class WeaponController : public IComponent
{
public:
	virtual void update() override;

private:
	void shoot();

	Timer clickTimer = Timer(1.0f);
};