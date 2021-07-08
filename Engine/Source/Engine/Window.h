// Code in this file is moslty copied from TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

#include <PCH.h>

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine {

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& Title = "Engine Window",
						unsigned int Width = 640,
			            unsigned int Height = 480)
			: Title(Title), Width(Width), Height(Height) {}

	};

	class ENGINE_API Window
	{
	public:
		using EventCbFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCb(const EventCbFn& Cb) = 0;
		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& Props = WindowProps());
	};
}