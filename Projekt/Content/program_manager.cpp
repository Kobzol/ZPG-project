#include "program_manager.h"
#include "../../Game/Camera/camera.h"

const std::string ProgramManager::PROGRAM_SIMPLE_CONSTANT = "constant";
const std::string ProgramManager::PROGRAM_MODEL = "model";
const std::string ProgramManager::PROGRAM_POSTPROCESS = "postprocess";
const std::string ProgramManager::PROGRAM_FONT = "font";
const std::string ProgramManager::PROGRAM_SKYBOX = "skybox";
const std::string ProgramManager::PROGRAM_SPRITE = "sprite";

const std::string ProgramManager::SHADER_VERTEX_PATH = "Shaders/Vertex/";
const std::string ProgramManager::SHADER_FRAGMENT_PATH = "Shaders/Fragment/";

ProgramManager ProgramManager::instance = ProgramManager();

ProgramManager& ProgramManager::getInstance()
{
	return ProgramManager::instance;
}

ProgramManager::ProgramManager() : observedCamera(nullptr)
{
	
}

void ProgramManager::preloadPrograms()
{
	this->preloadProgram(ProgramManager::PROGRAM_SIMPLE_CONSTANT, "model.vert", "constant.frag", Flags<ProgramEvent>(ProgramEvent::ViewProjection));
	this->preloadProgram(ProgramManager::PROGRAM_MODEL, "model.vert", "model.frag", Flags<ProgramEvent>({ ProgramEvent::ViewProjection, ProgramEvent::ViewPosition }));
	this->preloadProgram(ProgramManager::PROGRAM_POSTPROCESS, "postprocess.vert", "postprocess.frag", Flags<ProgramEvent>());
	this->preloadProgram(ProgramManager::PROGRAM_FONT, "font.vert", "font.frag", Flags<ProgramEvent>());
	this->preloadProgram(ProgramManager::PROGRAM_SKYBOX, "skybox.vert", "skybox.frag", Flags<ProgramEvent>(ProgramEvent::ViewProjection));
	this->preloadProgram(ProgramManager::PROGRAM_SPRITE, "sprite.vert", "sprite.frag", Flags<ProgramEvent>());
}

Program& ProgramManager::use(std::string identifier)
{
	if (this->items.count(identifier))
	{
		Program& program = this->items[identifier];

		if (this->currentProgram != identifier)
		{
			this->currentProgram = identifier;
			program.use();
		}

		if (this->observedCamera != nullptr && program.getEvents().isSet(ProgramEvent::ViewProjection))
		{
			program.setViewMatrix(this->observedCamera->calculateViewMatrix());
			program.setProjectionMatrix(this->observedCamera->calculateProjectionMatrix());
			program.setViewPosition(this->observedCamera->getGameObject()->getTransform().getPosition());
		}

		return program;
	}
	else throw std::runtime_error("Program with identifier " + identifier + " doesn't exist");
}
Program& ProgramManager::getCurrentProgram()
{
	return this->get(this->currentProgram);
}
std::string ProgramManager::getCurrentProgramName()
{
	return this->currentProgram;
}

void ProgramManager::save()
{
	this->saveStack.push(this->currentProgram);
}
void ProgramManager::restore()
{
	std::string lastSavedProgram = this->saveStack.top();
	this->saveStack.pop();

	this->use(lastSavedProgram);
}

void ProgramManager::dispose()
{
	for (auto program : this->items)
	{
		program.second.dispose();
	}

	this->items.clear();
}

void ProgramManager::preloadProgram(std::string identifier, std::string vertexPath, std::string fragmentPath, Flags<ProgramEvent> events)
{
	Shader vertexShader = ShaderLoader::getInstance().createShader(FileHelper::loadFile(ProgramManager::SHADER_VERTEX_PATH + vertexPath), GL_VERTEX_SHADER);
	Shader fragmentShader = ShaderLoader::getInstance().createShader(FileHelper::loadFile(ProgramManager::SHADER_FRAGMENT_PATH + fragmentPath), GL_FRAGMENT_SHADER);

	Program program(events);
	program.attachShader(vertexShader);
	program.attachShader(fragmentShader);
	program.link();

	this->load(identifier, program);
}

void ProgramManager::observeCamera(Camera* camera)
{
	this->observedCamera = camera;
}