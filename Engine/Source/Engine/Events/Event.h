// Code in this file is moslty copied from TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/

#pragma once

#include <PCH.h>
#include <Engine/Core.h>

namespace Engine {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLossFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4)

	};

// used in event class definitions to quickly implement necessary member functions
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

// used in event class definitions to quickly implement necessary member function
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/*
	 * Basic class for all engine events
	 */

	class ENGINE_API Event
	{
		friend class EventDistpatcher;
	
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory Category) { return GetCategoryFlags() & Category; }
	
	protected:
		bool Handled = false;

	};

	class EventDistpatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDistpatcher(Event& EventToDispatch)
			: EventToDispatch(EventToDispatch)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> Func)
		{
			if (EventToDispatch.GetEventType() == T::GetStaticType())
			{
				EventToDispatch.Handled = Func(*(T*)&EventToDispatch);
				return true;
			}
			return false;
		}

	private:
		Event& EventToDispatch;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
