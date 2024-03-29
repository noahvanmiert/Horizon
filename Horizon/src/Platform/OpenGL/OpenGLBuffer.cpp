/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "hrpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Horizon {

	
	/////////////////////////////////////////////////////////////////
	// VertexBuffer /////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////


	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}


	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}


	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}


	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	/////////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////


	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, size_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}


	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}


	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}