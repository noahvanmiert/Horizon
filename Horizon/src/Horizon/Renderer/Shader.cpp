/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "hrpch.h"

#include "Shader.h"

#include "Horizon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Horizon {

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLShader(filepath);
		}

		HR_CORE_ASSERT(false, "Unkown Renderer API!");
		return nullptr;
	}


	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:     HR_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:   return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		HR_CORE_ASSERT(false, "Unkown Renderer API!");
		return nullptr;
	}

}