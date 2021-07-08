// Code in this file is moslty copied from TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/

#include <PCH.h>
#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

#include <Engine/Events/ApplicationEvent.h>
#include <Engine/Events/MouseEvent.h>
#include <Engine/Events/KeyEvent.h>

namespace Engine {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCb(int Err, const char* Descr)
	{
		ENGINE_LOG(LOG_ERR, "GLFW Error ({0}): {1}", Err, Descr);
	}

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
			glfwSetErrorCallback(GLFWErrorCb);
			s_GLFWInitialized = true;
		}

		GL_Window = glfwCreateWindow(Props.Width, Props.Height, Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(GL_Window);
		glfwSetWindowUserPointer(GL_Window, &Data);
		SetVSync(true);

		// Set GLFW callbacks
		SetGLFWEvents();
	}

	void WindowsWindow::SetGLFWEvents()
	{
		glfwSetWindowSizeCallback(GL_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				WindowResizeEvent e(width, height);
				data.Cb(e);
			}
		);

		glfwSetWindowCloseCallback(GL_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent e;
				data.Cb(e);
			}
		);

		glfwSetKeyCallback(GL_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.Cb(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.Cb(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.Cb(e);
					break;
				}
				}
			}
		);

		glfwSetMouseButtonCallback(GL_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.Cb(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.Cb(e);
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(GL_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent e(static_cast<float>(xoffset), static_cast<float>(yoffset));
				data.Cb(e);
			}
		);

		glfwSetCursorPosCallback(GL_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent e(static_cast<float>(xpos), static_cast<float>(ypos));
				data.Cb(e);
			}
		);
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
