/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "hrpch.h"
#include "Application.h"

#include "Horizon/Events/ApplicationEvent.h"
#include "Horizon/Log.h"

#include "Input.h"

#include <glfw/glfw3.h>


namespace Horizon {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		HR_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}


	Application::~Application()
	{

	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}


	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);

			if (e.m_Handled)
				break;
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}


	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float) glfwGetTime();
			DeltaTime deltatime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltatime);

			m_ImGuiLayer->Begin();

			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}
