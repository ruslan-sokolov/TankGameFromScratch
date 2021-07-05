#pragma once


// For use in client apps

#include "Engine/Application.h"


// --- Entry Point ------------------------------------------------------------
#ifdef ENGINE_WIN_PLATFORM

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif
// ----------------------------------------------------------------------------
