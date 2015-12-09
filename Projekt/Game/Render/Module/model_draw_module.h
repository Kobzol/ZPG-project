#pragma once

#include <string>

#include "irender_module.h"
#include "../../../Content/model_manager.h"
#include "../../../Model/model.h"
#include "../../../Render/render_utils.h"

class ModelDrawModule : public IRenderModule
{
public:
	ModelDrawModule(std::string modelName);

	void startDraw(RenderComponent* component) override;

private:
	std::string modelName;
};