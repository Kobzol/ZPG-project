#pragma once

#include <stack>
#include <unordered_map>

#include "content_manager.h"
#include "../../Helper/file_helper.h"
#include "../../Model/vertex.h"
#include "../../Render/program.h"
#include "../../Render/shader.h"

class ProgramManager : public ContentManager<Program>
{
public:
	static const std::string PROGRAM_VERTEX;
	static const std::string PROGRAM_MODEL;
	static const std::string PROGRAM_POSTPROCESS;
	static const std::string PROGRAM_FONT;

	static ProgramManager& getInstance();

	void preloadPrograms();

	void use(std::string identifier);
	Program& getCurrentProgram();
	std::string getCurrentProgramName();

	void save();
	void restore();

	void dispose();

private:
	static const std::string SHADER_VERTEX_PATH;
	static const std::string SHADER_FRAGMENT_PATH;

	static ProgramManager instance;

	ProgramManager();

	void preloadProgram(std::string identifier, std::string vertexPath, std::string fragmentPath);

	std::string currentProgram;
	std::stack<std::string> saveStack;
};