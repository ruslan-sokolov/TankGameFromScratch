#pragma once

#include "Event.h"

namespace Engine {
	
	class ENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float X, float Y)
			: MouseX(X), MouseY(Y) {}

		float GetX() const { return MouseX; }
		float GetY() const { return MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float MouseX, MouseY;

	};

	class ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float OffsetX, float OffsetY) :
			OffsetX(OffsetX), OffsetY(OffsetY) {}

		float GetOffsetX() const { return OffsetX; }
		float GetOffsetY() const { return OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetOffsetX() << ", " << GetOffsetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float OffsetX, OffsetY;
	
	};

	class ENGINE_API MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int Button)
			: Button(Button) {}

		int Button;

	};

	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int Button)
			: MouseButtonEvent(Button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}