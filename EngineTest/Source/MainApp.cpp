#include <Engine.h>

class MainLoop : public Engine::Application
{
public:
	MainLoop()
	{

	}

	~MainLoop()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new MainLoop();
}
