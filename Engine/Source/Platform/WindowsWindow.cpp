// Code in this file is moslty copied from TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/

#include "PCH.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>

namespace Engine {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& Props)
	{
		return new WindowsWindow(Props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		Init(Props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		Data.Title = Props.Title;
		Data.Width = Props.Width;
		Data.Height = Props.Height;

		ENGINE_LOG(LOG_INFO, "Creating window {0} ({1}, {2})", Props.Title, Props.Width, Props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int Success = glfwInit();
			ENGINE_ASSERT(Success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		GL_Window = glfwCreateWindow(Props.Width, Props.Height, Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(GL_Window);
		glfwSetWindowUserPointer(GL_Window, &Data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(GL_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(GL_Window);
	}

	void WindowsWindow::SetVSync(bool Enabled)
	{
		glfwSwapInterval(Enabled);
		Data.VSync = Enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return Data.VSync;
	}

}
