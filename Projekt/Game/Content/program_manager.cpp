#include "program_manager.h"

ProgramManager ProgramManager::instance = ProgramManager();
const std::string ProgramManager::SHADER_VERTEX_PATH = "Shaders/Vertex/";
const std::string ProgramManager::SHADER_FRAGMENT_PATH = "Shaders/Fragment/";

const std::string ProgramManager::PROGRAM_DEFAULT = "default";

ProgramManager& ProgramManager::getInstance()
{
	return ProgramManager::instance;
}

ProgramManager::ProgramManager()
{

}

void ProgramManager::preloadPrograms()
{
	Shader vertexShader(FileHelper::loadFile(ProgramManager::SHADER_VERTEX_PATH + "lambert.vert"), GL_VERTEX_SHADER);
	Shader fragmentShader(FileHelper::loadFile(ProgramManager::SHADER_FRAGMENT_PATH + "lambert.frag"), GL_FRAGMENT_SHADER);

	Program program;
	program.attachShader(vertexShader);
	program.attachShader(fragmentShader);
	program.link();

	this->load(ProgramManager::PROGRAM_DEFAULT, program);
}

void ProgramManager::dispose()
{
	for (auto program : this->items)
	{
		program.second.free();
	}

	this->items.clear();
}