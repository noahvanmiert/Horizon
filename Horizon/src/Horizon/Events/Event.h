/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Core.h"


namespace Horizon {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyTyped, KeyReleased,
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


#define EVENT_CLASS_TYPE(type)			static EventType GetStaticType() { return EventType::##type; }\
										virtual EventType GetEventType() const override { return GetStaticType(); }\
										virtual const char* GetName()    const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags()   const override { return category; }


	class HORIZON_API Event
	{
		friend class EventDispatcher;

	public:
		/// <summary>
		/// Returns the type of an event, the types are defined in the EventType enum.
		/// </summary>
		/// <returns>event type</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// Returns the name of an event
		/// </summary>
		virtual const char* GetName()    const = 0;

		/// <summary>
		/// Returns the category flags of an event, these are defined in the EventCategory enum.
		/// </summary>
		/// <returns>event category</returns>
		virtual int GetCategoryFlags()   const = 0;

		/// <summary>
		/// Returns a string with info about the event, this is only used for logging.
		/// </summary>
		/// <returns> string with event info </returns>
		virtual std::string ToString()   const { return GetName(); }

		/// <summary>
		/// Returns true if an event is in the given category.
		/// </summary>
		/// <param name="category">An EventCategory category</param>
		/// <returns></returns>
		inline bool IsInGategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	public:
		bool m_Handled = false;
	};


	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		/// <summary>
		/// Dispatches a function for an event callback 
		/// </summary>
		/// <typeparam name="T">-> The specific event class</typeparam>
		/// <param name="func">->The function wrapped in HR_BIND_EVENT_FN(fn), this macro is defined in Core.h</param>
		/// <returns>True if callback function could be dispatched</returns>
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
