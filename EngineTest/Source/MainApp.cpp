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

	void Run()
	{
		while (true);
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new MainLoop();
}
