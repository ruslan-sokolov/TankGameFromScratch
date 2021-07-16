// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#include <PCH.h>
#include "WindowsWindow.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Engine/Events/ApplicationEvent.h>
#include <Engine/Events/MouseEvent.h>
#include <Engine/Events/KeyEvent.h>

namespace Engine {

	static bool s_GLFWInitialized = false;
	static bool s_GLEWInitialized = false;
	
	// GLFW error callback
	static void GLFWErrorCb(int Err, const char* Descr)
	{
		ENGINE_LOG(LOG_ERR, "GLFW Error ({0}): {1}", Err, Descr);
	}

	// GLEW error callback
	// stolen from https://gist.github.com/liam-middlebrook/c52b069e4be2d87a6d2f hehe)
	static void GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length,
		const GLchar* msg, const void* data)
	{
		const char* _source;
		const char* _type;
		const char* _severity;

		switch (source) {
		case GL_DEBUG_SOURCE_API:
			_source = "API";
			break;

		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			_source = "WINDOW SYSTEM";
			break;

		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			_source = "SHADER COMPILER";
			break;

		case GL_DEBUG_SOURCE_THIRD_PARTY:
			_source = "THIRD PARTY";
			break;

		case GL_DEBUG_SOURCE_APPLICATION:
			_source = "APPLICATION";
			break;

		case GL_DEBUG_SOURCE_OTHER:
			_source = "UNKNOWN";
			break;

		default:
			_source = "UNKNOWN";
			break;
		}

		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			_type = "ERROR";
			break;

		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			_type = "DEPRECATED BEHAVIOR";
			break;

		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			_type = "UDEFINED BEHAVIOR";
			break;

		case GL_DEBUG_TYPE_PORTABILITY:
			_type = "PORTABILITY";
			break;

		case GL_DEBUG_TYPE_PERFORMANCE:
			_type = "PERFORMANCE";
			break;

		case GL_DEBUG_TYPE_OTHER:
			_type = "OTHER";
			break;

		case GL_DEBUG_TYPE_MARKER:
			_type = "MARKER";
			break;

		default:
			_type = "UNKNOWN";
			break;
		}

		switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH:
			_severity = "HIGH";
			break;

		case GL_DEBUG_SEVERITY_MEDIUM:
			_severity = "MEDIUM";
			break;

		case GL_DEBUG_SEVERITY_LOW:
			_severity = "LOW";
			break;

		case GL_DEBUG_SEVERITY_NOTIFICATION:
			_severity = "NOTIFICATION";
			break;

		default:
			_severity = "UNKNOWN";
			break;
		}

		ENGINE_LOG(LOG_ERR, "{0}: {1} of {2} severity, raised from {3}: {4}",
			(int)id, _type, _severity, _source, (const char*)msg);
	}

	Window* Window::Create(const WindowProps& Props)
	{
		return new WindowsWindow(Props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		Init(Props);

		ENGINE_LOG(LOG_INFO, "Created Windows window '{0}' ({1}, {2})", Props.Title, Props.Width, Props.Height);
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

		if (!s_GLFWInitialized)
		{
			int SuccessGLFWInit = glfwInit();
			ENGINE_ASSERT(SuccessGLFWInit, "Could not initialize GLFW!");

			// Set Open GL version
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

			GL_Window = glfwCreateWindow(Props.Width, Props.Height, Data.Title.c_str(), nullptr, nullptr);
			glfwMakeContextCurrent(GL_Window);
			glfwSetWindowUserPointer(GL_Window, &Data);
			SetVSync(true);

			// Set GLFW Event callback
			SetGLFWEvents();

			if (!s_GLEWInitialized)
			{
				int SuccessGLEWInit = glewInit() == GLEW_OK;
				ENGINE_ASSERT(SuccessGLEWInit, "Could not initialize GLEW!");

				ENGINE_LOG(trace, "Open GL Version: {0}", glGetString(GL_VERSION));

				// Open GL Blending Alpha
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
				// GLEW Error callback
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(GLDebugMessageCallback, NULL);

				s_GLEWInitialized = true;
			}

			// GLFW Error callback
			glfwSetErrorCallback(GLFWErrorCb);
			
			s_GLFWInitialized = true;
		}
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
