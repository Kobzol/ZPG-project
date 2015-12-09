#include "model_draw_module.h"
#include "../render_component.h"

ModelDrawModule::ModelDrawModule(std::string modelName) : modelName(modelName)
{

}

void ModelDrawModule::startDraw(RenderComponent* component)
{
	Program& program = ProgramManager::getInstance().getCurrentProgram();

	for (auto& mesh : ModelManager::getInstance().get(this->modelName)->getMeshes())
	{
		glm::vec3 color = component->getColor();
		color *= glm::vec3(mesh.getColor());

		program.setUniform3f("color", color);

		mesh.draw();
	}
}