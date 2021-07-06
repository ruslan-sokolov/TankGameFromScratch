#pragma once


// For use in client apps

#include "Engine/Application.h"
#include "Engine/Log.h"

// --- Entry Point ------------------------------------------------------------
#ifdef ENGINE_WIN_PLATFORM

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	// initilize
	Engine::Log::Init();
	ENGINE_LOG(warn, "Initialized Core Log1");
	APP_LOG(info, "Initialized Client Log1");



	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif
// ----------------------------------------------------------------------------
