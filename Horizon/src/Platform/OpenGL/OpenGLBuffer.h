/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once

#include "Horizon/Renderer/Buffer.h"
#include "Horizon/Core.h"

namespace Horizon {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind()   const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual const BufferLayout& GetLayout() const      override { return m_Layout;   }

	private:
		uint32_t m_RendererID = 0;
		BufferLayout m_Layout;
	};


	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, size_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()   const override;
		virtual void UnBind() const override;

		inline virtual uint32_t GetCount() const { return m_Count; };
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;
	};

}