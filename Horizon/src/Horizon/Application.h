/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Core.h"
#include "Horizon/Window.h"
#include "Horizon/LayerStack.h"
#include "Horizon/Events/ApplicationEvent.h"

#include "Horizon/ImGui/ImGuiLayer.h"

#include "Horizon/Core/DeltaTime.h"


namespace Horizon {

	class HORIZON_API Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	/* To be defined in client */
	Application* CreateApplication();
}
