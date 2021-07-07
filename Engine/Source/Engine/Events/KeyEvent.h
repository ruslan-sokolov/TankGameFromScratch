// Code in this file is moslty copied from TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/

#pragma once

#include "Event.h"

namespace Engine {

	class ENGINE_API KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	
	protected:
		KeyEvent(int KeyCode)
			: KeyCode(KeyCode) {}

		int KeyCode;

	};

	class ENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount)
			: KeyEvent(KeyCode), RepeatCount(RepeatCount) {}

		int GetRepeatCount() const { return RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	
	private:
		int RepeatCount;

	};

	class ENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}