// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

// For use in client apps

#include "Engine/Log.h"
#include "Engine/Application.h"

// --- Entry Point ------------------------------------------------------------
#ifdef ENGINE_WIN_PLATFORM

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	// initilize
	Engine::Log::Init();
	GAME_LOG(info, "Initialized Game Log");
	ENGINE_LOG(warn, "Initialized Engine Log");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif
// ----------------------------------------------------------------------------
