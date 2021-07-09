#include <Engine.h>

class TestLayer : public Engine::Layer
{
public:
	TestLayer()
		: Layer("TestLayer") {}

	void OnUpdate() override
	{
	}

	void OnEvent(Engine::Event& e) override
	{
		// debug
		APP_LOG(LOG_INFO, "111 TestLayer:::OnEvent(Engine::Event& e) {0}", e);
	}
};

class MainLoop : public Engine::Application
{
public:
	MainLoop()
	{
		PushLayer(new TestLayer());
	}

	~MainLoop()
	{

	}
};

Engine::Application* Engine::CreateApplication()
{
	return new MainLoop();
}
