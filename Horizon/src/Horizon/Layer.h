#pragma once

#include "Horizon/Core.h"
#include "Horizon/Events/Event.h"

#include "Horizon/Core/DeltaTime.h"

#include <string>


namespace Horizon {

	class HORIZON_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(DeltaTime deltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}