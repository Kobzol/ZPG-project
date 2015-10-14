#pragma once

#include <unordered_map>

#include "../Helper/file_helper.h"
#include "../Model/vertex.h"
#include "../Render/program.h"
#include "../Render/shader.h"

class ProgramManager
{
public:
	static const std::string PROGRAM_DEFAULT;

	static ProgramManager& getInstance();

	void preloadPrograms();
	void load(std::string identifier, const Program &program);

	void dispose();

	Program& get(std::string identifier);

private:
	static const std::string SHADER_VERTEX_PATH;
	static const std::string SHADER_FRAGMENT_PATH;

	static ProgramManager instance;

	std::unordered_map<std::string, Program> programs;
};