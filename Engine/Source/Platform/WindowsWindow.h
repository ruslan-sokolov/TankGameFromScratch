// Code in this file is moslty copied from TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

#include "Engine/Window.h"

struct GLFWwindow;

namespace Engine {

	class ENGINE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return Data.Width; }
		inline unsigned int GetHeight() const override { return Data.Height; }

		// Window attrubutes
		inline void SetEventCb(const EventCbFn& Cb) override { Data.Cb = Cb; }
		void SetVSync(bool Enabled) override;
		bool IsVSync() const override;

	private:
		void Init(const WindowProps& Props);
		void Shutdown();
		void SetGLFWEvents();

		GLFWwindow* GL_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCbFn Cb;
		};

		WindowData Data;

	};

}
