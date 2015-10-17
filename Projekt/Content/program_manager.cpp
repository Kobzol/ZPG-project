#include "program_manager.h"

ProgramManager ProgramManager::instance = ProgramManager();
const std::string ProgramManager::SHADER_VERTEX_PATH = "Shaders/Vertex/";
const std::string ProgramManager::SHADER_FRAGMENT_PATH = "Shaders/Fragment/";

const std::string ProgramManager::PROGRAM_VERTEX = "vertex";
const std::string ProgramManager::PROGRAM_MODEL = "model";

ProgramManager& ProgramManager::getInstance()
{
	return ProgramManager::instance;
}

ProgramManager::ProgramManager()
{
	
}

void ProgramManager::preloadPrograms()
{
	Shader vertexShader(FileHelper::loadFile(ProgramManager::SHADER_VERTEX_PATH + "model.vert"), GL_VERTEX_SHADER);
	Shader fragmentShader(FileHelper::loadFile(ProgramManager::SHADER_FRAGMENT_PATH + "model.frag"), GL_FRAGMENT_SHADER);

	Program program;
	program.attachShader(vertexShader);
	program.attachShader(fragmentShader);
	program.link();

	this->load(ProgramManager::PROGRAM_MODEL, program);
}

void ProgramManager::use(std::string identifier)
{
	if (this->items.count(identifier))
	{
		this->currentProgram = identifier;
		this->items[identifier].use();
	}
	else std::runtime_error("Program with identifier " + identifier + " doesn't exist");
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