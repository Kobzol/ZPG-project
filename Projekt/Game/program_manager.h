#pragma once

#include <unordered_map>

#include "content_manager.h"
#include "../Helper/file_helper.h"
#include "../Model/vertex.h"
#include "../Render/program.h"
#include "../Render/shader.h"

class ProgramManager : public ContentManager<Program>
{
public:
	static const std::string PROGRAM_DEFAULT;

	static ProgramManager& getInstance();

	void preloadPrograms();

	void dispose();

private:
	static const std::string SHADER_VERTEX_PATH;
	static const std::string SHADER_FRAGMENT_PATH;

	static ProgramManager instance;

	ProgramManager();
};