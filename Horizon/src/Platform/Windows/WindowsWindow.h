/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Window.h"
#include "Horizon/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Horizon {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline uint32_t GetWidth()  const override { return m_Data.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Height; }

		// Window Attributes
		inline void SetEventCallBack(const EventCallBackFn& callback) override 
		{
			m_Data.EventCallBack = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string title;
			uint32_t Width, Height;
			bool VSync;

			EventCallBackFn EventCallBack;
		};

		WindowData m_Data;
	};

}