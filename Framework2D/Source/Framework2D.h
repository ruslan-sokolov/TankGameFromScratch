#pragma once

#include <EntryPoint.h>

#include <Framework2D/Initializer.h>
#include <Framework2D/Gameplay/Game2D.h>


Engine::Application* Engine::CreateApplication()
{
	// create App derived from Engine-module class
	auto App = Framework2D::CreateGame("Tanki Game", 640, 480);

	// initialize with initialized defined in Game-module
	auto Initializer = Framework2D::CreateInitializer();
	Initializer->Init();
	delete Initializer;

	return App;
}
