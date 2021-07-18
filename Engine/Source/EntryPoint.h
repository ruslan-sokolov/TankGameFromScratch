#pragma once

#include "Engine.h"

#ifdef ENGINE_WIN_PLATFORM

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	// initilize
	Engine::Log::Init();
	GAME_LOG(info, "Initialized Game Log");
	ENGINE_LOG(warn, "Initialized Engine Log");

	Engine::ApplicationInstance = Engine::CreateApplication();
	Engine::ApplicationInstance->Run();
	delete Engine::ApplicationInstance;

	std::cin.get();
}

#endif
