#pragma once

#include <stack>
#include <unordered_map>

#include "content_manager.h"
#include "../../Game/Component/camera.h"
#include "../../Event/listeners.h"
#include "../../Helper/file_helper.h"
#include "../../Model/vertex.h"
#include "../../Render/program.h"
#include "../../Render/shader.h"

class ProgramManager : public ContentManager<Program>, CameraViewChangedListener, CameraProjectionChangedListener, CameraPositionChangedListener
{
public:
	static const std::string PROGRAM_SIMPLE_CONSTANT;
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

	void observeCamera(Camera& camera);

	void onCameraViewChanged(Camera& camera) override;
	void onCameraProjectionChanged(Camera& camera) override;
	void onCameraPositionChanged(Camera& camera) override;

private:
	static const std::string SHADER_VERTEX_PATH;
	static const std::string SHADER_FRAGMENT_PATH;

	static ProgramManager instance;

	ProgramManager();

	void preloadProgram(std::string identifier, std::string vertexPath, std::string fragmentPath, Flags<ProgramEvent> events);

	std::string currentProgram;
	std::stack<std::string> saveStack;
};