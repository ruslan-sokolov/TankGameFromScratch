// Code in this file use source from and inspired by TheCherno/Hazel engine project
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

		inline void SetEventCb(const EventCbFn& Cb) override { Data.Cb = Cb; }

		// Window attrubutes
		void SetVSync(bool Enabled) override;
		bool IsVSync() const override;
		
		void SetDynViewportScale(bool Enabled) override;
		bool IsDynViewportScale() const override;
		
		void SetFullscreen(bool Enabled) override;
		bool IsFullscreen() const override;
		//

	private:
		void Init(const WindowProps& Props);
		void Shutdown();
		void SetGLFWEvents();

		GLFWwindow* GL_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			
			unsigned int WidthAtStart;
			unsigned int HeightAtStart;
			
			/* Limit fps to monitor refresh rate */
			bool VSync;
			/* IF true then all rendered content will be scalled acording to window size */
			bool ViewportScale;
			/* true - Fullscreen mode, false - Window Mode */
			bool FullscreenMode;

			EventCbFn Cb;
		};

		WindowData Data;

	};

}
