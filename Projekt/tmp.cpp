//if (InputController::getInstance().isLeftMouseDown() && clickTimer.resetIfReady())
//{
//	glm::vec2 mousePos = glm::vec2(context.getWindowWidth() / 2, context.getWindowHeight() / 2);
//
//	GLfloat depth;
//	GLchar index;
//
//	glReadPixels(mousePos.x, mousePos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
//	glReadPixels(mousePos.x, mousePos.y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &index);
//	printf("Clicked on pixel %f, %f, depth %f, stencil index %u\n", mousePos.x, mousePos.y, depth, index);
//
//	glm::vec3 position = glm::unProject(glm::vec3(mousePos, depth), cameraScript->calculateViewMatrix(), cameraScript->calculateProjectionMatrix(), glm::vec4(0, 0, context.getWindowWidth(), context.getWindowHeight()));
//	std::cout << position.x << ", " << position.y << ", " << position.z << std::endl;
//	GameObject* tree = new GameObject(nullptr, new RenderComponent(Color::White, ProgramManager::PROGRAM_MODEL, new ModelDrawModule(ModelManager::MODEL_TREE)));
//	this->scene.add(tree);
//	tree->getTransform().setPosition(position);
//	tree->getTransform().setRotation(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
//}